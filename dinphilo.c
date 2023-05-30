#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];

void *philosopher(void *arg);
void pick_forks(int i);
void put_forks(int i);
void test(int i);

void *philosopher(void *arg) {
    int i = *((int *) arg);
    while (1) {
        printf("Philosopher %d is thinking.\n", i);
        sleep(rand() % 3 + 1);  // Thinking for a random time

        pick_forks(i);

        printf("Philosopher %d is eating.\n", i);
        sleep(rand() % 3 + 1);  // Eating for a random time

        put_forks(i);
    }
}

void pick_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry.\n", i);
    test(i);
    if (state[i] != EATING) {
        pthread_cond_wait(&condition[i], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d has finished eating and is thinking.\n", i);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d has picked up forks %d and %d and is eating.\n", i, LEFT, i);
        pthread_cond_signal(&condition[i]);
    }
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int thread_ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&condition[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}
