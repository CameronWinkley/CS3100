/*
 * Christopher Nash
 * Lab4 - Errors, errors, everywhere...
 * CS 3100 - Operating Systems
 *
 * nofree.c
 *
 * Write a small program called nofree that allocates 1024 bytes of memory using malloc(), then exits
 * the program without calling free(). Compile it with make nofree, which will compile nofree.c,
 * creating nofree and running valgrind. Review the valgrind report. Run the program manually to
 * see if it crashes.
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int *pointer;
    pointer = (int *) malloc(1024);
    // Don't call free(pointer)
}