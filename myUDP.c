#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  
#define PORT     8080
#define MAXLINE 1024
  
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
      
    printf("myUDP\n");

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    servaddr.sin_family    = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
      
    int len, n;
  
    len = sizeof(cliaddr);  
  
  while(1){
      n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                  MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                  &len);
      
      //memcpy();
      buffer[n] = '\0';
      printf("Client : %d\n", buffer[0]);
      printf("Client : %d\n", buffer[1]);
      printf("Client : %d\n", buffer[2]);
      printf("Client : %d\n", buffer[3]);    

    // sendto(sockfd, (const char *)hello, strlen(hello), 
    //     MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
    //         len);
    // printf("Hello message sent.\n"); 
  }  
      
    return 0;
}
