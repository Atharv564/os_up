#include <stdio.h>

int findLRU(int time[], int n) {
    int minimum = time[0], pos = 0;
    
    for (int i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0;
    int time[10], flag1, flag2, i, j, pos;
    int faults = 0;

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &no_of_pages);

    // Input page numbers one by one
    printf("\nEnter the page numbers:\n");
    for (i = 0; i < no_of_pages; ++i) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("\nEnter the number of frames: ");
    scanf("%d", &no_of_frames);

    // Initialize frames to -1 to represent empty frames
    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    // Display table header
    printf("\n+---------------+-------------------------------+\n");
    printf("| Page Reference|       Frame Contents          |\n");
    printf("+---------------+-------------------------------+\n");

    // Process each page and manage frames with LRU algorithm
    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;
        
        // Check if the page is already in a frame
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = 1; // Page hit
                break;
            }
        }

        // If page was not found in the frames (Page Fault)
        if (flag1 == 0) {
            // Check for an empty frame
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1; // Frame filled
                    break;
                }
            }
        }

        // If there was no empty frame, replace with LRU page
        if (flag2 == 0) {
            pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Print the current frame state for the page
        printf("|      %d        | ", pages[i]);
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] != -1) {
                printf("%d\t", frames[j]);
            } else {
                printf("-\t");
            }
        }
        printf("|\n");
    }

    // Display total page faults
    printf("+---------------+-------------------------------+\n");
    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
