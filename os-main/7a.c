#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PIPE1 "/tmp/fifo1"
#define PIPE2 "/tmp/fifo2"
#define BUFFER_SIZE 1024

void count_characters_words_lines(char *str, int *char_count, int *word_count, int *line_count) {
    *char_count = *word_count = *line_count = 0;
    int in_word = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\n' && str[i] != '\0') { // Exclude null terminator from character count
            (*char_count)++;
        }
        if (str[i] == '\n') {
            (*line_count)++;
        }
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*word_count)++;
        }
    }
}


int main() {
    // Creating named pipes (FIFO)
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    pid_t pid = fork();

    if (pid > 0) {
        // Parent process (Process 1)
        char input[BUFFER_SIZE];
        int fd_write, fd_read;
        
        // Write to PIPE1
        printf("Enter a sentence: ");
        fgets(input, sizeof(input), stdin);

        fd_write = open(PIPE1, O_WRONLY);
        write(fd_write, input, strlen(input) + 1); // Include null terminator
        close(fd_write);

        // Read from PIPE2
        char result[BUFFER_SIZE] = {0}; // Initialize buffer with 0 to avoid garbage values
        fd_read = open(PIPE2, O_RDONLY);
        read(fd_read, result, sizeof(result));
        close(fd_read);

        // Display result
        printf("Result from Process 2:\n%s\n", result);
    } 
    else if (pid == 0) {
        // Child process (Process 2)
        char buffer[BUFFER_SIZE] = {0}; // Initialize buffer with 0
        int char_count, word_count, line_count;
        int fd_read, fd_write;

        // Read from PIPE1
        fd_read = open(PIPE1, O_RDONLY);
        read(fd_read, buffer, sizeof(buffer));
        close(fd_read);

        // Count characters, words, and lines
        count_characters_words_lines(buffer, &char_count, &word_count, &line_count);

        // Write results to file
        FILE *file = fopen("output.txt", "w");
        fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", char_count, word_count, line_count);
        fclose(file);

        // Read results from file
        FILE *file_read = fopen("output.txt", "r");
        char file_content[BUFFER_SIZE] = {0}; // Initialize buffer with 0
        fread(file_content, sizeof(char), BUFFER_SIZE, file_read);
        fclose(file_read);

        // Write to PIPE2
        fd_write = open(PIPE2, O_WRONLY);
        write(fd_write, file_content, strlen(file_content) + 1); // Include null terminator
        close(fd_write);
    }

    // Remove the FIFOs
    unlink(PIPE1);
    unlink(PIPE2);

    return 0;
}

