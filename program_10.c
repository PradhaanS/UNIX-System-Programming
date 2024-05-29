#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 5
// Shared resource
int shared_resource = 0;
// Semaphore declaration
sem_t semaphore;
// Thread function
void *thread_function(void *arg) {
     int thread_id = *((int *)arg);
     // Wait for semaphore
     sem_wait(&semaphore);
     // Critical section
     printf("Thread %d accessing shared resource.\n", thread_id);
     shared_resource++;
     printf("Shared resource value incremented to: %d\n", shared_resource);
     // Release semaphore
     sem_post(&semaphore);
     pthread_exit(NULL);
}
int main() {
     pthread_t threads[NUM_THREADS];
     int thread_ids[NUM_THREADS];
     // Initialize semaphore
     sem_init(&semaphore, 0, 1); // Initial value is 1, indicating semaphore is available
     // Create threads
     for (int i = 0; i < NUM_THREADS; i++) {
     thread_ids[i] = i + 1;
     if (pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]) != 0) {
        fprintf(stderr, "Error creating thread %d\n", i);
        exit(EXIT_FAILURE);
     }
 }
 // Join threads
 for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
        fprintf(stderr, "Error joining thread %d\n", i);
        exit(EXIT_FAILURE);
    }
 }
 // Destroy semaphore
 sem_destroy(&semaphore);
 return 0;
}
