#include <stdio.h>
#include <sys/select.h>
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
/* Prototype */
pthread_mutex_t lock;
void *ta(void* param); /* the thread */
void *student(void* param); /* the thread */

int main (int ac, char **av)
{
 int n; 
 
 if (ac == 2)
 {
 if (sscanf (av [1], "%d", &n)== 1)
 {
    // create the thread here... start program
    srand(time(NULL));
    pthread_t tidStudent[n]; /* the thread identifier */
    pthread_t tidTA; /* the thread identifier */
    pthread_attr_t attrTA; /* set of attributes for the thread */
    pthread_attr_t attrStudent; /* set of attributes for the thread */

    // if (pthread_mutex_init(&lock, NULL) != 0)
    // {
    //     printf("\n mutex init failed\n");
    //     return 1;
    // }

    /* get the default attributes */
    pthread_attr_init(&attrTA);
    /* get the default attributes */
    pthread_attr_init(&attrStudent);

    /* create the thread */
    pthread_create(&tidTA,&attrTA,ta, NULL);
    printf("%s","ta created\n");
    for (int i = 0; i < n; i++) {
    pthread_create(&tidStudent[i],&attrStudent,student, NULL);  
    }

    /* now wait for the thread to exit */
    pthread_join(tidTA,NULL);
    /* now wait for the thread to exit */
    for (int i = 0; i < n; i++) {
    pthread_join(tidStudent[i],NULL);  
    }
    
    
 }
    else fprintf(stderr, "Cannot translate argument\n");
 }
    else fprintf(stderr, "Invalid arguments\n");
    return (0);
}



/**
* The thread will begin control in this function
*/
void *ta(void* param) 
{
    printf("%s","in ta\n");

    // help student 


    

pthread_exit(0);
}


void *student(void* param) 
{   
    
    int r = rand() % 10;
    printf("%s","in student\n");
    sleep(r);
    printf("%d\n",r );
    // call TA

    pthread_exit(0);
}