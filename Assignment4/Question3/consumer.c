#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
int main()
{

  //Declare semaphore, name for shared memory, size, and shared memory map
  const char *name = "shared_memory";
  const char *semaphore1 = "fill";
  const char *semaphore2 = "avail";
  const char *semaphore3 = "mutex";
  long memorySize = sizeof(long);
  int shm_fd; // file descriptor of
  long *memoryNumber;

  sem_t *fill, *avail, *mutex;
  /* open the shared memory segment */
  shm_fd = shm_open(name, O_RDWR, 0666);
  /* now map the shared memory segment in the address space of the process*/
  memoryNumber = mmap(0, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  /* open semaphores*/
  fill = sem_open(semaphore1, O_CREAT, 0666, 0);
  avail = sem_open(semaphore2, O_CREAT, 0666, 1);
  mutex = sem_open(semaphore3, O_CREAT, 0666, 1);

  //Loop to check if there is a number in memory and updating it (mutual exclusion is important to make sure that every number put into memory is processed and printed out)
  while (1 == 1)
  {
    sem_wait(fill);
    printf("%ld %s", *memoryNumber, "\n");
    sem_post(mutex);
    sem_post(avail);
  }
  /* remove semaphores*/
  sem_close(fill);
  sem_close(avail);
  sem_close(mutex);
  sem_unlink(semaphore1);
  sem_unlink(semaphore2);
  sem_unlink(semaphore3);
  /* remove shared memory segment*/
  munmap(memoryNumber, memorySize);
  close(shm_fd);
  shm_unlink(name);
  return 0;
}