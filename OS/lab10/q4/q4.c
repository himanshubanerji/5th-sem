#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BLOCKS 100
#define BAD_BLOCK_MARKER -1

int disk[MAX_BLOCKS]; // Simulated disk blocks
int badBlocks[MAX_BLOCKS]; // Bad blocks table

void initializeFileSystem() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i] = i; // Contiguous allocation
        badBlocks[i] = -1; // Initialize bad blocks table
    }
}

void markBlockAsBad(int blockNumber) {
    badBlocks[blockNumber] = BAD_BLOCK_MARKER;
}

int allocateSpareBlock() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (badBlocks[i] == -1) {
            badBlocks[i] = i; // Mark it as used
            return i;
        }
    }
    return -1; // No spare blocks available
}

int readBlock(int blockNumber) {
    if (blockNumber < 0 || blockNumber >= MAX_BLOCKS) {
        printf("Invalid block number\n");
        return -1;
    }

    int realBlockNumber = disk[blockNumber];
    if (badBlocks[realBlockNumber] == BAD_BLOCK_MARKER) {
        printf("Block %d is marked as bad, allocating a spare block...\n", realBlockNumber);
        int spareBlock = allocateSpareBlock();
        if (spareBlock == -1) {
            printf("No spare blocks available. Cannot read block.\n");
            return -1;
        }
        disk[blockNumber] = spareBlock;
        printf("Spare block %d allocated for block %d\n", spareBlock, realBlockNumber);
        return spareBlock;
    }

    return realBlockNumber;
}

int main() {
    initializeFileSystem();

    // Simulate marking a block as bad
    markBlockAsBad(5);

    // Read block 5, which is marked as bad
    int data = readBlock(5);

    if (data != -1) {
        printf("Data read from block %d: %d\n", 5, data);
    }

    return 0;
}
