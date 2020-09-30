#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT	 12500


int main() {
	int sockfd, n;
  time_t start, end;
	socklen_t len;
	char buffer[1024] = "hello";
	struct sockaddr_in servaddr;
  struct timeval t;

  //set timeout val to 1
  t.tv_sec = 1;
	t.tv_usec = 0;

	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));

	// Fill server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number

	int l = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&t,sizeof(struct timeval));
	std::cout << "setsock " << l << std::endl;

	for(unsigned i = 0; i < 10; i++){
		std::cout << "here1111" << std::endl;
    time(&start);

    sendto(sockfd, (const char *)buffer, strlen(buffer),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);

		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
		MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';

		if(n >= 0){
    	time(&end);
    	std::cout << "Received in " << difftime(start, end) << std::endl;
		}
    else{
      std::cout << "Packet not received; timeout" << std::endl;
    }

	}



	return 0;
}
