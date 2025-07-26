#include <stdio.h>
#define MAX 100

int pages[MAX], frames[MAX], time[MAX];
int n, cap, faults = 0, hits = 0;

int inFrames(int page, int count) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page) return i;
    return -1;
}

// ----------- ALGORITHM SWITCH -----------

// -------- FIFO --------
int findVictim(int cur, int count) {
    static int ptr = 0;
    return ptr++ % cap;
}

/*
// -------- LRU --------
int findVictim(int cur, int count) {
    int lru = 0;
    for (int i = 1; i < count; i++)
        if (time[i] < time[lru]) lru = i;
    return lru;
}
*/

/*
// -------- MRU --------
int findVictim(int cur, int count) {
    int mru = 0;
    for (int i = 1; i < count; i++)
        if (time[i] > time[mru]) mru = i;
    return mru;
}
*/

/*
// ------- OPTIMAL -------
int findVictim(int cur, int count) {
    int far = cur, vic = -1;
    for (int i = 0; i < count; i++) {
        int j;
        for (j = cur + 1; j < n; j++)
            if (frames[i] == pages[j]) {
                if (j > far) far = j, vic = i;
                break;
            }
        if (j == n) return i;
    }
    return (vic == -1) ? 0 : vic;
}
*/

int main() {
    printf("Enter number of frames: ");
    scanf("%d", &cap);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int count = 0;
    for (int i = 0; i < n; i++) {
        int pos = inFrames(pages[i], count);
        if (pos != -1) hits++, time[pos] = i;
        else {
            faults++;
            if (count < cap) pos = count++;
            else pos = findVictim(i, count);
            frames[pos] = pages[i];
            time[pos] = i;
        }
    }

    printf("\nPage Faults = %d\n", faults);
    printf("Page Hits   = %d\n", hits);
    return 0;
}
