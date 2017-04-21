// File DynPipe.cpp
// Author: Timothy Shiveley
// Date: 4/1/2017
// Purpose: This program executes ls -ltr | grep 3376 | wc -1, by dividing the two precesses between parent and child
// argc has the number of arguments to the file, the name of the file is included in the number
// argv stores the actual arguments, starting at argv[1]

#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
using namespace std;

int run2com(char**, int []);
int run3com(char**, int [], int []);
int run4com(char**, int [], int [], int []);
int run5com(char**, int [], int [], int [], int []);
void tokenize(char* [], char*);

int main (int argc, char **argv) {
	int pipe1[2], pipe2[2], pipe3[2], pipe4[2];
	
	if ((argc - 2) <= 0 || (argc - 2) >= 5){
		cout << "Error, Wrong number of parameters. Enter between 2 and 5 commands." << endl;
	}else if ((argc - 2) == 1) {
		pipe(pipe1);
		run2com(argv, pipe1);
	}else if ((argc - 2) == 2) {
		pipe(pipe1);
		pipe(pipe2);
		run3com(argv, pipe1, pipe2);
	}else if ((argc - 2) == 3) {
		pipe(pipe1);
		pipe(pipe2);
		pipe(pipe3);
		run4com(argv, pipe1, pipe2, pipe3);
	}else {
		pipe(pipe1);
		pipe(pipe2);
		pipe(pipe3);
		pipe(pipe4);
		run5com(argv, pipe1, pipe2, pipe3, pipe4);
	}
	return 0;
}

int run2com(char **argv, int pipe1fd[]) {
	string cmd1_str, cmd2_str;
	int childpid1, numargs1, numargs2 = 0;
	char **cmd1_args, **cmd2_args;
	cmd1_str = argv[1];
	cmd2_str = argv[2];
	numargs1 = count(cmd1_str.begin(), cmd1_str.end(), ' ');
	numargs2 = count(cmd2_str.begin(), cmd2_str.end(), ' ');
	cmd1_args = new (nothrow) char*[numargs1 + 2];
	cmd2_args = new (nothrow) char*[numargs2 + 2];
	tokenize(cmd1_args, argv[1]);
	tokenize(cmd2_args, argv[2]);

	if((childpid1 = fork()) == -1){
		perror("Error creating a child process.");
		exit(1);
	}
	
	if (childpid1 == 0) {
		dup2(pipe1fd[1], 1);
		close(pipe1fd[0]);
		close(pipe1fd[1]);
		execvp(*cmd1_args, cmd1_args);
		exit(0);
	} else {
		dup2(pipe1fd[0], 0);
		close(pipe1fd[0]);
		close(pipe1fd[1]);
		execvp(*cmd2_args, cmd2_args);
	}
	return 0;
}

int run3com(char **argv, int pipe1fd[], int pipe2fd[]) {
	string cmd1_str, cmd2_str, cmd3_str;
	int childpid1, childpid2, numargs1, numargs2, numargs3 = 0;
	char **cmd1_args, **cmd2_args, **cmd3_args;
	cmd1_str = argv[1];
	cmd2_str = argv[2];
	cmd3_str = argv[3];
	numargs1 = count(cmd1_str.begin(), cmd1_str.end(), ' ');
	numargs2 = count(cmd2_str.begin(), cmd2_str.end(), ' ');
	numargs3 = count(cmd3_str.begin(), cmd3_str.end(), ' ');
	cmd1_args = new (nothrow) char*[numargs1 + 2];
	cmd2_args = new (nothrow) char*[numargs2 + 2];
	cmd3_args = new (nothrow) char*[numargs3 + 2];
	tokenize(cmd1_args, argv[1]);
	tokenize(cmd2_args, argv[2]);
	tokenize(cmd3_args, argv[3]);

	if((childpid1 = fork()) == -1){
		perror("Error creating a child process.");
		exit(1);
	}
	
	if (childpid1 == 0) {
		if((childpid2 = fork()) == -1){
			perror("Error creating a child process.");
			exit(1);
		}
		if (childpid2 == 0) {
			dup2(pipe1fd[1], 1);
			close(pipe1fd[0]);
			close(pipe1fd[1]);
			close(pipe2fd[0]);
			close(pipe2fd[1]);
			execvp(*cmd1_args, cmd1_args);
			exit(0);
		}else {	
			dup2(pipe1fd[0], 0);
			dup2(pipe2fd[1], 1);
			close(pipe1fd[0]);
			close(pipe1fd[1]);
			close(pipe2fd[0]);
			close(pipe2fd[1]);
			execvp(*cmd2_args, cmd2_args);
			exit(0);
		}
	} else {
		dup2(pipe2fd[0], 0);
		close(pipe1fd[0]);
		close(pipe1fd[1]);
		close(pipe2fd[0]);
		close(pipe2fd[1]);
		execvp(*cmd3_args, cmd3_args);
	}
	return 0;
}

