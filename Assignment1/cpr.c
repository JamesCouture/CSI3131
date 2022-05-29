/* ------------------------------------------------ ------------
File: cpr.c

Last name: Couture
Student number: 300076065

Last name: Bahia
Student number: 300025648

Description: This program contains the code for creation
 of a child process and attach a pipe to it.
	 The child will send messages through the pipe
	 which will then be sent to standard output.

Explanation of the zombie process
(point 5 of "To be completed" in the assignment):
A zombie process is a process that has terminated but is still shown in the 
process table. Once a child process is terminated, it first becomes a zombie 
before it dissapears from the process table. The parent needs the child process to 
remain in the table so it can check its status during the wait().
This is shown when we execute the ps -u command each time a process terminates, as
we can still see the remaining terminated process in the table, however it has 
<defunct> written next to it.

	

------------------------------------------------------------- */
#include <stdio.h>
#include <sys/select.h>
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
//Declare the message size
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

	//Check if in base case
	if (prcNum == 1){

		//Write that process 1 begins and sleep for time asked
		write(1, "Process 1 begins \n", MSGSIZE);
		sleep(5);
	}

	else {
		//Storing variable for pipe
		int fd[2];

		//Create pipe
		int ret = pipe(fd);

		//Check if there is a pipe error
		if (ret == -1) {
			/* error */
			perror("pipe");
			exit(1);
		}

		//Create fork
		int pid = fork();

		//Check to see if child or parent
		if (pid < 0) {
			fprintf(stderr, "Fork Failed");
			exit(-1);
		}
		else if (pid == 0) {
			//This is child, closing read, setting up standard output to pipe

			//Point standard output towards the pipe
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);

			//Get process begin message
			char process[] = "Process ";
			char buffer[12];
			sprintf(buffer, "%d", prcNum);
			strcat(process, buffer);
			strcat(process, " begins\n");
			write(1, process, MSGSIZE);

			//Execute cpr - 1
			int answer = prcNum - 1;
			char minusone[12];
			sprintf(minusone, "%d", answer);

			char* args[] = {"./cpr", minusone, NULL };
			execvp("./cpr", args);

		}
		else {
			//Change standard input from terminal to pipe
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);

			//Write message stored in pipe until there is none
			while (read(0, inbuf, MSGSIZE)) {
				write(1, inbuf, MSGSIZE);
			}
		}
		
	}
	//sleep 5 secs so we can observe the ps command
	// sleep(5);
	// char* args[] = {"ps", "-u", "sbahia", NULL };

	
	//Get process end message and end process
	char process[] = "\nProcess ";
	char buffer[30];
	sprintf(buffer, "%d", prcNum);
	strcat(process, buffer);
	strcat(process, " ends ");
	write(1, process, MSGSIZE);

	//show process table on CLI
	// execvp("ps", args);
	
	
	
	return;

 /* Please complete this function according to the
Assignment instructions. */
}



