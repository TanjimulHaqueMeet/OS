#include <stdio.h>

#define MAX 100

int pages[MAX], frames[MAX], time[MAX];
int n, capacity, pageFaults = 0, pageHits = 0;

// Check if page exists in frame
int isInFrames(int page, int count) {
    for (int i = 0; i < count; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

// Print current state of frames
void printFrames(int count) {
    printf("\t[");
    for (int i = 0; i < count; i++) {
        printf("%2d", frames[i]);
        if (i != count - 1) printf(" ");
    }
    printf("]\n");
}

/* 
-------------------------------
       ALGORITHM SWITCH
-------------------------------
To use a different algorithm, comment/uncomment only one of the following 
findVictim() functions.
*/

// ---------------- FIFO ----------------
int findVictim(int currentIndex, int count) {
    static int pointer = 0;
    int victim = pointer;
    pointer = (pointer + 1) % capacity;
    return victim;
}

/*
// ---------------- LRU ----------------
int findVictim(int currentIndex, int count) {
    int lruIndex = 0;
    for (int i = 1; i < count; i++) {
        if (time[i] < time[lruIndex])
            lruIndex = i;
    }
    return lruIndex;
}
*/

/*
// ---------------- MRU ----------------
int findVictim(int currentIndex, int count) {
    int mruIndex = 0;
    for (int i = 1; i < count; i++) {
        if (time[i] > time[mruIndex])
            mruIndex = i;
    }
    return mruIndex;
}
*/

/*
// ------------- OPTIMAL --------------
int findVictim(int currentIndex, int count) {
    int farthest = currentIndex, victim = -1;

    for (int i = 0; i < count; i++) {
        int j;
        for (j = currentIndex + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    victim = i;
                }
                break;
            }
        }
        if (j == n) return i; // Not used again
    }

    return (victim == -1) ? 0 : victim;
}
*/

void runAlgorithm() {
    int count = 0;

    for (int i = 0; i < n; i++) {
        int index = isInFrames(pages[i], count);

        if (index != -1) {
            pageHits++;
            time[index] = i;  // Update last used time (for LRU/MRU)
            printf("Page %2d -> Hit ", pages[i]);
        } else {
            pageFaults++;
            if (count < capacity) {
                frames[count] = pages[i];
                time[count] = i;
                count++;
            } else {
                int replaceIndex = findVictim(i, count);
                frames[replaceIndex] = pages[i];
                time[replaceIndex] = i;
            }
            printf("Page %2d -> Miss", pages[i]);
        }

        printFrames(count);
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits   = %d\n", pageHits);
}

int main() {
    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\nPage Replacement Simulation:\n");
    runAlgorithm();

    return 0;
}
