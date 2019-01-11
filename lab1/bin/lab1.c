/*
* Christopher Nash
* Lab1 - Code in C
* CS 3100 - Operating Systems
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>


// usage() prints a standard usage statement
void usage(char *path) {
    fprintf(stderr, "Usage: %s -n NAME\n", path);
}

int main(int argc, char *argv[]) {
    char *name;

    if (argc != 3) {
        usage(argv[0]);
        exit(1);
    }

    // read the input parameter and exit on error
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n':
                name = optarg;
                break;
            default:
                usage(argv[0]);
                exit(1);
        }
    }

    // output on STDOUT "Welcome to Lab 1, written by USERNAME"
    printf("Welcome to Lab 1, written by %s\n", name);

    // output on STDOUT "Hostname: <hostname>"
    char hostname[1024];
    gethostname(hostname, 1024);
    printf("Hostname: %s\n", hostname);

    // output on STDOUT "PID and PPID: nnnnn/nnnnn"
    printf("PID and PPID: %u/%u\n", getpid(), getppid());

    // output on STDOUT "Program: <pathToThisProgram>

    // This option gets the "Current Working Directory" and outputs it.
    // I would think this is more useful more often, but it doesn't appear to be what the instructor is testing for.
//    char pathToThisProgram[FILENAME_MAX];
//    getcwd(pathToThisProgram, sizeof(pathToThisProgram));
//    printf("Program: %s\n", pathToThisProgram);

    // This option gets the first argument of the call to launch this application, which is the name of the program.
    // This appears to be what the instructor is testing for.
    printf("Program: %s\n", argv[0]);

    return 0;
}

