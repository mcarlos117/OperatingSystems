#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2);

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
    int arg1 = atoi(argv[1]);
    int  arg2 = atoi(argv[2]);
    int  arg3 = atoi(argv[3]);
    int  arg4 = atoi(argv[4]);
    int  arg5 = atoi(argv[5]);
    int  arg6 = atoi(argv[6]);
    int  arg7 = atoi(argv[7]);

    int sum = arg2 + arg3 + arg4 + arg5 + arg6 + arg7;

    char str1[sum],str2[sum];

    fcfsa(str1,str2,arg2, arg3, arg4, arg5, arg6, arg7);
    display("Part 1", str1, str2);

    sjf(str1,str2,arg2,arg3,arg4,arg5,arg6,arg7);
    display("Part 2", str1, str2);

    psjf(str1,str2,arg2,arg3,arg4,arg5,arg6,arg7);
    display("Part 3", str1, str2);

    rr(str1,str2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    display("Part 4", str1, str2);

    return 0;
}
