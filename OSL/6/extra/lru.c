#include <stdio.h>

int main() {
    int q[20], p[50], pageFaults = 0, hits = 0, c1, f, i, j, k = 0, n, r, t, b[20], c2[20];
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);
    
    printf("Enter number of frames: ");
    scanf("%d", &f);
    
    q[k] = p[k];  // Load the first page
    printf("\n\t%d\n", q[k]);
    k++;
    
    for (i = 1; i < n; i++) {
        c1 = 0;
        for (j = 0; j < f; j++) {
            if (p[i] == q[j]) {
                hits++;  // Page hit
                c1 = -1;  // Mark as hit
                break;    // Break if found
            }
        }
        if (c1 != -1) {  // If it was a miss
            pageFaults++;
            if (k < f) {
                q[k] = p[i];  // Fill empty frame
                k++;
                for (j = 0; j < k; j++)
                    printf("\t%d", q[j]);
                printf("\n");
            } else {
                // Calculate the least recently used page
                for (r = 0; r < f; r++) {
                    c2[r] = 0;  // Initialize the counter
                    for (j = i - 1; j >= 0; j--) {
                        if (q[r] != p[j])
                            c2[r]++;
                        else
                            break;  // Stop when we find the page
                    }
                }
                for (r = 0; r < f; r++)
                    b[r] = c2[r];

                // Find the LRU page
                for (r = 0; r < f; r++) {
                    for (j = r + 1; j < f; j++) {
                        if (b[r] > b[j]) {  // Sort based on recency
                            t = b[r];
                            b[r] = b[j];
                            b[j] = t;
                        }
                    }
                }

                // Replace the LRU page
                for (r = 0; r < f; r++) {
                    if (c2[r] == b[0]) {
                        q[r] = p[i];  // Replace the LRU page
                        break;  // Break after replacement
                    }
                }
                for (j = 0; j < f; j++)
                    printf("\t%d", q[j]);
                printf("\n");
            }
        }
    }
    
    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Hits: %d\n", hits);
    printf("Hit Ratio: %.2f\n", (float)hits / n);
    printf("Miss Ratio: %.2f\n", (float)pageFaults / n);

    return 0;
}
