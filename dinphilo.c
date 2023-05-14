#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

enum { THINKING, HUNGRY, EATING } state[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;
pthread_cond_t cond[NUM_PHILOSOPHERS];

void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d is eating.\n", i);
        pthread_cond_signal(&cond[i]);
    }
}

void pickup_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry.\n", i);
    test(i);
    if (state[i] != EATING)
        pthread_cond_wait(&cond[i], &mutex);
    pthread_mutex_unlock(&mutex);
}

void return_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is thinking.\n", i);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    int eat_count = 0;

    while (eat_count < 3) {
        usleep(rand() % 1000000); // Think for a random period
        pickup_forks(i);
        usleep(rand() % 1000000); // Eat for a random period
        return_forks(i);
        eat_count++;
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_init(&cond[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_destroy(&cond[i]);

    return 0;
}
