#include <stdio.h>

int main() {
    int n, m; // n = processes, m = resource types
    printf("Enter number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++) scanf("%d", &avail[i]);

    int finish[n], safeSeq[n], index = 0;
    for(int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;
    while(count < n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < m; j++)
                    if(need[i][j] > avail[j]) break;
                if(j == m) {
                    for(int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[index++] = i;
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if(!found) break; // system not safe
    }

    if(count == n) {
        printf("System is in a safe state.\nSafe Sequence: ");
        for(int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }

    return 0;
}
