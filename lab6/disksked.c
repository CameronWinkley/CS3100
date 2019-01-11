/*
* Christopher Nash
* Lab6 - Disk Scheduling
* CS 3100 - Operating Systems
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int debug = 1;
int REALLY_BIG = 20000;
int REALLY_SMALL = -20000;

/**
 * First Come First Served (FCFS)
 *
 * Tracks are processed in the order received, from the starting track to each of the 8 tracks in order on the
 * command-line from left to right.
 *
 * Example:
 * disksked 53 98 183 37 122 14 124 65 67 
 * FCFS: Start:53 98:45 183:85 37:146 122:85 14:108 124:110 65:59 67:2 Total:640 
 */
const char* FCFS(int argc, char **argv) {
    int total = 0;
    int values[10];
    int distance[10];

    // Populate the values array. Note: the 0th element will always be "0" because atoi can't parse "disksked"
    for (int i = 0; i <= 9; ++i) {
        values[i] = atoi(argv[i]);
    }

    // Skip the first 2 values ("disksked" and our Start)
    for (int i = 2; i <= 9; ++i) {
        distance[i] = abs(values[i] - values[i-1]);
        total += distance[i];
    }

    printf("FCFS: Start:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d Total:%d\n",
           values[1],
           values[2], distance[2],
           values[3], distance[3],
           values[4], distance[4],
           values[5], distance[5],
           values[6], distance[6],
           values[7], distance[7],
           values[8], distance[8],
           values[9], distance[9],
           total);
    return 0;
}

/**
 * Copied directly from https://stackoverflow.com/questions/4710795/finding-the-smallest-number-in-an-array-of-integers
 */
int smallest(int* values, int count) {
    int smallest_value = INT_MAX;
    for (int i = 0; i < count; ++i) {
        if (values[i] < smallest_value) {
            smallest_value = values[i];
        }
    }
    return smallest_value;
}

/**
 * Copied directly from https://stackoverflow.com/questions/15094834/check-if-a-value-exist-in-a-array
 */
bool isValueInArray(int val, int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val)
            return true;
    }
    return false;
}

/**
 * Modified from the answer https://stackoverflow.com/questions/8199403/how-to-check-if-an-array-has-any-duplicates
 */
