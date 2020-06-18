#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

EXPORT int __stdcall add2(int num){
  return num + 2;
}

EXPORT int __stdcall mul(int num1, int num2){
  return num1 * num2;
}

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 1000
#define PORT 8080 
#define SA struct sockaddr 
 
int sockfd, connfd, len; 
struct sockaddr_in servaddr, cli; 

void init_server() { 
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else {
        printf("Socket successfully created..\n"); 
    }
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 1)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else{
        printf("Server listening..\n"); 
    }

    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else {
        printf("server acccept the client...\n"); 
    }
}

int recv(char *buff) {
	return read(sockfd, buff, sizeof(buff)); 
}

int send(char *buff) {
	return write(sockfd, buff, sizeof(buff)); 
}

void end_server() {
	close(sockfd);
}