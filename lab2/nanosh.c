/*
* Christopher Nash
* Lab2 - Nano Shell
* CS 3100 - Operating Systems
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int debug = 0;

void cmdExit(int argc, char **argv) {
    if(debug == 1) printf("Executing EXIT\n");

    if (argc != 1) {
        errno=EINVAL;
        perror("Error");
        return;
    }

    exit(0);
}

void cmdPwd(int argc, char **argv) {
    if(debug == 1) printf("Executing PWD\n");

    if (argc != 1) {
        errno=EINVAL;
        perror("Error");
        return;
    }

    char thePwd[FILENAME_MAX];
    getcwd(thePwd, sizeof(thePwd));
    printf("%s\n", thePwd);

    // I could use exec?
//    execvp("pwd", argv);
}

void cmdCd(int argc, char **argv) {
    if(debug == 1) printf("Executing CD\n");
    if(debug == 1) printf("arg count %d\n", argc);

    if (argc == 2) {
        if(debug == 1) printf("Change to directory\n");
        int returnCode = chdir(argv[1]);
        if (returnCode == -1) {
            if(debug == 1) printf("An error occurred with changing directory\n");
            perror("Error");
        }
    } else if (argc == 1) {
        if(debug == 1) printf("Change to home\n");
        chdir(getenv("HOME"));
    } else  {
        errno=EINVAL;
        perror("Error");
    }
}

void cmdOther(int argc, char **argv) {
    if(debug == 1) printf("Executing OTHER\n");

    int returnCode;
    int status;

    char *cmd = argv[0];

    returnCode = fork();
    if (returnCode > 0) { // I am the parent
        if(debug == 1) printf("Parent: waiting on pid %d\n", returnCode);
        waitpid(returnCode, &status, 0);
        if(debug == 1) printf("Parent: child has ended with status %d\n", WEXITSTATUS(status));
        return;
    } else if (returnCode == 0) { // I am the child
        if(debug == 1) printf("Child: I am pid %d about to exec() %s\n", getpid(), cmd);
        execvp(cmd, argv);
        perror("Child: execvp() failed:");
        exit(1);
    } else { // an error occured, no child created
        perror("Parent: a bad thing happened:");
        exit(1);
    }

}

// getParameters returns the argc, the number of words found in cmd
//  while populating argv with pointers to each word
int getParameters(char *cmd, char **argv) {
	char *token;
	int argc = 0;
	token = strtok(cmd, " \t\n");
	while (token != NULL) {
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;		// set last + 1 argument to NULL
	return argc;
}

int main(int argc, char **argv) {

	char cmd[1024];
	char *rc;
	int myArgc = 0;
	char *myArgv[1000];

	while (1) {
		printf("nanosh: ");
		fflush(stdout);
		rc = fgets(cmd, sizeof(cmd), stdin);
		if (rc == NULL) {
			exit(0);
		}
		myArgc = getParameters(cmd, myArgv);

		// if no words typed: restart loop
		if (myArgc == 0) {			
			continue;
		}

		if (strcmp(myArgv[0], "exit") == 0) {
			cmdExit(myArgc, myArgv);
			continue;
		} else if (strcmp(myArgv[0], "pwd") == 0) {
            cmdPwd(myArgc, myArgv);
            continue;
        } else if (strcmp(myArgv[0], "cd") == 0) {
            cmdCd(myArgc, myArgv);
            continue;
        } else {
            cmdOther(myArgc, myArgv);
            continue;
        }

		// add if statements here for the other internal commands
		//   and a default action that calls a function to fork()
		//   and exec() while the parent issues waitpid()
	}

	return 0;
} 
