#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

int factorial(int number)
{
    int fact = 1;

    for (int j = 1; j <= number; j++)
    {
        fact = fact * j;
    }
    return fact;
}

int main(int ac, char **av)
{

    int number;

    if (ac == 2)
    {
        if (sscanf(av[1], "%d", &number) == 1)
        {
            const char *name = "shared_memory";
            const char *sema1 = "fill";
            const char *sema2 = "avail";
            const char *sema3 = "mutex";
            int memorySize = sizeof(int)*sizeof(int);
            //int memorySize = 500000000;
            int shm_fd; // shared memory file discriptor
            long *catNumber;
            
            sem_t *fill, *avail, *mutex;
            /* make * shcatNumberelf shared between processes*/
            // create the shared memory segment
            shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
            // configure the size of the shared memory segment
            ftruncate(shm_fd, memorySize);
            // map the shared memory segment in process address space
            catNumber = mmap(0, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
            /* creat/open semaphores*/
            // cook post semaphore fill after cooking a pizza
            fill = sem_open(sema1, O_CREAT, 0666, 0);
            // waiter post semaphore avail after picking up a pizza, at the beginning avail=3
            avail = sem_open(sema2, O_CREAT, 0666, 1);
            // mutex for mutual exclusion of catNumber
            mutex = sem_open(sema3, O_CREAT, 0666, 1);
            //printf("\nCook: I have started cooking pizza.\n");
            for (int i = 1; i <= number; i ++)
            {
                sem_wait(avail);
                sem_wait(mutex);
                *catNumber = (double)factorial(2*i)/(double)((factorial(i+1))*(factorial(i)));
                sem_post(mutex);
                sem_post(fill);
            }
            //printf("Cook: Time is up. I cooked 6 pizza. %d are left.\n", *shelf);
            /* close and unlink semaphores*/
            sem_close(fill);
            sem_close(avail);
            sem_close(mutex);
            sem_unlink(sema1);
            sem_unlink(sema2);
            sem_unlink(sema3);
            /* close and unlink shared memory*/
            munmap(catNumber, memorySize);
            close(shm_fd);
            shm_unlink(name);
        }
        else
            fprintf(stderr, "Cannot translate argument\n");
    }
    else
        fprintf(stderr, "Invalid arguments\n");
    return (0);
}