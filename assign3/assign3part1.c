#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>


#define PAGE 4096
#define BUFSIZE 5000

int getOffset(unsigned long num){
    return num & 0x007f;
}

int virtualTable(unsigned long num){
    if(num < 128){
        return 0;
    }
    if(num < 256){
        return 1;
    }
    if(num < 384){
        return 2;
    }
    if(num < 512){
        return 3;
    }
    if(num < 640){
        return 4;
    }
    if(num < 768){
        return 5;
    }
    if(num < 896){
        return 6;
    }
    return 7;
}

int physicalTable(int num){
    switch(num){
        case 0:
            return 2;
        case 1:
            return 4;
        case 2:
            return 1;
        case 3:
            return 7;
        case 4:
            return 3;
        case 5:
            return 5;
        case 6:
            return 6;
        default:
        return -1;
    }
}

void openFile(char * inFile){
    int fdin, fdout, i, fsize;
    unsigned long fileSize,checkSize,offset,normal, total, vpg, ppg;
    unsigned long * mapping;
    unsigned long *mapout;
    struct stat size;

    stat(inFile, &size);

    fdin = open (inFile, O_RDONLY);
    if(fdin == -1){
        printf("Error Opening.\n");
        exit (-1);
    }

    fileSize = size.st_size;
    checkSize = (fileSize + (PAGE - 1)) & ~(PAGE -1);


    mapping = (unsigned long*) mmap(0, checkSize, PROT_READ, MAP_PRIVATE, fdin, 0);

    char* outFile = "output-part1";
    fdout = open(outFile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fdout == -1){
        printf("Error opening output file. \n");
        exit(-1);
    }

    lseek(fdout, fileSize-1, SEEK_SET);
    write(fdout,"",1);
    mapout = (unsigned long*) mmap(0, checkSize, PROT_READ | PROT_WRITE, MAP_SHARED, fdout,0);

    fsize = fileSize / sizeof(unsigned long);
    for(i = 0; i < fsize; i++){
        vpg = virtualTable(mapping[i]);
        ppg = physicalTable(vpg);
        normal = ppg << 7;
        offset = getOffset(mapping[i]);
        total = offset + normal;
        mapout[i] = total;
    }
}

int main(int argc, char** argv) {

    if(argc != 2){
        printf("Please include a sequence file to run program.\n");
        return -1;
    }

    char* sFile;
    sFile = argv[1];
    openFile(sFile);
}
