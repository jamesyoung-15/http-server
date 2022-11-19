#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main()
{
    //variables
    struct sockaddr_in serv_address;
    int sock, client_fd;
    int address_length = sizeof(serv_address);

    //create socket and check error
    sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock <0)
    {
        perror("error creating socket \n");
        exit(1);
    }
    else
        printf("Created socket\n");

    memset(&serv_address,0,address_length); //use memset instead of bzero
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(4545);

    //check if ip address is valid
    if(inet_pton(AF_INET,"127.0.0.1",&serv_address.sin_addr)<0)
    {
        perror("invalid ip \n");
        exit(1);
    }
    //connect to server
    client_fd = connect(sock, (struct sockaddr *) &serv_address, address_length);
    if(client_fd<0)
    {
        printf("couldnt connect\n");
        exit(1);
    }

    //send message to server
    char* message = "Hello World";
    send(sock,message,strlen(message),0);
    printf("Message to server: %s \n", message);

    //close sockets
    close(client_fd);
    return 0;
}