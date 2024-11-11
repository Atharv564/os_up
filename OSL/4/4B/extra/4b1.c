#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep()

#define NUM_READERS 3
#define NUM_WRITERS 2
#define MAX_OPERATIONS 10  // Define the maximum number of operations for readers and writers

sem_t mutex, writeMutex;
int readCount = 0;
int totalReaderOperations = 0;
int totalWriterOperations = 0;
sem_t readerOpsMutex, writerOpsMutex;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);  // Enter critical section for readerCount
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeMutex);  // Block writers when the first reader enters
        }
        sem_post(&mutex);

        // Reading
        printf("Reader %ld is reading...\n", (long)arg);
        sleep(2);  // Simulate reading

        sem_wait(&mutex);  // Enter critical section for readerCount
        readCount--;
        if (readCount == 0) {
            sem_post(&writeMutex);  // Allow writers when the last reader exits
        }
        sem_post(&mutex);

        // Increment the total reader operations with synchronization
        sem_wait(&readerOpsMutex);
        totalReaderOperations++;
        sem_post(&readerOpsMutex);

        if (totalReaderOperations >= MAX_OPERATIONS) {
            break;
        }
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&writeMutex);  // Writer has exclusive access

        // Writing
        printf("Writer %ld is writing...\n", (long)arg);
        sleep(3);  // Simulate writing

        sem_post(&writeMutex);  // Release the writer lock

        // Increment the total writer operations with synchronization
        sem_wait(&writerOpsMutex);
        totalWriterOperations++;
        sem_post(&writerOpsMutex);

        if (totalWriterOperations >= MAX_OPERATIONS) {
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    sem_init(&mutex, 0, 1);  // Mutex for readCount
    sem_init(&writeMutex, 0, 1);  // Mutex for write access (exclusive)
    sem_init(&readerOpsMutex, 0, 1);  // Mutex for reader operation counter
    sem_init(&writerOpsMutex, 0, 1);  // Mutex for writer operation counter

    // Create reader threads
    for (long i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)i);
    }

    // Create writer threads
    for (long i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    // Wait for all reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writer threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeMutex);
    sem_destroy(&readerOpsMutex);
    sem_destroy(&writerOpsMutex);

    return 0;
}

