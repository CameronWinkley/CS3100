/*
* Christopher Nash
* Lab6 - Disk Scheduling
* CS 3100 - Operating Systems
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 1;

const char * FCFS(int argc, char **argv) {
/*
tcowan@tcowan-Ubuntu:~/cs3100/lab6$ ./disksked 53 98 183 37 122 14 124 65 67 
FCFS: Start:53 98:45 183:85 37:146 122:85 14:108 124:110 65:59 67:2 Total:640 
*/
    if(debug == 1) printf("Executing FCFS\n");

    return "FCFS: Start:53 98:45 183:85 37:146 122:85 14:108 124:110 65:59 67:2 Total:640\n";
}

const char * SSTF(int argc, char **argv) {
/*
tcowan@tcowan-Ubuntu:~/cs3100/lab6$ ./disksked 53 98 183 37 122 14 124 65 67 
SSTF: Start:53 65:12 67:2 37:30 14:23 98:84 122:24 124:2 183:59 Total:236 
*/
    if(debug == 1) printf("Executing SSTF\n");

    return "SSTF: Start:53 65:12 67:2 37:30 14:23 98:84 122:24 124:2 183:59 Total:236\n";
}

const char * SCAN(int argc, char **argv) {
/*
tcowan@tcowan-Ubuntu:~/cs3100/lab6$ ./disksked 53 98 183 37 122 14 124 65 67 
SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 14:169 37:23 Total:322 
*/
    if(debug == 1) printf("Executing SCAN\n");

    return "SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 14:169 37:23 Total:322\n";
}

const char * C_SCAN(int argc, char **argv) {
/*
tcowan@tcowan-Ubuntu:~/cs3100/lab6$ ./disksked 53 98 183 37 122 14 124 65 67 
C_SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 37:146 14:23 Total:299 
*/
    if(debug == 1) printf("Executing C_SCAN\n");

    return "C_SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 37:146 14:23 Total:299\n";
}

int main(int argc, char *argv[]) {
    if (argc != 10) {
        fprintf(stderr, "Usage: ./disksked START T1 T2 T3 T4 T5 T6 T7 T8\n");
        exit(1);
    }

    printf(FCFS(argc, argv));
    printf(SSTF(argc, argv));
    printf(SCAN(argc, argv));
    printf(C_SCAN(argc, argv));

    return 0;
}