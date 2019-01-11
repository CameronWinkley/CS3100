/*
 * Christopher Nash
 * Lab4 - Errors, errors, everywhere...
 * CS 3100 - Operating Systems
 *
 * datagone.c
 *
 * Write a small program called datagone that allocates an array of integers with malloc() as in
 * bounds, saves the pointer in a pointer variable called ptr, frees the storage with free(), then prints
 * the 51st integer with printf("%d\n", ptr[50]);. make datagone will compile your code
 * and run valgrind. Review the valgrind report. Run the program manually to see if it crashes.
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int *ptr;
    ptr = (int *) malloc(sizeof(int) * 100);
    free(ptr);

    printf("%d\n", ptr[50]);
}