#include "../include/hashing.h"
#include "../include/utilities.h"
#include "../include/VotingCounter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
#include <fstream>
#include <iostream>

Block createGenesisBlock()
{
    Block genesisBlock;
    genesisBlock.index = 0;
    initializeHash(genesisBlock.previousHash);
    char timeString[20];
    getFormattedTime(timeString);
    strcpy(genesisBlock.timestamp, timeString);
    strcpy(genesisBlock.data, "Genesis Block");
    strcpy(genesisBlock.username, "None");
    genesisBlock.nonce = 0;

    // does proof of work
    char hashBuffer[256];
    char previousHashString[HASH_STRING_LENGTH];
    makeHashString(genesisBlock.previousHash, previousHashString);
    do
    {
        genesisBlock.nonce++;
        snprintf(hashBuffer, sizeof(hashBuffer), "%d%s%s%s%s%d", genesisBlock.index, genesisBlock.username, previousHashString, genesisBlock.timestamp, genesisBlock.data, genesisBlock.nonce);
        sha256(hashBuffer, genesisBlock.hash);
    } while (!meetsProofOfWork(genesisBlock.hash));
    return genesisBlock;
}

void addBlock(Blockchain *bc, Block newBlock)
{
    bc->blocks = (Block *)realloc(bc->blocks, (bc->length + 1) * sizeof(Block));
    bc->blocks[bc->length] = newBlock;
    bc->length++;
}

void createBlockchain(Blockchain *bc)
{
    bc->blocks = NULL;
    bc->length = 0;
    Block genesisBlock = createGenesisBlock();
    addBlock(bc, genesisBlock);
}

int isValidBlock(Block lastBlock, Block newBlock)
{
    if (lastBlock.index + 1 != newBlock.index)
    {
        return 0;
    }
    if (!compareHashes(lastBlock.hash, newBlock.previousHash))
    {
        return 0;
    }
    char hashBuffer[256];
    char previousHashString[HASH_STRING_LENGTH];
    makeHashString(newBlock.previousHash, previousHashString);
    snprintf(hashBuffer, sizeof(hashBuffer), "%d%s%s%s%s%d", newBlock.index, newBlock.username, previousHashString, newBlock.timestamp, newBlock.data, newBlock.nonce);
    u_int8_t hashOutput[32];
    sha256(hashBuffer, hashOutput);
    if (!compareHashes(hashOutput, newBlock.hash))
    {
        return 0;
    }
    // check if the user has already voted
    if (VotingCounter::checkIfVoted((std::string) newBlock.username)){
        return 0;
    }
    return 1;
}

Block createNewBlock(Block lastBlock, const char *data, const char *username)
{
    Block newBlock;
    newBlock.index = lastBlock.index + 1;
    copyHashes(lastBlock.hash, newBlock.previousHash);
    // Get current timestamp
    char timeString[20];
    getFormattedTime(timeString);
    strcpy(newBlock.timestamp, timeString);
    strcpy(newBlock.data, data);
    strcpy(newBlock.username, username);
    newBlock.nonce = 0;

    char hashBuffer[256];
    char previousHashString[HASH_STRING_LENGTH];
    makeHashString(newBlock.previousHash, previousHashString);
    do
    {
        newBlock.nonce++;
        snprintf(hashBuffer, sizeof(hashBuffer), "%d%s%s%s%s%d", newBlock.index, newBlock.username,previousHashString, newBlock.timestamp, newBlock.data, newBlock.nonce);
        sha256(hashBuffer, (uint8_t *)newBlock.hash);
    } while (!meetsProofOfWork(newBlock.hash));
    return newBlock;
}

void printBlockchain(Blockchain *bc)
{
    char hashString[HASH_STRING_LENGTH];
    for (int i = 0; i < bc->length; i++)
    {
        Block block = bc->blocks[i];
        printf("Block %d:\n", block.index);
        printf("  Nonce: %d\n", block.nonce);
        printf("  Timestamp: %s\n", block.timestamp);
        printf("  Username: %s\n", block.username);
        printf("  Data: %s\n", block.data);
        makeHashString(block.previousHash, hashString);
        printf("  Previous Hash: %s\n", hashString);
        makeHashString(block.hash, hashString);
        printf("  Hash: %s\n", hashString);
        printf("\n");
    }
}

void writeToWebsite(Blockchain *bc){
    std::ofstream file("./website/index.html");
    if (!file.is_open()) {
        std::cerr << "Error opening HTML file.\n";
        return;
    }
    // Puts out regular HTML layout stuff
    file << "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    file << "<title>Blockchain Viewer</title><link rel=\"stylesheet\" href=\"styles.css\"></head>";
    file << "<body><div class=\"blockchain-container\"><div class=\"blockchain\" id=\"blockchain\">";
    char hashString[HASH_STRING_LENGTH];
    for (int i = 0; i < bc->length; i++)
    {
        file << "<div class=\"block\">";
        Block block = bc->blocks[i];
        file << "<h2>Block " << block.index << "</h2>";
        file << "<p><strong>Nonce:</strong> " << block.nonce << "</p>";
        file << "<p><strong>Timestamp:</strong> " << block.timestamp << "</p>";
        file << "<p><strong>Username:</strong> " << block.username << "</p>";
        file << "<p><strong>Timestamp:</strong> " << block.data << "</p>";
        makeHashString(block.previousHash, hashString);
        file << "<p><strong>Previous Hash:</strong> " << hashString << "</p>";
        makeHashString(block.hash, hashString);
        file << "<p><strong>Hash:</strong> " << hashString << "</p>";
        file << "</div>";
    }
    file << "</div></div></body></html>";

    file.close();
}

void freeBlockchain(Blockchain *bc)
{
    free(bc);
}