#include <stdio.h>

int main() {
    int i, j, n, a[50], frame[10], no, k, avail, count = 0;

    // Input the number of pages
    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);

    // Input the page numbers
    printf("\nENTER THE PAGE NUMBERS:\n");
    for(i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    // Input the number of frames
    printf("\nENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &no);

    // Initialize frames with -1 (empty)
    for(i = 0; i < no; i++)
        frame[i] = -1;

    j = 0;

    // Print headers
    printf("\n+------------+-----------------------------+\n");
    printf("| Page No.  |       Page Frames           |\n");
    printf("+------------+-----------------------------+\n");

    // Process each page in the reference string
    for(i = 1; i <= n; i++) {
        avail = 0;
        printf("| %-10d |", a[i]);  // Print the current page number

        // Check if the page is already in the frame
        for(k = 0; k < no; k++) {
            if(frame[k] == a[i]) {
                avail = 1;
                break;
            }
        }

        // If page is not found, it's a page fault
        if(avail == 0) {
            frame[j] = a[i];  // Replace the oldest page (circular replacement)
            j = (j + 1) % no;  // Update the index for the next frame to replace
            count++;  // Increment page fault count
        }

        // Print the current status of frames
        for(k = 0; k < no; k++) {
            if(frame[k] == -1) {
                printf("  -  ");
            } else {
                printf("  %d  ", frame[k]);
            }
        }
        printf("|\n");
    }

    printf("+------------+-----------------------------+\n");

    // Output the total number of page faults
    printf("\nPage Faults: %d\n", count);

    return 0;
}
