#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep function

#define BUFFER_SIZE 5

//4_a

sem_t full, empty;        
pthread_mutex_t mutex;        
int array[BUFFER_SIZE];        

int in = 0;        
int out = 0;        

void *producer(void *data)        
{
    int i, num, id;
    id = *((int *)data);  // Use pointer dereferencing to get the ID
    for(i = 0; i < 3; i++)        
    {
        sem_wait(&empty);        
        pthread_mutex_lock(&mutex);    

        num = id;            
        array[in] = num;            
        printf("\n\t Producer %d produced value %d stored at location %d", id, array[in], in);
        in = (in + 1) % BUFFER_SIZE;        

        pthread_mutex_unlock(&mutex);    
        sem_post(&full);        
        sleep(2);
    }
    return NULL;
}

void *consumer(void *data)    
{
    int i, num;
    int produced_items = 0; // Counter for produced items
    while (1)    
    {
        sem_wait(&full);    
        pthread_mutex_lock(&mutex);        

        num = array[out];                
        printf("\n\t\t\t Consumer consumed value %d from location %d", num, out);
        out = (out + 1) % BUFFER_SIZE;        

        pthread_mutex_unlock(&mutex);        
        sem_post(&empty);            
        sleep(3);
        
        // Increment the produced items counter
        produced_items++;

        // Break the loop if all items are consumed
        if (produced_items >= (4 * 3)) // 4 producers producing 3 items each
        {
            break; // Exit after consuming all produced items
        }
    }
    return NULL;
}

int main()        
{
    pthread_t tid[4], tid1;    
    int i, ids[4];

    sem_init(&full, 0, 0);    
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);

    // Initialize producer thread IDs
    for(i = 0; i < 4; i++)
    {
        ids[i] = i;
        pthread_create(&tid[i], NULL, producer, (void *)&ids[i]); 
    }
    
    // Create consumer thread
    pthread_create(&tid1, NULL, consumer, NULL); 

    // Join producer threads
    for(i = 0; i < 4; i++)
    {
        pthread_join(tid[i], NULL);
    }
    
    // Join consumer thread
    pthread_join(tid1, NULL);

    // Cleanup
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);

    return 0;
}

