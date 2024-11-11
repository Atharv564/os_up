#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 12345 // Shared memory key
#define SHM_SIZE 1024 // Size of shared memory

int main() {
    // Create a shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
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

    // Write a message to shared memory
    char message[] = "Hello from server process!";
    strncpy(shared_memory, message, SHM_SIZE);

    printf("Server: Message written to shared memory: %s\n", message);

    // Detach from shared memory (optional, server can stay attached)
    shmdt(shared_memory);

    // Wait for the client to finish reading before deleting (optional)
    printf("Press Enter to delete shared memory and exit...\n");
    getchar();

    // Delete the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

