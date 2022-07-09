#include <stdio.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t waitForProducer;
void *producer(void *param); /* the thread */
void *consumer(void *param); /* the thread */

int factorial(int number){
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
            // create the thread here... start program
            // srand(time(NULL));
            pthread_t tidConsumer;       /* the thread identifier */
            pthread_t tidProducer;       /* the thread identifier */
            pthread_attr_t attrProducer; /* set of attributes for the thread */
            pthread_attr_t attrConsumer; /* set of attributes for the thread */

            /* get the default attributes */
            pthread_attr_init(&attrProducer);
            /* get the default attributes */
            pthread_attr_init(&attrConsumer);

            sem_init(&waitForProducer, 0, 0);

            /* create the thread */
            pthread_create(&tidProducer, &attrProducer, producer, &number);
            pthread_create(&tidConsumer, &attrConsumer, consumer, NULL);

            /* now wait for the thread to exit */
            pthread_join(tidProducer, NULL);
            /* now wait for the thread to exit */
            pthread_join(tidConsumer, NULL);
            

            // Destroy semaphore when done code
            sem_destroy(&waitForProducer);
        }
        else
            fprintf(stderr, "Cannot translate argument\n");
    }
    else
        fprintf(stderr, "Invalid arguments\n");
    return (0);
}

void *producer(void *param)
{
    int a = *(int *)param;

    int numberArray[a];

    for (int i = 1; i <= a; i++)
    {
        

        //numberArray[i-1] = fact;
        numberArray[i-1] = (double)factorial(2*i)/(double)((factorial(i+1))*(factorial(i)));
    }

    for (int i = 0; i < a; i++)
    {
        printf("%d %s", numberArray[i],"\n");
    }
}


void *consumer(void *param)
{
}