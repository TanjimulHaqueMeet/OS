#include <stdio.h>
#include <string.h>

#define MAX 100

// Select strategy: 0 = First Fit, 1 = Best Fit, 2 = Worst Fit
#define STRATEGY 0

void allocateMemory(int blockSize[], int blocks, int processSize[], int processes, int allocation[]) {
    int temp[MAX];
    memcpy(temp, blockSize, sizeof(int) * blocks);

    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
        int idx = -1;
        for (int j = 0; j < blocks; j++) {
            if (temp[j] >= processSize[i]) {
                if (STRATEGY == 0) { idx = j; break; }                            // First Fit
                if (STRATEGY == 1 && (idx == -1 || temp[j] < temp[idx])) idx = j; // Best Fit
                if (STRATEGY == 2 && (idx == -1 || temp[j] > temp[idx])) idx = j; // Worst Fit
            }
        }
        if (idx != -1) {
            allocation[i] = idx;
            temp[idx] -= processSize[i];
        }
    }
}

int main() {
    int blockSize[MAX], processSize[MAX], allocation[MAX], blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter sizes of %d blocks:\n", blocks);
    for (int i = 0; i < blocks; i++) scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of %d processes:\n", processes);
    for (int i = 0; i < processes; i++) scanf("%d", &processSize[i]);

    allocateMemory(blockSize, blocks, processSize, processes, allocation);

    printf("\t\nProcess\t\tSize\tBlock\n");
    for (int i = 0; i < processes; i++)
        printf("\t%d\t\t%d\t\t%s\n", i + 1, processSize[i],
               allocation[i] != -1 ? (char[5]){ '0' + allocation[i] + 1, 0 } : "Not Allocated");

    return 0;
}
