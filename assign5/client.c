#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sock, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buff[100000];
    int i, num;

    if (argc < 4) {
        fprintf(stderr,"usage %s n port hostname\n",argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("Error opening socket");
        exit(1);
    }

    server = gethostbyname(argv[3]);
    if (server == NULL) {
        fprintf(stderr,"Error, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("Error connecting");
        exit(1);
    }else{
        fprintf(stderr,"Connection Made. Calculating in server.....\n");
    }

    bzero(buff,100000);

    n = write(sock,argv[1],strlen(argv[1]));
    if (n < 0){
        perror("Error writing to socket");
        exit(1);
    }

    bzero(buff,100000);

    num = atoi(argv[1]);
    for(i = 0; i < num; i++){
        n = read(sock,buff,30);
        if (n < 0){
            perror("Error reading from socket");
            exit(1);
        }
        printf("%s",buff);
        memset(&buff[0],0,sizeof(buff));
        n = 0;
    }

    n = read(sock,buff,30);
    if(n == -1){
        perror("Error reading total.\n");
        exit(-1);
    }
    printf("%s",buff);

    close(sock);
    return 0;
}
