#include <stdio.h>
#include <stdlib.h>
#include "nqueens_library.h"

int main(int argc, char * argv[]){
    int n,i,arg1, arg2;

    thread_info_t thr;

    if(argc == 2){
        arg1 = atoi(argv[1]);
        thr.out_flag = 0;
    }else if(argc == 3) {
        arg1 = atoi(argv[1]);
        arg2 = atoi(argv[2]);
        thr.out_flag = arg2;
    }else{
        printf("Error!\n");
    }

    thr.n = arg1;

    for(i = 0; i < arg1; i++){
        thr.first = i;
        queens_thread(&thr);
    }

    return 0;
}
