/*
 * Christopher Nash
 * Lab4 - Errors, errors, everywhere...
 * CS 3100 - Operating Systems
 *
 * freebad.c
 *
 * Write a small program called freebad that allocates an array of integers with malloc() as in
 * bounds, saves the pointer in a pointer variable called ptr, then frees the storage with free(ptr+50),
 * which instructs free() to free memory from the middle of the allocated region. make freebad will
 * compile your code and run valgrind. Review the valgrind report. Run the program manually to see
 * if it crashes.
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int *ptr;
    ptr = (int *) malloc(sizeof(int) * 100);
    free(ptr+50);
}