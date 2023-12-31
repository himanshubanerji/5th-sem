#include "bits/stdc++.h"
#define PORT 10200

void clifunc(int sockfd)
{
    printf("I am a client and my name is Himanshu.\n");
    int a, b;
    char c;
    printf("Enter an arithmetic expression : \n");
    scanf("%d%c%d", &a, &c, &b);
    write(sockfd, (int *)&a, sizeof(int));
    write(sockfd, (int *)&b, sizeof(int));
    write(sockfd, (char *)&c, sizeof(char));
    int res;
    read(sockfd, (int *)&res, sizeof(int));
    printf("%d %c %d = %d\n", a, c, b, res);
    printf("Client Closing!\n");
}

int main(int argc, char const *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in server_address;
    int result;
    char ch;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("172.16.48.87");
    len = sizeof(server_address);
    result = connect(sockfd, (struct sockaddr *)&server_address, len);
    if(result == -1)
    {
        printf("Connection Error Occured!\n");
        exit(0);
    }
    clifunc(sockfd);
    close(sockfd);
}