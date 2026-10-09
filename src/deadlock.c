#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *worker1(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&lock1);

    printf("Thread 1: acquired Lock 1\n");

    sleep(1);

    printf("Thread 1: waiting for Lock 2\n");

    pthread_mutex_lock(&lock2);

    printf("Thread 1: acquired Lock 2\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

void *worker2(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&lock1);

    printf("Thread 2: acquired Lock 1\n");

    sleep(1);

    printf("Thread 2: waiting for Lock 2\n");

    pthread_mutex_lock(&lock2);

    printf("Thread 2: acquired Lock 2\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker1, NULL);
    pthread_create(&t2, NULL, worker2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
