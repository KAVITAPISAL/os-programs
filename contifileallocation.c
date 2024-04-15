#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_BLOCKS 100

// Function prototypes
void initializeDisk(int n,bool disk[]);
void showBitVector(int n, bool disk[]);
void createNewFile(int n, bool disk[], int fileBlocks[]);
void showDirectory(int n, bool disk[], int fileBlocks[]);

int main() {
    int n;
    printf("Enter the number of blocks in the disk: ");
    scanf("%d", &n);
    
    bool disk[MAX_BLOCKS] = {false}; // Initialize disk blocks as free
    int fileBlocks[MAX_BLOCKS] = {0}; // Initialize file block array

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showBitVector(n, disk);
                break;
            case 2:
                createNewFile(n, disk, fileBlocks);
                break;
            case 3:
                showDirectory(n, disk, fileBlocks);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to initialize disk blocks as free
void initializeDisk(int n,bool disk[]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        // Randomly mark some blocks as allocated (occupied)
        if (rand() % 2 == 1) {
            printf("Block %d is allocated.\n", i);
            disk[i] = true;
        }
    }
}

// Function to display the bit vector of the disk
void showBitVector(int n, bool disk[]) {
    printf("Bit Vector (Disk Status):\n");
    for (int i = 0; i < n; i++) {
        if (disk[i]) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

// Function to create a new file
void createNewFile(int n, bool disk[], int fileBlocks[]) {
    printf("Enter the starting block number for the new file: ");
    int startBlock;
    scanf("%d", &startBlock);

    printf("Enter the number of blocks required for the new file: ");
    int numBlocks;
    scanf("%d", &numBlocks);

    bool canAllocate = true;
    for (int i = startBlock; i < startBlock + numBlocks; i++) {
        if (disk[i]) {
            canAllocate = false; // Some blocks are already allocated
            break;
        }
    }

    if (canAllocate) {
        for (int i = startBlock; i < startBlock + numBlocks; i++) {
            disk[i] = true;
            fileBlocks[i - startBlock] = i;
        }
        printf("File created successfully.\n");
    } else {
        printf("Error: Some blocks are already allocated. Cannot create file.\n");
    }
}

// Function to show the directory
void showDirectory(int n, bool disk[], int fileBlocks[]) {
    printf("Directory (List of allocated blocks):\n");
    for (int i = 0; i < n; i++) {
        if (disk[i]) {
            printf("Block %d - File\n", i);
        }
    }
    printf("File Blocks:\n");
    for (int i = 0; i < n; i++) {
        if (fileBlocks[i] != 0) {
            printf("%d ", fileBlocks[i]);
        }
    }
    printf("\n");
}