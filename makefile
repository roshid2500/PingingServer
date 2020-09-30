C=client
S=server
CFLAGS=-g -std=c++14


all: $(S).o $(C).o 
	g++ $(CFLAGS) $(S).o -o $(S)
	g++ $(CFLAGS) $(C).o -o $(C) 

$(C).o : $(C).cpp
	g++ $(CFLAGS) -c $(C).cpp -o $(C).o

$(S).o: $(S).cpp
	g++ $(CFLAGS) -c $(S).cpp -o $(S).o

clean:
	rm $(S) $(C) *.o


