#include "../include/blockchain.h"
#include "../include/hashing.h"
#include "../include/utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Block createGenesisBlock() {
    Block genesisBlock;
    genesisBlock.index = 0;
    initializeHash(genesisBlock.previousHash);
    char timeString[20];
    getFormattedTime(timeString);
    strcpy(genesisBlock.data, "Genesis Block");
    genesisBlock.nonce = 0;

    // does proof of work
    char hashBuffer[256];
    char previousHashString[65];
    makeHashString(genesisBlock.previousHash, previousHashString);
    do {
        genesisBlock.nonce++;
        sprintf(hashBuffer, "%d%s%s%s%d", genesisBlock.index, previousHashString, genesisBlock.timestamp, genesisBlock.data, genesisBlock.nonce);
        sha256(hashBuffer, genesisBlock.hash);
    } while (!meetsProofOfWork(genesisBlock.hash));
    return genesisBlock;
}

void addBlock(Blockchain *bc, Block newBlock) {
    bc->blocks = realloc(bc->blocks, (bc->length + 1) * sizeof(Block));
    bc->blocks[bc->length] = newBlock;
    bc->length++;
}

void createBlockchain(Blockchain *bc) {
    bc->blocks = NULL;
    bc->length = 0;
    Block genesisBlock = createGenesisBlock();
    addBlock(bc, genesisBlock);
}


int isValidBlock(Block lastBlock, Block newBlock) {
    if (lastBlock.index + 1 != newBlock.index) {
        return 0;
    }
    if (!compareHashes(lastBlock.hash, newBlock.previousHash)) {
        return 0;
    }
    char hashBuffer[256];
    char previousHashString[65];
    makeHashString(newBlock.previousHash, previousHashString);
    sprintf(hashBuffer, "%d%s%s%s%d", newBlock.index, previousHashString, newBlock.timestamp, newBlock.data, newBlock.nonce);
    u_int8_t hashOutput[32];
    sha256(hashBuffer, hashOutput);
    if (!compareHashes(hashOutput, newBlock.hash)) {
        return 0;
    }
    return 1;
}

Block createNewBlock(Block lastBlock, const char *data) {
    Block newBlock;
    newBlock.index = lastBlock.index + 1;
    copyHashes(lastBlock.hash, newBlock.previousHash);
    // Get current timestamp
    char timeString[20];
    getFormattedTime(timeString);
    strcpy(newBlock.timestamp, timeString); 
    strcpy(newBlock.data, data);
    newBlock.nonce = 0;

    char hashBuffer[256];
    char previousHashString[65];
    makeHashString(newBlock.previousHash, previousHashString);
    do {
        newBlock.nonce++;
        sprintf(hashBuffer, "%d%s%s%s%d", newBlock.index, previousHashString, newBlock.timestamp, newBlock.data, newBlock.nonce);
        sha256(hashBuffer, (uint8_t *)newBlock.hash );
    } while (!meetsProofOfWork(newBlock.hash)); 
    return newBlock;
}

void printBlockchain(Blockchain *bc) {
    char hashString[65];
    for (int i = 0; i < bc->length; i++) {
        Block block = bc->blocks[i];
        printf("Block %d:\n", block.index);
        printf("  Nonce: %d\n", block.nonce);
        printf("  Timestamp: %s\n", block.timestamp);
        printf("  Data: %s\n", block.data);
        makeHashString(block.previousHash, hashString);
        printf("  Previous Hash: %s\n", hashString);
        makeHashString(block.hash, hashString);
        printf("  Hash: %s\n", hashString);
        printf("\n");
    }
}

void freeBlockchain(Blockchain *bc){
    free(bc);
}
