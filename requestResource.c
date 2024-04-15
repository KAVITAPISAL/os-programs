#include<stdio.h>
#include<stdbool.h>
#define P_COUNT 5 // Number of processes
#define R_COUNT 4 // Number of resource types
// Function to check if the system is in a safe state after granting a resource request
bool isSafe(int available[], int max[][R_COUNT], int allocation[][R_COUNT], int request[], int pid) {
    int need[P_COUNT][R_COUNT];
    bool finish[P_COUNT] = {false};
    int work[R_COUNT];
    int safeSeq[P_COUNT];
    int i, j;

    // Calculate need matrix
    for (i = 0; i < P_COUNT; i++) {
        for (j = 0; j < R_COUNT; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check if the request can be granted
    for (j = 0; j < R_COUNT; j++) {
        if (request[j] > need[pid][j] || request[j] > available[j]) {
            printf("Request cannot be granted as it exceeds maximum needs or available resources.\n");
            return false;
        }
    }

    // Temporarily allocate resources for the request
    for (j = 0; j < R_COUNT; j++) {
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j] -= request[j];
    }

    // Check if the system is in a safe state
    int count = 0;
    while (count < P_COUNT) {
        bool found = false;
        for (i = 0; i < P_COUNT; i++) {
            if (!finish[i]) {
                bool canProcess = true;
                for (j = 0; j < R_COUNT; j++) {
                    if (need[i][j] > available[j]) {
                        canProcess = false;
                        break;
                    }
                }
                if (canProcess) {
                    // Grant the request temporarily
                    for (j = 0; j < R_COUNT; j++) {
                        available[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }
        // If no process was found, the system is in an unsafe state
        if (!found) {
            // Roll back the resource allocation for the request
            for (j = 0; j < R_COUNT; j++) {
                available[j] += request[j];
                allocation[pid][j] -= request[j];
                need[pid][j] += request[j];
            }
            return false;
        }
    }

    // If all processes were executed safely, the system is in a safe state
    return true;
}

int main() {
    int allocation[P_COUNT][R_COUNT] = {{0, 0, 1, 2},
                                         {1, 0, 0, 0},
                                         {1, 3, 5, 4},
                                         {0, 6, 3, 2},
                                         {0, 0, 1, 4}};
    int max[P_COUNT][R_COUNT] = {{0, 0, 1, 2},
                                  {1, 7, 5, 0},
                                  {2, 3, 5, 6},
                                  {0, 6, 5, 2},
                                  {0, 6, 5, 6}};
    int available[R_COUNT] = {1, 5, 2, 0};

    // Example: Process P1 requests resources [0, 0, 2, 0]
    int request[R_COUNT] = {0, 0, 2, 0};
    int pid = 1; // Process P1

    // Check if the request can be granted without causing deadlock
    if (isSafe(available, max, allocation, request, pid)) {
        printf("The request can be granted without causing deadlock.\n");
    } else {
        printf("The request cannot be granted to avoid deadlock.\n");
    }

    return 0;
}