/*
* Christopher Nash
* Lab5 - Threads and synchronization
*    (Original template by Ted Cowan)
* CS 3100 - Operating Systems
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

WINDOW *topwin, *botwin;

void *countUp(void *ptr) {
    int i = 0, key;

    while (1) {
        // Lock the mutex
        pthread_mutex_lock(ptr);

        wprintw(topwin, "Count up: %d\n", i++);
        wrefresh(topwin);
        key = getch();

        // Unlock the mutex
        pthread_mutex_unlock(ptr);

        if (key != ERR) {
            break;
        }
    }

    // Once the loop is done, exit the thread
    pthread_exit(NULL);
    return NULL;
}

void *countDown(void *ptr) {
    int i = 0, key;

    while (1) {
        // Lock the mutex
        pthread_mutex_lock(ptr);

        wprintw(botwin, "Count down: %d\n", i--);
        wrefresh(botwin);
        key = getch();

        // Unlock the mutex
        pthread_mutex_unlock(ptr);

        if (key != ERR) {
            break;
        }
    }

    // Once the loop is done, exit the thread
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char **argv) {

    int tlines, blines;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    tlines = LINES / 2 - 1;
    blines = LINES - tlines - 1;

    topwin = newwin(tlines, COLS, 0, 0);
    scrollok(topwin, TRUE);
    botwin = newwin(blines, COLS, tlines + 1, 0);
    scrollok(botwin, TRUE);
    move(tlines, 0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        wattron(topwin, COLOR_PAIR(1));
        wattron(botwin, COLOR_PAIR(2));
        wattron(stdscr, COLOR_PAIR(3));
    }
    hline('_', 200);
    refresh();

    // Create a mutex to use for locking the ncurses calls
    pthread_mutex_t ncurses = PTHREAD_MUTEX_INITIALIZER;

    // Create two threads: One which will count up, one which will count down
    pthread_t upThread;
    pthread_t downThread;

    // Create and launch the two threads
    pthread_create(&upThread, NULL, countUp, &ncurses);
    pthread_create(&downThread, NULL, countDown, &ncurses);

    // Wait for both threads to finish and exit before moving on
    pthread_join(upThread, NULL);
    pthread_join(downThread, NULL);

    // Wait 3 seconds then close the window and exit
    usleep(3000000);
    endwin();

    return 0;
}
