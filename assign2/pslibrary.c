#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pslibrary.h"

#define READY 0
#define RUNNING 1
#define WAITING 2
#define DONE 3

void part0(char *s1,char *s2){
    strcpy(s1,"RRwwwwwRRRRRRRRR");
    strcpy(s2 ,"rrRRRRwwwwwwwwrrRRRRRRR");

}

void display(char *heading, char *s1, char *s2){
    printf("\n");
    printf("%s\n",heading);
    printf("%s\n",s1);
    printf("%s\n",s2);
    int s1len;
    int s2len;
    int i, numlr1,numlr2;
    int numur1, numur2;
    float avg,longer;

    s1len = strlen(s1);
    s2len = strlen(s2);
    numlr1 = 0;
    numlr2 = 0;
    numur1 = 0;
    numur2 = 0;
    for(i = 0; i < s1len; i++){
        if(s1[i] == 'r' ){
            numlr1++;
        }
    }

    for (i = 0; i < s2len; i++){
        if(s2[i] == 'r'){
            numlr2++;
        }
    }

    for(i = 0; i < s1len; i++){
        if(s1[i] == 'R'){
            numur1++;
        }
    }

    for(i = 0; i < s2len; i++){
        if(s2[i] == 'R'){
            numur2++;
        }
    }

    avg = (float)(numlr1 + numlr2) / 2;
    if(s1len < s2len){
        longer = (float) (numur1 + numur2)/s2len;
    }else{
        longer = (float) (numur1 + numur2)/s1len;
    }

    printf("%d %d %.1f %.5f\n", numlr1, numlr2,avg,longer);

}

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2){
    int i,j,k;
    int count1,count2;
    int s1Start,s1End;
    int s2Start, s2End;
    int str1, str2;

    s1Start = 0;
    s1End = x1;

    for(i = s1Start; i < s1End; i++){
        s1[i] = 'R';
    }

    s1Start = s1End;
    s1End += y1;
    for( i = s1Start; i < s1End; i++){
        s1[i] = 'w';
    }

    s1Start = s1End;
    s1End += z1;
    for(i = s1Start; i < s1End; i++){
        s1[i] = 'R';
    }

    s1[s1End] = '\0';

    s2Start = 0;
    s2End = x1;
    for(i = s2Start; i < s2End; i++){
        s2[i] = 'r';
    }

    s2Start = s2End;
    s2End += x2;
    for(i = s2Start; i < s2End; i++){
        s2[i] = 'R';
    }

    s2Start = s2End;
    s2End += y2;
    for(i = s2Start; i < s2End; i++){
        s2[i] = 'w';
    }

    s2Start = s2End;
    s2End += z2;
    for(i = s2Start; i < s2End; i++){
        s2[i] = 'R';
    }

    s2[s2End] = '\0';
    j = 0;

    while ((s1[j] != '\0') && (s2[j] != '\0')){
        if(s1[j] == 'R' && s2[j] == 'R'){
            if(s2[j] == s2[j - 1] ){
                str1 = strlen(s1);
                for(k = str1; k >= j; k--){
                    s1[k+1] = s1[k];
                }
                s1[j] = 'r';
            }else{
                str2 = strlen(s2);
                for(k = str2; k >= j; k--){
                    s2[k + 1] = s2[k];
                }
                s2[j] = 'r';
            }
        }
        j++;
    }
}

static char stateChars[] = {'r','R','w',0};

/* 1) handle state changes:
   running process completes CPU burst
   running process has quantum expire
   IO complete
   2) do context switch if necessary
   both ready
   one ready and CPU free
   3) append appropriate characters to character arrays
   avoid putting in multiple string terminators
 */
/* assume s1 and s2 point to buffers with enough space to hold the result */
/* assume that the int parameters are strictly greater than 0 */
void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;                                         /* quantum remaining */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0){
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            state1 = RUNNING;
        }
        /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        //qleft--;                   /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */
}


void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;                                         /* quantum remaining */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0){
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            if(cpuLeft1 <= cpuLeft2){
                state1 = RUNNING;
            }else{
                state2 = RUNNING;
            }
        }
        /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        //qleft--;                   /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */
}


void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;                                         /* quantum remaining */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0){
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
            if(cpuLeft1 < cpuLeft2){
                state2 = READY;
            }
        }
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
            if(cpuLeft2 < cpuLeft1){
                state1 = READY;
            }
        }
        /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            if(cpuLeft1 <= cpuLeft2){
                state1 = RUNNING;
            }else{
                state2 = RUNNING;
            }
        }
        /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        //qleft--;                   /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */
}


void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;                                         /* quantum remaining */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
                state2 = DONE;
                s2[i] = stateChars[state2];            /* terminate the string */
            }
            else
                state2 = WAITING;

        }

        /* running process has quantum expire */
        if ((state1 == RUNNING) && (qleft == 0) ) {
            state1 = READY;
            if(state2 == READY){
                state2 = RUNNING;
                qleft = quantum;
            }
        }
        if ((state2 == RUNNING) && (qleft == 0) ) {
            state2 = READY;
            if(state1 == READY){
                state1 = RUNNING;
                qleft = quantum;
            }
        }
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            state1 = RUNNING;
            qleft = quantum;

        }
        /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
            qleft = quantum;
        }
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
            qleft = quantum;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        qleft--;                   /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }
}
