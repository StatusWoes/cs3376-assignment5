// File pipe4.cpp
// Author: Timothy Shiveley
// Date: 4/1/2017
// Purpose: This program executes ls -ltr | grep 3376, by dividing the two precesses between parent and child

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>
using namespace std;

int main (int argc, char **argv) {
	int status, childpid, childpid2;
	char *cat_args[] = { (char *) "ls", (char *) "-ltr", (char *) NULL};
	char *grep_args[] = { (char *) "grep", (char *) "3376", (char *) NULL};
	char *wc_args[] = { (char *) "wc", (char *) "-l", (char *) NULL};
	int pipes[2];
	int pipe2[2];
	pipe(pipes);
	pipe(pipe2);

	if((childpid = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}	

	if (childpid == 0){
		if ((childpid2 = fork()) == -1 ){
			perror("Error creating a child process");
			exit(1);
		}
		if (childpid2 == 0) {
			dup2(pipes[1], 1);
			close(pipes[0]);
			close(pipes[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			execvp(*cat_args, cat_args);
			exit(0);
		} else {
			dup2(pipe2[1], 1);
			dup2(pipes[0], 0);
			close(pipes[0]);
			close(pipes[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			execvp(*grep_args, grep_args);
			exit(0);
		}
	} else {
		dup2(pipe2[0], 0);
		close(pipes[0]);
		close(pipes[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(*wc_args, wc_args);
	}
	return(0);
}
