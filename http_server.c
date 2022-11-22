#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//network headers
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 4545
#define BUFFERSIZE 1024

/*function for http response*/
void httpHeader()
{
    //variable for http response
    char *http_header = "HTTP/1.1 200 OK\n";

    //open index.html file
    FILE *htmlFile = fopen("./src/index.html", "r");

}


int main()
{
    //variables for socket
    struct sockaddr_in server_address, client_address; //client and server address structs
    int serverFd, clientFd; //file descriptors
    int serv_address_length = sizeof(server_address); //get size of server address struct
    int client_address_length = sizeof(client_address); //get size of client address struct
    char buf[BUFFERSIZE] = {0}; //buffer for http request

    //create socket
    serverFd = socket(AF_INET, //domain type
     SOCK_STREAM, //Use TCP (UDP is SOCK_DGRAM)
      0 //protocol most of the time set to 0
      );

    //check for socket creation error
    if(serverFd<0)
    {
        perror("socket creation failure\n");
        return 1;
    }
    printf("Socket created\n");

    //bind socket
    memset(&server_address, 0, serv_address_length); //set memory address of server address to 0
    server_address.sin_family = AF_INET; //set to AF_INET for TCP and UDP
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); //accept any ip address, htonl to convert host byte order to network byte order
    server_address.sin_port = htons(PORT); //listen on defined port, htons to convert host byte order to network byte order

    //check for error when binding socket
    if(bind(serverFd, (struct sockaddr *) &server_address, client_address_length)<0)
    {
        perror("Couldn't bind socket");
        return 1;
    }
    printf("Socket binded\n");

    //listen socket, SOMAXCONN is maximum connections allowed (see man for listen)
    if(listen(serverFd, SOMAXCONN)<0)
    {
        perror("Error listening\n");
        return 1;
    }
    printf("Socket is listening for incoming connection\n");

    //accept, read/write section
    while(1)
    {
        //accept incoming connection, see man accept for more details
        int acceptFd = accept(serverFd, (struct sockaddr *)&client_address, (socklen_t *) &client_address);
        //check whether client's connection attempt was accepted
        if(acceptFd<0)
        {
            perror("Connection declined/error\n");
            continue;
        }
        printf("Client connected\n");

        //read request from client
        
    }

    //close server socket
    close(serverFd);

    return 0;
}