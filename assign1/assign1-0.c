#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

void part0(char *s1, char *s2);
void display(char *heading, char *s1, char *s2);


int main(int argc, char*argv[]){
    int n, fdin, fdout;
    char buf[5000];

    if (argc == 8){
        printf("inputs: %s %s %s %s %s %s %s\n",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);


    }else{
        printf("You didn't enter 7 numbers\n");
        return 0;
    }

    int  arg2 = atoi(argv[2]);
    int  arg3 = atoi(argv[3]);
    int  arg4 = atoi(argv[4]);
    int  arg5 = atoi(argv[5]);
    int  arg6 = atoi(argv[6]);
    int  arg7 = atoi(argv[7]);

    int sum = arg2 + arg3 + arg4 + arg5 + arg6 + arg7;

    char str1[sum],str2[sum];

    /*if(sum != (arg2 + arg3 + arg4 + arg5 + arg6 + arg7)){
        printf("Array size is incorrect!\n");
    }*/

    part0(str1,str2);
    display("Part 0\n", str1, str2);

    return 0;
}
