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
            if (temp[j] < processSize[i]) continue;

            if (STRATEGY == 0) { // First Fit
                idx = j;
                break;
            } else if (STRATEGY == 1) { // Best Fit
                if (idx == -1 || temp[j] < temp[idx]) idx = j;
            } else if (STRATEGY == 2) { // Worst Fit
                if (idx == -1 || temp[j] > temp[idx]) idx = j;
            }
        }

        if (idx != -1) {
            allocation[i] = idx;
            temp[idx] -= processSize[i];
        }
    }
}

int main() {
    int blockSize[MAX], processSize[MAX], allocation[MAX];
    int blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter sizes of %d blocks:\n", blocks);
    for (int i = 0; i < blocks; i++) scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of %d processes:\n", processes);
    for (int i = 0; i < processes; i++) scanf("%d", &processSize[i]);

    allocateMemory(blockSize, blocks, processSize, processes, allocation);

    printf("\nProcess\t\tSize\tBlock\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("\t%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
    }

    return 0;
}
