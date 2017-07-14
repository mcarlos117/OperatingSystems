all: assign1 assign1-0

assign1-0: assign1-0.c pslibrary.c
        cc -o assign1-0 assign1-0.c pslibrary.c

assign1: assign1.c pslibrary.c
        cc -o assign1 assign1.c pslibrary.c

clean:
        rm -f assign1-0 assign1 *.o

run0:
        assign1-0 0 1 2 3 4 5 6

runa:
        assign1 0 2 5 9 4 8 7
