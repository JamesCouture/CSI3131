#include <stdio.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
Last name: Couture
Student number: 300076065

Last name: Bahia
Student number: 300025648
*/

/* Prototype */
pthread_mutex_t lock;
sem_t taSleepSemaphore;
void *ta(void *param);      /* the thread */
void *student(void *param); /* the thread */
int counter;

int main(int ac, char **av)
{
    int n;

    if (ac == 2)
    {
        if (sscanf(av[1], "%d", &n) == 1)
        {
            // create the thread here... start program
            // srand(time(NULL));
            pthread_t tidStudent[n];    /* the thread identifier */
            pthread_t tidTA;            /* the thread identifier */
            pthread_attr_t attrTA;      /* set of attributes for the thread */
            pthread_attr_t attrStudent; /* set of attributes for the thread */

            /* get the default attributes */
            pthread_attr_init(&attrTA);
            /* get the default attributes */
            pthread_attr_init(&attrStudent);

            sem_init(&taSleepSemaphore, 0, 0);

            /* create the thread */
            pthread_create(&tidTA, &attrTA, ta, NULL);
            printf("%s", "ta created\n");
            for (int i = 0; i < n; i++)
            {
                pthread_create(&tidStudent[i], &attrStudent, &student, &i);
            }

            /* now wait for the thread to exit */
            pthread_join(tidTA, NULL);
            /* now wait for the thread to exit */
            for (int i = 0; i < n; i++)
            {
                pthread_join(tidStudent[i], NULL);
            }

            sem_destroy(&taSleepSemaphore);
        }
        else
            fprintf(stderr, "Cannot translate argument\n");
    }
    else
        fprintf(stderr, "Invalid arguments\n");
    return (0);
}

/**
 * The thread will begin control in this function
 */
void *ta(void *param)
{

    int check = 0;

    printf("%s", "Ta is going to sleep\n");
    sem_wait(&taSleepSemaphore);
    printf("%s", "Ta is waking up to work with student\n");
    sem_post(&taSleepSemaphore);

    while (1 == 1)
    {
        // Checking if it is necessary to check conditions
        if (counter != check)
        {

            if (counter == 0)
            {
                printf("%s", "Ta is going to sleep\n");
                sem_wait(&taSleepSemaphore);
                printf("%s", "Ta is waking up to work with student\n");
                sem_post(&taSleepSemaphore);
            }

            check = counter;
        }
    }

    pthread_exit(0);
}

void *student(void *param)
{

    int a = *(int *)param;

    while (1 == 1)
    {
        // Student starting to work
        printf("%s %d %s", "Student #", a, " is programing\n");

        sleep((rand() % 10)+4);

        //  call TA
        printf("%s %d %s", "Student #", a, " is going to TA\n");

        counter += 1;

        while (counter > 4)
        {
            printf("%s %d %s", "Student #", a, " has no chair and goes back to programming\n");
            counter -= 1;
            sleep((rand() % 10)+2);
            counter += 1;
            printf("%s %d %s", "Student #", a, " is going to TA\n");
        }

        if (counter > 1)
        {
            printf("%s %d %s", "Student #", a, " has a chair and is waiting\n");
        }

        if (counter == 1)
        {
            printf("%s %d %s", "Student #", a, " is waking up TA\n");
        }

        sem_post(&taSleepSemaphore);
        pthread_mutex_lock(&lock);

        printf("%s %d %s", "Student #", a, " is getting help with TA\n");

        sleep((rand() % 10)+2);
        printf("%s %d %s", "Student #", a, " is done getting helped with TA\n");

        sem_wait(&taSleepSemaphore);
        counter -= 1;
        pthread_mutex_unlock(&lock);

    }

    pthread_exit(0);
}