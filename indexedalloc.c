#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100

// Structure to represent an indexed file
typedef struct {
    int index_block;
    int allocated;
} File;

// Function prototypes
void initializeDisk(int disk[], int n);
void showBitVector(int disk[], int n);
void showDirectory(File directory[], int n);
void deleteFile(File directory[], int n, int file_index);
void menu();

int main() {
    int disk[MAX_BLOCKS];
    File directory[MAX_BLOCKS];
    int n, choice, file_index;
    
    // Seed the random number generator
    srand(time(NULL));
    
    printf("Enter the number of blocks in the disk: ");
    scanf("%d", &n);
    
    // Initialize the disk and directory
    initializeDisk(disk, n);
    for (int i = 0; i < n; i++) {
        directory[i].index_block = -1;
        directory[i].allocated = 0;
    }

    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showBitVector(disk, n);
                break;
            case 2:
                showDirectory(directory, n);
                break;
            case 3:
                printf("Enter the file index to delete: ");
                scanf("%d", &file_index);
                deleteFile(directory, n, file_index);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to initialize the disk with random allocation
void initializeDisk(int disk[], int n) {
    for (int i = 0; i < n; i++) {
        disk[i] = rand() % 2; // Randomly allocate blocks
    }
}

// Function to display the bit vector representing the disk
void showBitVector(int disk[], int n) {
    printf("Bit Vector (Disk):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

// Function to display the directory containing the index blocks
void showDirectory(File directory[], int n) {
    printf("Directory:\n");
    for (int i = 0; i < n; i++) {
        if (directory[i].allocated) {
            printf("File %d -> Index Block: %d\n", i, directory[i].index_block);
        }
    }
}

// Function to delete a file from the directory
void deleteFile(File directory[], int n, int file_index) {
    if (file_index >= 0 && file_index < n && directory[file_index].allocated) {
        directory[file_index].allocated = 0;
        printf("File %d deleted successfully.\n", file_index);
    } else {
        printf("Invalid file index or file not found.\n");
    }
}

// Function to display the menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Show Bit Vector\n");
    printf("2. Show Directory\n");
    printf("3. Delete File\n");
    printf("4. Exit\n");
}
