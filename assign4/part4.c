#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "nqueens_library.h"

int main(int argc, char * argv[]){
    int n,i,arg1, arg2, outflag;

    if(argc == 2){
        arg1 = atoi(argv[1]);
        outflag = 1;
    }else if (argc == 3){
        arg1 = atoi(argv[1]);
        arg2 = atoi(argv[2]);
        outflag = arg2;
    }else{
        printf("Error!\n");
    }

    //thr.n = arg1;
    pthread_t threads[arg1];
    thread_info_t thr[arg1];

    for(i = 0; i < arg1; i++){
        thr[i].first = i;
        thr[i].n = arg1;
        thr[i].out_flag = outflag;
        pthread_create(&threads[i], NULL, queens_thread,&thr[i]);
    }

    for(i = 0; i < arg1; i++){
        pthread_join(threads[i],NULL);
    }

    return 0;
}
