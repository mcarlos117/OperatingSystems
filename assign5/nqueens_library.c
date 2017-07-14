#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>

#include "nqueens_library.h"

int generate_n_queens_serial(int n, int print_flag){
    int list[n];
    int i,count, solcnt;
    char str[1000000];
    char sol[1000000];
    count = 1;
    solcnt = 0;

    for(i =0; i < n; i++){
        list[i] = i;
    }
    if(print_flag == 1){
        get_array_string(list,n,str);
    }
    while(!next_permutation(list,n)){
        count++;
        if(print_flag == 1){
            get_array_string(list,n,str);
        }
        if(check_diagonal(list,n) == 0){
            solcnt++;
            if(print_flag == 1){
                get_array_string(list,n,sol);
            }
        }
    }
    if(print_flag == 1){
        printf("%s",str);
    }

    printf("Permutations: %d\n",count);

    if(print_flag == 1){
        printf("%s", sol);
    }
    printf("Solutions: %d\n", solcnt);
}

void get_array_string(int *list, int n, char *s){
    int i,size;
    char str[1000000];

    for(i = 0; i < n; i++){
        sprintf(str, "    %d", list[i]);
        strcat(s,str);
    }
    strcat(s,"\n");
}

int next_permutation(int *list, int n){
    int  i,j;
    int temp;

    if (n == 0)
        return 1;
    i = n - 1;
    while (i > 0 && list[i - 1] >= list[i])
        i--;
    if (i == 0)
        return 1;

    j = n - 1;
    while (list[j] <= list[i - 1])
        j--;
    temp = list[i - 1];
    list[i - 1] = list[j];
    list[j] = temp;

    j = n - 1;
    while (i < j) {
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
        i++;
        j--;
    }
    return 0;
}

int check_diagonal(int *list, int n){
    int i,j;

    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j ++){
            if((abs(list[i] - list[j])) == (j - i)){
                return 1;
            }
        }
    }
    return 0;
}

int generate_n_queens_serial_one(int n, int out_flag, int first){
    int list[n];
    int i,count, solcnt;
    char str[1000000];
    char str2[1000000];
    char sol[1000000];
    count = 1;
    solcnt = 0;

    for(i =0; i < n; i++){
        list[i] = i;
    }
    if(out_flag == 1){
        if(list[0] == first){
            get_array_string(list,n,str);
        }
        if(list[0] != first){
            get_array_string(list,n,str2);
        }
    }
    while(!next_permutation(list,n)){
        count++;
        if(out_flag == 1){
            if(list[0] == first){
                get_array_string(list,n,str);
            }
            if(list[0] != first){
                get_array_string(list,n,str2);
            }
        }
        if(check_diagonal(list,n) == 0){
            if(list[0] == first){
                solcnt++;
                if(out_flag == 1){
                    get_array_string(list,n,sol);
                }
            }
        }
    }
    if(out_flag == 1){
        printf("%s",str);
        printf("%s",str2);


        printf("Permutations: %d\n",count);
    }

    if(out_flag == 1){
        printf("%s", sol);

        printf("Solutions: %d\n", solcnt);
    }
    return solcnt;
}

void *queens_thread(void *infopointer){

    int bytes;

    thread_info_t *thr = (thread_info_t*) infopointer;

    thr->result = generate_n_queens_serial_one(thr->n,thr->out_flag,thr->first );
    pthread_mutex_lock(&mutex);

    sprintf(thr->box,"First: %d  Solutions: %d\n", thr->first,thr->result);

    bytes = write(thr->fd,thr->box,30);
    if(bytes <= 0){
        perror("Write error\n");
        exit(1);
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}
