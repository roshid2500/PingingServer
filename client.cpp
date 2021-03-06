#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <chrono> 
#define PORT	 12551

using namespace std; 

int main() {
	int sockfd, n, send;
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
	len = sizeof(servaddr);

	//Set the timeout for the socket to 1sec
	if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&t,sizeof(struct timeval)) < 0){
		cout << "Error setting timeout" << endl;
	}

	//Loop to send 10 packets
	for(unsigned i = 0; i < 10; i++){
		//track time before sending the packet to server
		auto t1 = chrono::high_resolution_clock::now();
  		int send = sendto(sockfd, (const char *)buffer, strlen(buffer),
       			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
		 

		//receive packet
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
		
		//time after receiving
		auto t2 = chrono::high_resolution_clock::now();
		
		auto t3 = (t2 - t1).count(); 

		//output either success or timeout
		if(n >= 0)
    			cout << "Received in " << t3 << " (nanoseconds)" << endl;
    		else
     			cout << "Packet not received; timeout" << endl;

	}



	return 0;
}
