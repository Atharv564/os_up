#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h> // For sleep function

void* reader(void*);
void* writer(void*);

int getItemforBuff();
void readItemfromBuff(int buffer);

//4_b_thread

int buffer;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;

int flag = 0;
int read_count = 0;
int running = 1; // Control variable for running threads

int main()
{
    pthread_t rd1_tid;
    pthread_t wr_tid;
    pthread_t rd2_tid;

    // Create threads
    pthread_create(&wr_tid, NULL, writer, NULL);
    pthread_create(&rd1_tid, NULL, reader, NULL);
    pthread_create(&rd2_tid, NULL, reader, NULL); 

    // Wait for threads to finish
    pthread_join(wr_tid, NULL);  
    pthread_join(rd1_tid, NULL);
    pthread_join(rd2_tid, NULL);

    return 0;
}

void* reader(void *argp)
{
    while (running)
    {
        pthread_mutex_lock(&mutex1);
        read_count++;

        if (read_count == 1)
        {
            pthread_mutex_lock(&wrt); // First reader locks the writer
        }

        pthread_mutex_unlock(&mutex1);        

        if (flag == 1) // Check if there's an item to read
        {
            readItemfromBuff(buffer);
            sleep(1); // Simulate reading time
            flag = 0; // Reset flag after reading
        }

        pthread_mutex_lock(&mutex1);    
        read_count--;    
        if (read_count == 0)
        {
            pthread_mutex_unlock(&wrt); // Last reader unlocks the writer
        }
        pthread_mutex_unlock(&mutex1);    
    }
    return NULL;
}

void* writer(void *argp)
{
    while (running)
    {
        int item = getItemforBuff();
        if (item == -1) // Termination condition
        {
            running = 0; // Stop the loop
            break; // Exit the loop
        }

        pthread_mutex_lock(&mutex1);
        if (flag == 0)
        {
            buffer = item; // Set buffer
            flag = 1; // Indicate an item is available
        }
        pthread_mutex_unlock(&mutex1);        
    }
    return NULL;
}

int getItemforBuff()
{
    int item;
    printf("Writer: Enter an item into buffer (enter -1 to exit): ");
    scanf("%d", &item);
    return item;
}

void readItemfromBuff(int buffer)
{
    printf("Thread ID=%ld\n", syscall(SYS_gettid));
    printf("Reader: Read item from buffer=%d\n", buffer);    
}

