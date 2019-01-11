/*
 * Christopher Nash
 * Lab4 - Errors, errors, everywhere...
 * CS 3100 - Operating Systems
 *
 * bounds.c
 *
 * Write a small program called bounds that allocates memory for 100 integers (sizeof(int) * 100)
 * using malloc() and saves the pointer from malloc() in a pointer variable called ptr. Then set
 * ptr[100] = 0 and see what happens when you run this program. make bounds will compile your
 * code and run valgrind. Review the valgrind report. Run the program manually to see if it crashes.
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int *ptr;
    ptr = (int *) malloc(sizeof(int) * 100);
    ptr[100] = 0;
}