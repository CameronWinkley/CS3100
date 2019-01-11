/*
 * Christopher Nash
 * Lab4 - Errors, errors, everywhere...
 * CS 3100 - Operating Systems
 *
 * null.c
 *
 * Write a small program called null that creates a pointer to an integer, sets the pointer to NULL, and then attempts
 * to set the integer to zero through the pointer. This program should crash when you run it.
 * Compile it with make null, which will compile null.c, creating null and running valgrind, a
 * memory utility that will identify potential memory bugs in your code. Notice what it tells you about
 * null. Run the program manually to see if it crashes.
 *
 * After you have successfully written a crashing null program, type gdb ./null, then run, then quit,
 * then y. These commands will execute null under the GNU debugger. The debugger will identify the
 * line in your program that caused the abnormal termination of null.
 */

#include <stdlib.h>

int main(int argc, char **argv) {
    int *someInt;
    *someInt = NULL;
    *someInt = 0;
}