bool arrayHasDuplicates(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

/**
 *  Shortest Seek Time First (SSTF)
 *
 *  Tracks are processed from the absolute value of the shortest distance from the current track, beginning with the
 *  starting track.
 *
 *  If there are two tracks that are equal distance from the current track, choose the first one (the earliest one in
 *  the list) and move there first.
 *
 *  Example:
 *  disksked 53 98 183 37 122 14 124 65 67 
 *  SSTF: Start:53 65:12 67:2 37:30 14:23 98:84 122:24 124:2 183:59 Total:236 
 */
const char* SSTF(int argc, char **argv) {
    int total = 0;

    int values[10];

    int orderProcessing[15] = {REALLY_BIG};
    int distance[10];

    // Populate the values array. Note: the 0th element will always be "0" because atoi can't parse "disksked"
    for (int i = 0; i <= 9; ++i) {
        values[i] = atoi(argv[i]);
    }

//    printf("Array has duplicates? (1=true) %i \n", arrayHasDuplicates(values, sizeof(values)));

    // Set the starting value
    orderProcessing[1] = values[1];
    values[1] = REALLY_BIG;

    for (int i = 1; i <= 9; i++) {

        int lowest = REALLY_BIG;
        int lowest_index;

        int comparing = orderProcessing[i];

        for (int j = 1; j <= 9; j++) {
            // Skip ourselves
            int inner = values[j];
            int abs_val = abs(inner - comparing);
//            printf("absolute value comp: i=%d j=%d ===> abs=%d\n", comparing, inner, abs_val);

            if (abs_val < lowest
//                    && !isValueInArray(inner, orderProcessing, sizeof(orderProcessing))) {
                ) {
//                printf("New lowest value: %d at index: %d\n", abs_val, j);
                lowest = abs_val;
                lowest_index = j;
            }
        }

//        printf("FINAL lowest value: %d at index: %d\n", lowest, lowest_index);

        orderProcessing[i+1] = values[lowest_index];
        distance[i+1] = lowest;
        values[lowest_index] = REALLY_BIG;
    }

    total = distance[2]+distance[3]+distance[4]+distance[5]+distance[6]+distance[7]+distance[8]+distance[9];

//    return "SSTF: Start:53 65:12 67:2 37:30 14:23 98:84 122:24 124:2 183:59 Total:236\n";

    printf("SSTF: Start:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d Total:%d\n",
           orderProcessing[1],
           orderProcessing[2], distance[2],
           orderProcessing[3], distance[3],
           orderProcessing[4], distance[4],
           orderProcessing[5], distance[5],
           orderProcessing[6], distance[6],
           orderProcessing[7], distance[7],
           orderProcessing[8], distance[8],
           orderProcessing[9], distance[9],
           total);
    return 0;
}

void printArray(char *arrayName, int *arr, int size) {
    printf("Array %s: ", arrayName);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void determineLarger(int value, int valuePosition, int *comparingArr, int comparingSize, int *largerArray) {
//    printf("Determining Larger. Size of Comparing Array: %d\n", sizeof(comparingArr) / sizeof(int));
    for (int i = 0; i < comparingSize; i++) {
        if (value <= comparingArr[i] && i != valuePosition) { // If its "me" then don't add it, but allow duplicates through
            largerArray[i] = comparingArr[i];
        }
    }
}

void determineSmaller(int value, int *comparingArr, int comparingSize, int *smallerArray) {
    for (int i = 0; i < comparingSize; i++) {
        if (value > comparingArr[i]) {
            smallerArray[i] = comparingArr[i];
        }
    }
}

/**
 * Copied directly from https://stackoverflow.com/questions/3893937/c-array-sorting-tips
 */
int compare(const void* a, const void* b) {
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

/**
 * SCAN
 *
 * Re-order the tracks, so that from the current track, move to higher numbered tracks first, then reverse to the lower
 * tracks. Process all of the higher numbered tracks in ascending order, then move to the lowest numbered track and
 * process the lower numbered tracks in ascending order.
 *
 * Do not move to track 0 or to the end of the disk during your scan. Some of you might recognize this variant of the
 * SCAN algorithm as the LOOK algorithm.
 *
 * Example:
 * disksked 53 98 183 37 122 14 124 65 67 
 * SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 14:169 37:23 Total:322
 */
const char* SCAN(int argc, char **argv) {
    int total = 0;
    int values[10] = {0};

    int orderProcessing[15] = {REALLY_BIG};
    int distance[15] = {0};

    int largerThanStart[10] = {REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG,
                               REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG};
    int smallerThanStart[10] = {REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG,
                                REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG};;

    // Populate the values array. Note: the 0th element will always be "0" because atoi can't parse "disksked"
    for (int i = 0; i <= 9; ++i) {
        values[i] = atoi(argv[i]);
    }
    values[0] = REALLY_BIG;

    // Set the starting value
    orderProcessing[1] = values[1];

//    printf("Size of values: %d\n", sizeof(values) / sizeof(int));

//    printArray("Values", values, sizeof(values) / sizeof(int));
//    printArray("Order Processing", orderProcessing, sizeof(orderProcessing) / sizeof(int));
//    printArray("Distance", distance, sizeof(distance) / sizeof(int));

    determineLarger(orderProcessing[1], 1, values, sizeof(values) / sizeof(int), largerThanStart);
    determineSmaller(orderProcessing[1], values, sizeof(values) / sizeof(int), smallerThanStart);

//    printArray("Larger", largerThanStart, sizeof(largerThanStart) / sizeof(int));
//    printArray("Smaller", smallerThanStart, sizeof(smallerThanStart) / sizeof(int));

    qsort(largerThanStart, sizeof(largerThanStart) / sizeof(int), sizeof(int), compare);
    qsort(smallerThanStart, sizeof(smallerThanStart) / sizeof(int), sizeof(int), compare);
//
//    printArray("Larger Sorted", largerThanStart, sizeof(largerThanStart) / sizeof(int));
//    printArray("Smaller Sorted", smallerThanStart, sizeof(smallerThanStart) / sizeof(int));

    values[1] = REALLY_SMALL;

    // >>>>>> then got to the lowest track then >>>> through any that haven't been read

    // Iterate over the larger than array
    int startNextChunkAt = 2; // We will always start at least at the second slot after "disksked" and our Start
    for (int i = 0; i <= 9; ++i) {
        if (largerThanStart[i] != REALLY_BIG) {
            orderProcessing[i+2] = largerThanStart[i]; // Add 2 values to skip our "disksked" and our Start
            distance[i+2] = abs(orderProcessing[i+1] - orderProcessing[i+2]);
            startNextChunkAt++;
        }
    }

//    printf("Starting next chunk at position: %d\n", startNextChunkAt);

    // Iterate over the smaller than array
    for (int i = 0; i <= 9; ++i) {
        if (smallerThanStart[i] != REALLY_BIG) {
            int position = i+startNextChunkAt;
            orderProcessing[position] = smallerThanStart[i]; // Add 2 values to skip our "disksked" and our Start
            distance[i+startNextChunkAt] = abs(orderProcessing[position-1] - orderProcessing[position]);
        }
    }

//    printArray("Values", values, sizeof(values) / sizeof(int));
//    printArray("Order Processing", orderProcessing, sizeof(orderProcessing) / sizeof(int));
//    printArray("Distance", distance, sizeof(distance) / sizeof(int));

    total = distance[2]+distance[3]+distance[4]+distance[5]+distance[6]+distance[7]+distance[8]+distance[9];

//    return "SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 14:169 37:23 Total:322\n";

    printf("SCAN: Start:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d Total:%d\n",
           orderProcessing[1],
           orderProcessing[2], distance[2],
           orderProcessing[3], distance[3],
           orderProcessing[4], distance[4],
           orderProcessing[5], distance[5],
           orderProcessing[6], distance[6],
           orderProcessing[7], distance[7],
           orderProcessing[8], distance[8],
           orderProcessing[9], distance[9],
           total);
    return 0;
}

/**
 * Circular SCAN (C-SCAN)
 *
 * Re-order the tracks, so that from the current track, move to higher numbered tracks first in ascending order (as in
 * SCAN), but then reverse direction and process the lower numbered tracks in descending order.
 *
 * Some might recognize this variant as the C-LOOK algorithm.
 *
 * Example:
 * tcowan@tcowan-Ubuntu:~/cs3100/lab6$ ./disksked 53 98 183 37 122 14 124 65 67 
 * C_SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 37:146 14:23 Total:299 
 */
const char* C_SCAN(int argc, char **argv) {
    int total = 0;
    int values[10] = {0};

    int orderProcessing[15] = {REALLY_BIG};
    int distance[15] = {0};

    int largerThanStart[10] = {REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG,
                               REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG};
    int smallerThanStart[10] = {REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG,
                                REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG, REALLY_BIG};;

    // Populate the values array. Note: the 0th element will always be "0" because atoi can't parse "disksked"
    for (int i = 0; i <= 9; ++i) {
        values[i] = atoi(argv[i]);
    }
    values[0] = REALLY_BIG;

    // Set the starting value
    orderProcessing[1] = values[1];

//    printf("Size of values: %d\n", sizeof(values) / sizeof(int));

//    printArray("Values", values, sizeof(values) / sizeof(int));
//    printArray("Order Processing", orderProcessing, sizeof(orderProcessing) / sizeof(int));
//    printArray("Distance", distance, sizeof(distance) / sizeof(int));

    determineLarger(orderProcessing[1], 1, values, sizeof(values) / sizeof(int), largerThanStart);
    determineSmaller(orderProcessing[1], values, sizeof(values) / sizeof(int), smallerThanStart);

//    printArray("Larger", largerThanStart, sizeof(largerThanStart) / sizeof(int));
//    printArray("Smaller", smallerThanStart, sizeof(smallerThanStart) / sizeof(int));

    qsort(largerThanStart, sizeof(largerThanStart) / sizeof(int), sizeof(int), compare);
    qsort(smallerThanStart, sizeof(smallerThanStart) / sizeof(int), sizeof(int), compare);
//
//    printArray("Larger Sorted", largerThanStart, sizeof(largerThanStart) / sizeof(int));
//    printArray("Smaller Sorted", smallerThanStart, sizeof(smallerThanStart) / sizeof(int));

    values[1] = REALLY_SMALL;

    // >>>>>> then <<<<<<<<

    // Iterate over the larger than array
    int startNextChunkAt = 2; // We will always start at least at the second slot after "disksked" and our Start
    for (int i = 0; i <= 9; ++i) {
        if (largerThanStart[i] != REALLY_BIG) {
            orderProcessing[i+2] = largerThanStart[i]; // Add 2 values to skip our "disksked" and our Start
            distance[i+2] = abs(orderProcessing[i+1] - orderProcessing[i+2]);
            startNextChunkAt++;
        }
    }

//    printf("Starting next chunk at position: %d\n", startNextChunkAt);

    // Iterate over the smaller than array
    for (int i = 9; i >= 0; --i) {
        if (smallerThanStart[i] != REALLY_BIG) {
            int position = startNextChunkAt;
            orderProcessing[position] = smallerThanStart[i];
            distance[startNextChunkAt] = abs(orderProcessing[position-1] - orderProcessing[position]);
            startNextChunkAt++;
        }
    }

//    printArray("Values", values, sizeof(values) / sizeof(int));
//    printArray("Order Processing", orderProcessing, sizeof(orderProcessing) / sizeof(int));
//    printArray("Distance", distance, sizeof(distance) / sizeof(int));

    total = distance[2]+distance[3]+distance[4]+distance[5]+distance[6]+distance[7]+distance[8]+distance[9];

//    return "C_SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 37:146 14:23 Total:299\n";

    printf("C_SCAN: Start:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d %d:%d Total:%d\n",
           orderProcessing[1],
           orderProcessing[2], distance[2],
           orderProcessing[3], distance[3],
           orderProcessing[4], distance[4],
           orderProcessing[5], distance[5],
           orderProcessing[6], distance[6],
           orderProcessing[7], distance[7],
           orderProcessing[8], distance[8],
           orderProcessing[9], distance[9],
           total);
    return 0;
}

/**
 An example run:
    disksked 53 98 183 37 122 14 124 65 67 
    FCFS: Start:53 98:45 183:85 37:146 122:85 14:108 124:110 65:59 67:2 Total:640 
    SSTF: Start:53 65:12 67:2 37:30 14:23 98:84 122:24 124:2 183:59 Total:236 
    SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 14:169 37:23 Total:322 
    C_SCAN: Start:53 65:12 67:2 98:31 122:24 124:2 183:59 37:146 14:23 Total:299 
 */
int main(int argc, char *argv[]) {
    if (argc != 10) {
        fprintf(stderr, "Usage: ./disksked START T1 T2 T3 T4 T5 T6 T7 T8\n");
        exit(1);
    }

    FCFS(argc, argv);
    SSTF(argc, argv);
    SCAN(argc, argv);
    C_SCAN(argc, argv);

    return 0;
}