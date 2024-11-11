#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep function

//4_b_rw

void *reader(void*);
void *writer(void*);

int getItemforBuff();
void readItemfromBuff(int buffer);

int buff;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Condition variable

int flag = 0;

int main()
{
    pthread_t rd_tid, rd_tid1;
    pthread_t wr_tid;

    // Create writer and reader threads
    pthread_create(&wr_tid, NULL, writer, NULL);
    pthread_create(&rd_tid, NULL, reader, NULL);
    pthread_create(&rd_tid1, NULL, reader, NULL);

    // Join threads (wait for them to finish)
    pthread_join(wr_tid, NULL);
    pthread_join(rd_tid, NULL);
    pthread_join(rd_tid1, NULL);

    return 0;
}

void *reader(void *argp)
{
    while (1)
    {
        pthread_mutex_lock(&mut);
        while (flag == 0) // Use a while loop to avoid spurious wakeups
        {
            pthread_cond_wait(&cond, &mut); // Wait for a signal from the writer
        }
        // Print thread ID
        printf("Reader Thread ID=%lu\n", pthread_self());
        readItemfromBuff(buff);
        flag = 0; // Mark buffer as empty
        pthread_cond_signal(&cond); // Signal the writer to continue
        pthread_mutex_unlock(&mut);
        sleep(1);  // Added sleep to avoid busy-waiting
    }
    return NULL;
}

void *writer(void *argp)
{
    int a;
    while (1)
    {
        pthread_mutex_lock(&mut);
        while (flag == 1) // Use a while loop to avoid spurious wakeups
        {
            pthread_cond_wait(&cond, &mut); // Wait for a signal from the reader
        }
        // Print thread ID
        a = (int)pthread_self();  // Cast to int for display
        printf("Writer Thread ID=%lu\n", pthread_self());
        buff = getItemforBuff();
        flag = 1; // Mark buffer as full
        pthread_cond_signal(&cond); // Signal the reader to continue
        pthread_mutex_unlock(&mut);
        sleep(1);  // Added sleep to avoid busy-waiting
    }
    return NULL;
}

int getItemforBuff()
{
    int item;
    printf("Writer: Enter an item into buffer\n");
    scanf("%d", &item);
    return item;
}

void readItemfromBuff(int buffer)
{
    printf("Reader: Read item from buffer=%d\n", buffer);
}

