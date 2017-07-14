#include <stdio.h>
#include <stdlib.h>
#include "nqueens_library.h"
int generate_n_queens_serial(int n, int print_flag);

int main(int argc, char * argv[]){
    int arg1, arg2;

    if(argc == 2){
        arg1 = atoi(argv[1]);
        generate_n_queens_serial(arg1,1);
    }else if (argc == 1){
        printf("Error!\n");
    }else{
        arg1 = atoi(argv[1]);
        arg2 = atoi(argv[2]);
        if(arg2 == 0){
            generate_n_queens_serial(arg1,0);
        }else if(arg2 == 1){
            generate_n_queens_serial(arg1,1);
        }else{
            printf("Error!\n");
        }
    }

    return 0;
}