int run4com(char **argv, int pipe1fd[], int pipe2fd[], int pipe3fd[]) {
	string cmd1_str, cmd2_str, cmd3_str, cmd4_str;
	int childpid1, childpid2, childpid3, numargs1, numargs2, numargs3, numargs4 = 0;
	char **cmd1_args, **cmd2_args, **cmd3_args, **cmd4_args;
	cmd1_str = argv[1];
	cmd2_str = argv[2];
	cmd3_str = argv[3];
	cmd4_str = argv[4];
	numargs1 = count(cmd1_str.begin(), cmd1_str.end(), ' ');
	numargs2 = count(cmd2_str.begin(), cmd2_str.end(), ' ');
	numargs3 = count(cmd3_str.begin(), cmd3_str.end(), ' ');
	numargs4 = count(cmd4_str.begin(), cmd4_str.end(), ' ');
	cmd1_args = new (nothrow) char*[numargs1 + 2];
	cmd2_args = new (nothrow) char*[numargs2 + 2];
	cmd3_args = new (nothrow) char*[numargs3 + 2];
	cmd4_args = new (nothrow) char*[numargs4 + 2];
	tokenize(cmd1_args, argv[1]);
	tokenize(cmd2_args, argv[2]);
	tokenize(cmd3_args, argv[3]);
	tokenize(cmd4_args, argv[4]);
	
	if((childpid1 = fork()) == -1){
		perror("Error creating a child process.");
		exit(1);
	}
	
	if (childpid1 == 0) {
		if((childpid2 = fork()) == -1){
			perror("Error creating a child process.");
			exit(1);
		}
		if (childpid2 == 0) {
			if((childpid3 = fork()) == -1){
				perror("Error creating a child process.");
				exit(1);
			}

			if(childpid3 == 0){
				dup2(pipe1fd[1], 1);
				close(pipe1fd[0]);
				close(pipe1fd[1]);
				close(pipe2fd[0]);
				close(pipe2fd[1]);
				close(pipe3fd[0]);
				close(pipe3fd[1]);
				execvp(*cmd1_args, cmd1_args);
				exit(0);
			}else {
				dup2(pipe1fd[0], 0);
				dup2(pipe2fd[1], 1);
				close(pipe1fd[0]);
				close(pipe1fd[1]);
				close(pipe2fd[0]);
				close(pipe2fd[1]);
				close(pipe3fd[0]);
				close(pipe3fd[1]);
				execvp(*cmd2_args, cmd2_args);
				exit(0);
			}
		}else {	
			dup2(pipe2fd[0], 0);
			dup2(pipe3fd[1], 1);
			close(pipe1fd[0]);
			close(pipe1fd[1]);
			close(pipe2fd[0]);
			close(pipe2fd[1]);
			close(pipe3fd[0]);
			close(pipe3fd[1]);
			execvp(*cmd3_args, cmd3_args);
			exit(0);
		}
	} else {
		dup2(pipe3fd[0], 0);
		close(pipe1fd[0]);
		close(pipe1fd[1]);
		close(pipe2fd[0]);
		close(pipe2fd[1]);
		close(pipe3fd[0]);
		close(pipe3fd[1]);
		execvp(*cmd4_args, cmd4_args);
	}
	return 0;
}

