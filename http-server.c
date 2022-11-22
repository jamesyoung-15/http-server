#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//network headers
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 4545
#define BUFFERSIZE 2048



int main()
{
    //variables for socket
    struct sockaddr_in server_address, client_address; //client and server address structs
    int serverFd, clientFd, fileFd; //file descriptors
    int serv_address_length = sizeof(server_address); //get size of server address struct
    int client_address_length = sizeof(client_address); //get size of client address struct
    char buf[BUFFERSIZE] = {0}; //buffer for http request
    char *testResponsee = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"; //http response test
    char *forbiddenResponse = "HTTP/1.1 403 Forbidden\n Content-Type: text/plain\n Content-Length: 13\n\n403 Forbidden";
    char *htmlResponse = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><head>Hello World. This is my static page.</head></html>";

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
        close(serverFd);
        return 1;
    }
    printf("Socket binded\n");

    //listen socket, SOMAXCONN is maximum connections allowed (see man for listen)
    if(listen(serverFd, SOMAXCONN)<0)
    {
        perror("Error listening\n");
        close(serverFd);
        return 1;
    }
    printf("Socket is listening for incoming connection\n");

    //accept, read/write section
    while(1)
    {
        //accept incoming connection, see man accept for more details
        int clientFd = accept(serverFd, (struct sockaddr *)&client_address, (socklen_t *) &client_address);
        //check whether client's connection attempt was accepted
        if(clientFd<0)
        {
            perror("Connection declined/error\n");
            continue;
        }
        printf("Client connected\n");

        //read request from client
        int valread = read(clientFd,buf,sizeof(buf));
        //if request has error, return status code 403
        if(valread<=0)
        {
            write(clientFd,forbiddenResponse,strlen(forbiddenResponse));
        }
        //printf("%s\n",&buf[0]);
        //skip GET and space (hence i=4) to get to filepath, stop once second space is detected
        int targetLength = 0;
        for(int i=4;i<BUFFERSIZE;i++)
        {
            if(buf[i]==' ')
            {
                break;
            }
            else 
            {
                targetLength++;
            }
        }
        char targetPath[targetLength];
        //not working change tmr
        for(int i = 0;i<targetLength;i++)
        {
            targetPath[i] = buf[i+4];
        }
        //printf("%d: %s\n",targetLength,targetPath);
        //if request line is GET / with no filename, redirect to index.html by writing GET /src/index.html



        //write(clientFd,testResponsee,strlen(testResponsee));
        write(clientFd, htmlResponse, strlen(htmlResponse));


        //close sockets
        close(clientFd);
        //close(htmlData);
    }
    //close server socket
    close(serverFd);

    return 0;
}