#include <stdio.h>

int search(int key, int frame_items[], int frame_occupied) {
    for (int i = 0; i < frame_occupied; i++)
        if (frame_items[i] == key)
            return 1;
    return 0;
}

void printOuterStructure(int max_frames) {
    printf("\n+------------+");
    for (int i = 0; i < max_frames; i++)
        printf("----------+");
    printf("\n| Page No.   |");
    for (int i = 0; i < max_frames; i++)
        printf(" Frame %d   |", i + 1);
    printf("\n+------------+");
    for (int i = 0; i < max_frames; i++)
        printf("----------+");
}

void printCurrFrames(int item, int frame_items[], int frame_occupied, int max_frames) {
    printf("\n| %-10d |", item);
    for (int i = 0; i < max_frames; i++) {
        if (i < frame_occupied)
            printf(" %-8d |", frame_items[i]);
        else
            printf("    -    |");
    }
}

int predict(int ref_str[], int frame_items[], int refStrLen, int index, int frame_occupied) {
    int result = -1, farthest = index;
    for (int i = 0; i < frame_occupied; i++) {
        int j;
        for (j = index; j < refStrLen; j++) {
            if (frame_items[i] == ref_str[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == refStrLen)
            return i;
    }
    return (result == -1) ? 0 : result;
}

void optimalPage(int ref_str[], int refStrLen, int frame_items[], int max_frames) {
    int frame_occupied = 0;
    printOuterStructure(max_frames);
    
    int hits = 0;
    for (int i = 0; i < refStrLen; i++) {
        if (search(ref_str[i], frame_items, frame_occupied)) {
            hits++;
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
            continue;
        }
  
        if (frame_occupied < max_frames) {
            frame_items[frame_occupied] = ref_str[i];
            frame_occupied++;
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
        } else {
            int pos = predict(ref_str, frame_items, refStrLen, i + 1, frame_occupied);
            frame_items[pos] = ref_str[i];
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
        }
    }
    printf("\n+------------+");
    for (int i = 0; i < max_frames; i++)
        printf("----------+");
    printf("\n\nTotal Hits: %d", hits);
    printf("\nTotal Faults: %d\n", refStrLen - hits);
}

int main() {
    int refStrLen, max_frames;

    printf("Enter the number of pages: ");
    scanf("%d", &refStrLen);

    int ref_str[refStrLen];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < refStrLen; i++) {
        scanf("%d", &ref_str[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &max_frames);

    int frame_items[max_frames];
    for (int i = 0; i < max_frames; i++)
        frame_items[i] = -1;

    optimalPage(ref_str, refStrLen, frame_items, max_frames);
    
    return 0;
}
