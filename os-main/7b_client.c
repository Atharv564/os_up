#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 12345 // Shared memory key
#define SHM_SIZE 1024 // Size of shared memory

int main() {
    // Locate the shared memory segment created by the server
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory segment
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Read the message from shared memory
    printf("Client: Message read from shared memory: %s\n", shared_memory);

    // Detach from shared memory
    shmdt(shared_memory);

    return 0;
}

