#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pslibrary.h"

//Part 0
void part0(char *s1,char *s2){
   strcpy(s1,"RRwwwwwRRRRRRRRR");
   strcpy(s2 ,"rrRRRRwwwwwwwwrrRRRRRRR");

}

//Display
//Prints the strings
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

//fcfsa
//Creates proper string given parameter.
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

    //Inserts small r
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
