all: assign2 assign1-0

assign1-0: assign1-0.c pslibrary.c
        cc -o assign1-0 assign1-0.c pslibrary.c

assign2: assign2.c pslibrary.c
        cc -o assign2 assign2.c pslibrary.c

clean:
        rm -f assign2-0 assign2 *.o

run0:
        assign2-0 0 1 2 3 4 5 6

runa:
        assign2 0 2 5 9 4 8 7
