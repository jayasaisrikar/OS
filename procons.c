#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t condp, condc;

void *producer(void *arg)
{
    int item;

    for (int i = 0; i < 10; i++) {
        item = rand() % 100;

        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&condp, &mutex);
        }

        buffer[in] = item;
        printf("Producer produced item %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;

    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&condc, &mutex);
        }

        item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t producerThread, consumerThread;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);

    return 0;
}
