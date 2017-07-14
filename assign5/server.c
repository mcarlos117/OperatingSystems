#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "nqueens_library.h"

int main(int argc, char *argv[])
{
    int sock, newsock, portno;
    socklen_t clilen;
    char buff[1000000];
    struct sockaddr_in serv_addr, cli_addr;
    int n,i;
    int num,sol;
    int total;
    int enable = 1;

    //total = 0;

    if (argc < 2) {
        fprintf(stderr,"Error, no port provided\n");
        exit(1);
    }

    fprintf(stderr, "Waiting for client....\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0){
        perror("Error opening socket");
        exit(1);
    }
    if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&enable, sizeof(int)) < 0){
        perror("setsocketopt(SO_REUSEADDR) failed");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons((short)portno);

    if (bind(sock, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) == -1){
        perror("Error on binding");
        exit(1);
    }

    // I wasn't sure if the server was suppose to keep running after function call.
    // From what I understood, the connection was suppose to be cut and
    // the server stops running. But IF the server was suppose to be kept running,
    // that can be easily done by uncommenting this while and the bracket.

    //while(1){
    char str[1000000]= "";

    listen(sock,5);
    clilen = sizeof(cli_addr);
    if((newsock = accept(sock,(struct sockaddr *) &cli_addr,&clilen)) != -1){
        fprintf(stderr,"Calculating...\n");
    }

    if (newsock < 0){
        perror("Error on accept");
        exit(1);
    }

    bzero(buff,1000000);
    n = read(newsock,buff,99999);
    num = atoi(buff);

    pthread_t threads[num];
    thread_info_t thr[num];
    pthread_mutex_init(&mutex,NULL);

    for(i = 0; i < num; i++){
        thr[i].first = i;
        thr[i].n = num;
        thr[i].fd = newsock;
        thr[i].out_flag = 0;
        pthread_create(&threads[i],NULL,queens_thread,&thr[i]);
    }

    total = 0;
    for(i =0; i < num; i++){
        pthread_join(threads[i],NULL);
        total += thr[i].result;
    }

    pthread_mutex_destroy(&mutex);

    memset(&buff[0],0,sizeof(buff));
    sprintf(buff,"Total Solutions: %d\n",total);
    write(newsock,buff,30);

    //}

    printf("Done\n");
    close(newsock);
    close(sock);
    return 0;
}
