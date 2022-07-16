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
            const char *semaphore1 = "fill";
            const char *semaphore2 = "avail";
            const char *semaphore3 = "mutex";
            int memorySize = sizeof(int);
            int shm_fd; // shared memory file discriptor
            long *memoryNumber;
            
            sem_t *fill, *avail, *mutex;
            /* make * shmemorNumber shared between processes*/
            // create the shared memory segment
            shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
            // configure the size of the shared memory segment
            ftruncate(shm_fd, memorySize);
            // map the shared memory segment in process address space
            memoryNumber = mmap(0, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
            /* creat/open semaphores*/
            // semaphore to allow to know if the number has been printed
            fill = sem_open(semaphore1, O_CREAT, 0666, 0);
            // Check if a new number was consumed
            avail = sem_open(semaphore2, O_CREAT, 0666, 1);
            // mutex for mutual exclusion of memoryNumber
            mutex = sem_open(semaphore3, O_CREAT, 0666, 1);
            
            for (int i = 1; i <= number; i ++)
            {
                //Mutual exclusion and check to make sure the number was posted before adding the next one
                sem_wait(avail);
                sem_wait(mutex);
                //Calculation for Catalan Number
                *memoryNumber = (double)factorial(2*i)/(double)((factorial(i+1))*(factorial(i)));
                sem_post(mutex);
                sem_post(fill);
            }
            
            /* close and unlink semaphores*/
            sem_close(fill);
            sem_close(avail);
            sem_close(mutex);
            sem_unlink(semaphore1);
            sem_unlink(semaphore2);
            sem_unlink(semaphore3);
            /* close and unlink shared memory*/
            munmap(memoryNumber, memorySize);
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