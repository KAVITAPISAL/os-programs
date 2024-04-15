#include<stdio.h>
#include<stdbool.h>

#define P_COUNT 6 // Number of processes
#define R_COUNT 4 // Number of resource types

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R_COUNT], int alloc[][R_COUNT]) {
    int need[P_COUNT][R_COUNT];
    int finish[P_COUNT] = {0};
    int safeSeq[P_COUNT];
    int work[R_COUNT];
    int i, j, k;
    int count = 0;

    // Initialize need matrix
    for (i = 0; i < P_COUNT; i++) {
        for (j = 0; j < R_COUNT; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize work as available matrix
    for (i = 0; i < R_COUNT; i++) {
        work[i] = avail[i];
    }

    // Find a safe sequence
    while (count < P_COUNT) 
    {
        bool found = false;
        for (i = 0; i < P_COUNT; i++) 
        {
            // 0=false 1=true 
            //if(!(0)) = true
            if (!finish[i]) 
            {
                bool canProcess = true;
                for (j = 0; j < R_COUNT; j++) {
                    if (need[i][j] > work[j]) {
                        canProcess = false;
                        break;
                    }
                }
                if (canProcess) {
                    for (k = 0; k < R_COUNT; k++) {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) 
        {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < P_COUNT; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int alloc[P_COUNT][R_COUNT] = {{0, 3, 2, 4},
                                    {1, 2, 0, 1},
                                    {0, 0, 0, 0},
                                    {3, 3, 2, 2},
                                    {1, 4, 3, 2},
                                    {2, 4, 1, 4}};
    int max[P_COUNT][R_COUNT] = {{6, 5, 4, 4},
                                  {4, 4, 4, 4},
                                  {0, 0, 1, 2},
                                  {3, 9, 3, 4},
                                  {2, 5, 3, 3},
                                  {4, 6, 3, 4}};
    int avail[R_COUNT] = {3, 4, 4, 2};

    // Calculate and display the content of need matrix
    printf("Need Matrix:\n");
    int need[P_COUNT][R_COUNT];
    for (int i = 0; i < P_COUNT; i++) {
        for (int j = 0; j < R_COUNT; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check if the system is in a safe state
    isSafe(NULL, avail, max, alloc);

    return 0;
}