int run5com(char **argv, int pipe1fd[], int pipe2fd[], int pipe3fd[], int pipe4fd[]) {
	string cmd1_str, cmd2_str, cmd3_str, cmd4_str, cmd5_str;
	int childpid1, childpid2, childpid3, childpid4, numargs1, numargs2, numargs3, numargs4, numargs5 = 0;
	char **cmd1_args, **cmd2_args, **cmd3_args, **cmd4_args, **cmd5_args;
	cmd1_str = argv[1];
	cmd2_str = argv[2];
	cmd3_str = argv[3];
	cmd4_str = argv[4];
	cmd5_str = argv[5];
	numargs1 = count(cmd1_str.begin(), cmd1_str.end(), ' ');
	numargs2 = count(cmd2_str.begin(), cmd2_str.end(), ' ');
	numargs3 = count(cmd3_str.begin(), cmd3_str.end(), ' ');
	numargs4 = count(cmd4_str.begin(), cmd4_str.end(), ' ');
	numargs5 = count(cmd5_str.begin(), cmd5_str.end(), ' ');
	cmd1_args = new (nothrow) char*[numargs1 + 2];
	cmd2_args = new (nothrow) char*[numargs2 + 2];
	cmd3_args = new (nothrow) char*[numargs3 + 2];
	cmd4_args = new (nothrow) char*[numargs4 + 2];
	cmd5_args = new (nothrow) char*[numargs5 + 2];
	tokenize(cmd1_args, argv[1]);
	tokenize(cmd2_args, argv[2]);
	tokenize(cmd3_args, argv[3]);
	tokenize(cmd4_args, argv[4]);
	tokenize(cmd5_args, argv[5]);
	
	if((childpid1 = fork()) == -1){
		perror("Error creating a child process.");
		exit(1);
	}
	
	if (childpid1 == 0) {
		if((childpid2 = fork()) == -1){
			perror("Error creating a child process.");
			exit(1);
		}
		if (childpid2 == 0) {
			if((childpid3 = fork()) == -1){
				perror("Error creating a child process.");
				exit(1);
			}

			if(childpid3 == 0){
				if((childpid4 = fork()) == -1){
					perror("Error creating a child process.");
					exit(1);
				}
				
				if(childpid4 == 0){
					dup2(pipe1fd[1], 1);
					close(pipe1fd[0]);
					close(pipe1fd[1]);
					close(pipe2fd[0]);
					close(pipe2fd[1]);
					close(pipe3fd[0]);
					close(pipe3fd[1]);
					close(pipe4fd[0]);
					close(pipe4fd[1]);
					execvp(*cmd1_args, cmd1_args);
					exit(0);
				}else {
					dup2(pipe1fd[0], 0);
					dup2(pipe2fd[1], 1);
					close(pipe1fd[0]);
					close(pipe1fd[1]);
					close(pipe2fd[0]);
					close(pipe2fd[1]);
					close(pipe3fd[0]);
					close(pipe3fd[1]);
					close(pipe4fd[0]);
					close(pipe4fd[1]);
					execvp(*cmd2_args, cmd2_args);
					exit(0);
				}
			}else {
				dup2(pipe2fd[0], 0);
				dup2(pipe3fd[1], 1);
				close(pipe1fd[0]);
				close(pipe1fd[1]);
				close(pipe2fd[0]);
				close(pipe2fd[1]);
				close(pipe3fd[0]);
				close(pipe3fd[1]);
				close(pipe4fd[0]);
				close(pipe4fd[1]);
				execvp(*cmd3_args, cmd3_args);
				exit(0);
			}
		}else {	
			dup2(pipe3fd[0], 0);
			dup2(pipe4fd[1], 1);
			close(pipe1fd[0]);
			close(pipe1fd[1]);
			close(pipe2fd[0]);
			close(pipe2fd[1]);
			close(pipe3fd[0]);
			close(pipe3fd[1]);
			close(pipe4fd[0]);
			close(pipe4fd[1]);
			execvp(*cmd4_args, cmd4_args);
			exit(0);
		}
	} else {
		dup2(pipe4fd[0], 0);
		close(pipe1fd[0]);
		close(pipe1fd[1]);
		close(pipe2fd[0]);
		close(pipe2fd[1]);
		close(pipe3fd[0]);
		close(pipe3fd[1]);
		close(pipe4fd[0]);
		close(pipe4fd[1]);
		execvp(*cmd5_args, cmd5_args);
	}
	return 0;
}

void tokenize (char *cmd_args[], char *cmd_str) {
	char *tmp = cmd_str;
	int i = 0;
	tmp = strtok(tmp, " ");
	while (tmp != NULL){
		cmd_args[i] = tmp;
		tmp = strtok(NULL, " ");
		i++;
	}
}
