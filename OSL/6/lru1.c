#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3 // Number of frames

// Function to find the index of the least recently used page
int findLRU(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return i; // Page found
        }
    }
    return -1; // Page not found
}

// Function to implement LRU Page Replacement
void LRU(int pages[], int pageCount) {
    int frames[FRAME_SIZE];
    int pagesCount[FRAME_SIZE] = {0}; // To count page references
    int pageFaults = 0;
    int pageHits = 0; // Initialize page hits

    // Initialize frames
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1; // Empty frame
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int lruIndex = -1;

        // Check if page is already in frames
        if (findLRU(frames, FRAME_SIZE, page) == -1) {
            // Page fault occurs
            pageFaults++;
            // Find an empty frame
            for (int j = 0; j < FRAME_SIZE; j++) {
                if (frames[j] == -1) {
                    frames[j] = page; // Place page in the empty frame
                    pagesCount[j] = i; // Record the reference time
                    break;
                }
            }
            // If no empty frame, replace the least recently used page
            if (frames[FRAME_SIZE - 1] != -1) {
                lruIndex = 0;
                for (int j = 1; j < FRAME_SIZE; j++) {
                    if (pagesCount[j] < pagesCount[lruIndex]) {
                        lruIndex = j; // Update the LRU index
                    }
                }
                frames[lruIndex] = page; // Replace LRU page
                pagesCount[lruIndex] = i; // Update reference time
            }
        } else {
            // Page hit: Update reference time
            int index = findLRU(frames, FRAME_SIZE, page);
            pagesCount[index] = i; // Update reference time
            pageHits++; // Increment hit count
        }

        // Print current frames
        printf("Current Frames: ");
        for (int j = 0; j < FRAME_SIZE; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    // Calculate and print hit and miss ratios
    int totalReferences = pageCount;
    float hitRatio = (float)pageHits / totalReferences;
    float missRatio = (float)pageFaults / totalReferences;

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
    printf("Hit Ratio: %.2f\n", hitRatio);
    printf("Miss Ratio: %.2f\n", missRatio);
}

int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1}; // Example page reference string
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    LRU(pages, pageCount);

    return 0;
}

