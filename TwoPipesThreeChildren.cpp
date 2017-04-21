// File TwoPipesThreeChildren.cpp
// Author: Timothy Shiveley
// Date: 4/1/2017
// Purpose: This program executes ls -ltr | grep 3376 | wc -1, by dividing the two precesses between parent and child

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>
using namespace std;

int main (int argc, char **argv) {
	int status, childpid1, childpid2, childpid3;
	char *cat_args[] = { (char *) "ls", (char *) "-ltr", (char *) NULL};
	char *grep_args[] = { (char *) "grep", (char *) "3376", (char *) NULL};
	char *wc_args[] = { (char *) "wc", (char *) "-l", (char *) NULL};
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);

	if((childpid1 = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}	

	if (childpid1 == 0){
		if ((childpid2 = fork()) == -1 ){
			perror("Error creating a child process");
			exit(1);
		}
		if (childpid2 == 0) {
			if ((childpid3 = fork()) == -1) {
				perror("Error creating a child process");
				exit(1);
			}
			if (childpid3 == 0) {	
				dup2(pipe1[1], 1);
				close(pipe1[0]);
				close(pipe1[1]);
				close(pipe2[0]);
				close(pipe2[1]);
				execvp(*cat_args, cat_args);
				exit(0);
			} else {
				dup2(pipe2[1], 1);
				dup2(pipe1[0], 0);
				close(pipe1[0]);
				close(pipe1[1]);
				close(pipe2[0]);
				close(pipe2[1]);
				execvp(*grep_args, grep_args);
				exit(0);
			}
		} else {
			dup2(pipe2[0], 0);
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			execvp(*wc_args, wc_args);
		}
	}
	sleep(1);
	return(0);
}
