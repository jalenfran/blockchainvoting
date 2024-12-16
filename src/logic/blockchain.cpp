#include "../../include/logic/hashing.h"
#include "../../include/logic/utilities.h"
#include "../../include/logic/VotingCounter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <atomic>

void mineBlock(Block *blockPtr){
    char previousHashString[HASH_STRING_LENGTH];
    makeHashString(blockPtr->previousHash, previousHashString);
    std::string initialString = std::to_string(blockPtr->index) + blockPtr->username + previousHashString + blockPtr->timestamp + blockPtr->data;
    const int numThreads = std::thread::hardware_concurrency(); // gets number of threads
    const long rangePerThread = (LONG_MAX) / numThreads; 
    std::atomic<bool> found(false); 
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        long threadStart = i * rangePerThread;
        long threadEnd = threadStart + rangePerThread;

        // Start a new thread for each range
        threads.push_back(std::thread([&, threadStart, threadEnd] {
            if (!found.load()) { // Check if a solution hasn't already been found
                mineBlockRange(threadStart, threadEnd, initialString, blockPtr->hash, &(blockPtr->nonce), found);
            }
        }));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }
}

void mineBlockRange(long startNonce, long endNonce, std::string initialString, uint8_t hash[], long *nonce, std::atomic<bool>& found){
    for (long i = startNonce; i < endNonce; i++){
        if (found.load()) return; // makes sure we stop if a thread has found a hash
        std::string testString = initialString + std::to_string(i); // gathers string with nonce
        uint8_t testHash[32];
        sha256(testString.c_str(), testHash);
        if (meetsProofOfWork(testHash)){
            *nonce = i;
            copyHashes(testHash, hash);
            found.store(true); 
            return;
        }
    }
}

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

    mineBlock(&genesisBlock);
    return genesisBlock;
}

void addBlock(Blockchain *bc, Block newBlock)
{
    bc->blocks = (Block *)realloc(bc->blocks, (bc->length + 1) * sizeof(Block));
    bc->blocks[bc->length] = newBlock;
    bc->length++;
}

void createBlockchain(Blockchain *bcPtr)
{
    bcPtr->blocks = NULL;
    bcPtr->length = 0;
    Block genesisBlock = createGenesisBlock();
    addBlock(bcPtr, genesisBlock);
}

bool isValidBlock(Block *lastBlockPtr, Block *newBlockPtr)
{
    if (lastBlockPtr->index + 1 != newBlockPtr->index)
    {
        return false;
    }
    if (!compareHashes(lastBlockPtr->hash, newBlockPtr->previousHash))
    {
        return false;
    }
    std::string hashBuffer;
    char previousHashString[HASH_STRING_LENGTH];
    makeHashString(newBlockPtr->previousHash, previousHashString);
    hashBuffer = std::to_string(newBlockPtr->index) + newBlockPtr->username + previousHashString + newBlockPtr->timestamp + newBlockPtr->data + std::to_string(newBlockPtr->nonce);
    uint8_t hashOutput[32];
    sha256(hashBuffer.c_str(), hashOutput);
    if (!compareHashes(hashOutput, newBlockPtr->hash))
    {
        return false;
    }
    // check if the user has already voted
    if (VotingCounter::checkIfVoted((std::string) newBlockPtr->username)){
        return false;
    }
    return true;
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

    mineBlock(&newBlock);
    return newBlock;
}

void printBlockchain(Blockchain *bcPtr)
{
    char hashString[HASH_STRING_LENGTH];
    for (int i = 0; i < bcPtr->length; i++)
    {
        Block block = bcPtr->blocks[i];
        printf("Block %d:\n", block.index);
        printf("  Nonce: %ld\n", block.nonce);
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

void writeToWebsite(Blockchain *bcPtr, std::string fileName){
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening HTML file.\n";
        return;
    }
    // Puts out regular HTML layout stuff
    file << "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << std::endl;
    file << "<title>Blockchain Viewer</title><link rel=\"stylesheet\" href=\"styles.css\"></head>" << std::endl;
    file << "<body><div class=\"blockchain-container\"><div class=\"blockchain\" id=\"blockchain\">" << std::endl;
    char hashString[HASH_STRING_LENGTH];
    for (int i = 0; i < bcPtr->length; i++)
    {
        file << "<div class=\"block\">" << std::endl;
        Block block = bcPtr->blocks[i];
        file << "<h2>Block " << block.index << "</h2>" << std::endl;
        file << "<p><strong>Nonce:</strong> " << block.nonce << "</p>" << std::endl;
        file << "<p><strong>Timestamp:</strong> " << block.timestamp << "</p>" << std::endl;
        file << "<p><strong>Username:</strong> " << block.username << "</p>" << std::endl;
        file << "<p><strong>Timestamp:</strong> " << block.data << "</p>" << std::endl;
        makeHashString(block.previousHash, hashString);
        file << "<p><strong>Previous Hash:</strong><br> " << hashString << "</p>" << std::endl;
        makeHashString(block.hash, hashString);
        file << "<p><strong>Hash:</strong><br> " << hashString << "</p>" << std::endl;
        file << "</div>" << std::endl;
    }
    file << "</div></div></body></html>";

    file.close();
}

void freeBlockchain(Blockchain *bcPtr)
{
    free(bcPtr);
}
