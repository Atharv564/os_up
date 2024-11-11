#include <stdio.h>

int main() {
    int incomingStream[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};  
    int pageFaults = 0;  
    int hits = 0;  // Initialize hits count
    int frames = 3;  
    int m, n, s, pages;   
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);   
    
    printf("Incoming\tFrame 1\tFrame 2\tFrame 3\n");
    
    int temp[frames];  
    for (m = 0; m < frames; m++) {  
        temp[m] = -1;  
    }  
    
    for (m = 0; m < pages; m++) {  
        s = 0;   
        
        for (n = 0; n < frames; n++) {  
            if (incomingStream[m] == temp[n]) {  
                s++;  // Page hit
                hits++;  // Increment hit count
                break;  // Exit the loop on hit
            }  
        }  
        
        if (s == 0) {  // If it was a miss
            pageFaults++;  // Increment page fault count

            // If there's an empty frame, load the new page
            if (pageFaults <= frames) {  
                temp[pageFaults - 1] = incomingStream[m];  
            } else {  
                // Replace the oldest page
                temp[(pageFaults - 1) % frames] = incomingStream[m];  
            }  
        }  

        // Print the current state of frames
        printf("\n%d\t\t", incomingStream[m]);  
        for (n = 0; n < frames; n++) {  
            if (temp[n] != -1)  
                printf("%d\t\t", temp[n]);  
            else  
                printf("-\t\t");  
        }  
    }  
    
    // Calculate hit ratio and miss ratio
    float hitRatio = (float)hits / pages;  // Total hits / total page requests
    float missRatio = (float)pageFaults / pages;  // Total page faults / total page requests

    printf("\nTotal Hits:\t\t%d\n", hits);  
    printf("Total Page Faults:\t%d\n", pageFaults);  
    printf("Hit Ratio:\t\t%.2f\n", hitRatio);  
    printf("Miss Ratio:\t\t%.2f\n", missRatio);  

    return 0;  
}
