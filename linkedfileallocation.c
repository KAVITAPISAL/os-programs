#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_BLOCKS 100

// Structure to represent a disk block
typedef struct Block {
    int blockNumber;
    bool allocated;
    struct Block* next;
} Block;

// Function prototypes
void initializeDisk(int n, Block** disk);
void showBitVector(int n, Block* disk);
void createNewFile(int n, Block* disk);
void showDirectory(int n, Block* disk);

int main() {
    int n;
    printf("Enter the number of blocks in the disk: ");
    scanf("%d", &n);

    Block* disk[MAX_BLOCKS] = {NULL}; // Initialize disk blocks as free

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
                createNewFile(n, disk);
                break;
            case 3:
                showDirectory(n, disk);
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
void initializeDisk(int n, Block** disk) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        // Randomly mark some blocks as allocated (occupied)
        if (rand() % 2 == 1) {
            disk[i] = (Block*)malloc(sizeof(Block));
            disk[i]->blockNumber = i;
            disk[i]->allocated = true;
            disk[i]->next = NULL;
        }
    }
}

// Function to display the bit vector of the disk
void showBitVector(int n, Block* disk[]) {
    printf("Bit Vector (Disk Status):\n");
    for (int i = 0; i < n; i++) {
        if (disk[i] != NULL && disk[i]->allocated) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

// Function to create a new file
void createNewFile(int n, Block* disk[]) {
    printf("Enter the starting block number for the new file: ");
    int startBlock;
    scanf("%d", &startBlock);

    if (startBlock < 0 || startBlock >= n) {
        printf("Invalid starting block number.\n");
        return;
    }

    if (disk[startBlock] != NULL && disk[startBlock]->allocated) {
        printf("Error: Starting block is already allocated.\n");
        return;
    }

    disk[startBlock] = (Block*)malloc(sizeof(Block));
    disk[startBlock]->blockNumber = startBlock;
    disk[startBlock]->allocated = true;
    disk[startBlock]->next = NULL;

    printf("File created successfully.\n");
}

// Function to show the directory
void showDirectory(int n, Block* disk[]) {
    printf("Directory (List of allocated blocks):\n");
    for (int i = 0; i < n; i++) {
        if (disk[i] != NULL && disk[i]->allocated) {
            printf("Block %d - File\n", i);
        }
    }
}