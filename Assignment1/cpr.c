/* ------------------------------------------------ ------------
File: cpr.c

Last name: Couture
Student number: 300076065

Description: This program contains the code for creation
 of a child process and attach a pipe to it.
	 The child will send messages through the pipe
	 which will then be sent to standard output.

Explanation of the zombie process
(point 5 of "To be completed" in the assignment):

	(please complete this part);

------------------------------------------------------------- */
#include <stdio.h>
#include <sys/select.h>
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#define MSGSIZE 17

/* Prototype */
void createChildAndRead (int);

/* -------------------------------------------------------------
Function: main
Arguments: 
	int ac	- number of command arguments
	char **av - array of pointers to command arguments
Description:
	Extract the number of processes to be created from the
	Command line. If an error occurs, the process ends.
	Call createChildAndRead to create a child, and read
	the child's data.
-------------------------------------------------- ----------- */

int main (int ac, char **av)
{
 int processNumber; 

 if (ac == 2)
 {
 if (sscanf (av [1], "%d", &processNumber)== 1)
 {
    createChildAndRead(processNumber);
 }
    else fprintf(stderr, "Cannot translate argument\n");
 }
    else fprintf(stderr, "Invalid arguments\n");
    return (0);
}


/* ------------------------------------------------ -------------
Function: createChildAndRead
Arguments: 
	int prcNum - the process number
Description:
	Create the child, passing prcNum-1 to it. Use prcNum
	as the identifier of this process. Also, read the
	messages from the reading end of the pipe and sends it to 
	the standard output (df 1). Finish when no data can
	be read from the pipe.
-------------------------------------------------- ----------- */

void createChildAndRead(int prcNum)
{
	//Create buffer
	char inbuf[MSGSIZE];

	if (prcNum == 1){
		write(1, "Process 1 begins", MSGSIZE);
		sleep(0);
		write(1, "Process 1 ends", MSGSIZE);
		return;
	}

	else {
		//Storing variable for pipe
		int fd[2];

		int ret = pipe(fd);
		if (ret == -1) {
			/* error */
			perror("pipe");
			exit(1);
		}

		int pid = fork();
		if (pid < 0) {
			fprintf(stderr, "Fork Failed");
			exit(-1);
		}
		else if (pid == 0) {
			//This is child, closing read, setting up standard output to pipe

			//printf("%s", "SOMETHINBGGGGGGGGGGGGGGG\n");

			close(fd[0]);
			dup2(fd[1], 1);

			//Get process begin message
			char process[] = "Process ";
			char buffer[17];
			sprintf(buffer, "%d", prcNum);
			strcat(process, buffer);
			strcat(process, " begins");

			//printf("%s", process);
			write(fd[1], process, MSGSIZE);
			//close(fd[1]);

			int answer = prcNum - 1;

			char minusone[17];
			sprintf(minusone, "%d", answer);
			//printf("%s", minusone);

			char* args[] = {"./cpr", minusone, NULL };

			execvp("./cpr", args);


		}
		else {
			close(fd[1]);
			dup2(fd[0], 0);

			while (read(fd[0], inbuf, MSGSIZE)) {
				strcat(inbuf, "\n");
				write(1, inbuf, 17);
				//printf("%s", inbuf);
				//printf("\n");
			}
			
			//Get process end message
			char process[] = "Process ";
			char buffer[20];
			sprintf(buffer, "%d", prcNum);
			strcat(process, buffer);
			strcat(process, " ends");

			//printf("%s", process);
			printf("%s",process);
			//write(1, process, 15);

		}


	}

 /* Please complete this function according to the
Assignment instructions. */
}



