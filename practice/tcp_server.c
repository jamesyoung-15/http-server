#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
    //variables
    struct sockaddr_in address, client_address;
    int server_fd, client_fd;
    int address_length = sizeof(address);
    int client_address_length = sizeof(client_address);

    //create socket and check error
    server_fd = socket(AF_INET, SOCK_STREAM,0);
    if (server_fd <0)
    {
        perror("error creating socket \n");
        exit(1);
    }
    else
    {
        printf("Created socket\n");
    }
    //bind socket and check error
    memset(&address,0,address_length); //use memset instead of bzero
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(4545);
    if(bind(server_fd, (struct sockaddr *) &address, address_length)<0)
    {
        perror("error in binding \n");
        exit(1);
    }
    else 
    {
        printf("Bind success.\n");
    }

    //listen
    if(listen(server_fd, 3)<0)
    {
        perror("failed to listen\n");
        exit(1);
    }

    //accept
    client_fd = accept(server_fd, (struct sockaddr *) &client_address, (socklen_t *)&client_address_length);
    if(client_fd <0)
    {
        perror("error in accepting\n");
        exit(1);
    }

    //read from client
    char buf[1024]={0};
    int valread = read(client_fd, buf, sizeof(buf));
    time_t time_received = time(0);
    struct tm *tm = localtime(&time_received);

    if(valread < 0)
    {
        perror("read error");
    }
    printf("Message from client: %s\n",buf);
    printf("Client's address: %s \n", inet_ntoa(client_address.sin_addr));
    printf("Received at: %s.",asctime(tm));

    //close sockets
    close(client_fd);
    close(server_fd);
    return 0;
}