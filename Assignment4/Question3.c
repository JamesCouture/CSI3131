#include <stdio.h>
#include <sys/select.h>
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

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