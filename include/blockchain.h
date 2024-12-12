#include <stdint.h>

/* Contains what each block will have */
typedef struct Block {
    int index;
    int nonce;
    char timestamp[64];
    char data[256];
    u_int8_t previousHash[32];
    u_int8_t hash[32];
} Block;

/* Contains the structure of the blockchain */
typedef struct Blockchain{
    Block *blocks;
    int length;
} Blockchain;

/* Function to create first block */
Block createGenesisBlock();

/* Takes in the current blockchain and a newly created block to add it to the chain */
void addBlock(Blockchain *bc, Block newBlock);

/* Takes a pointer to a blockchain and creates the chain by also making the genesis block */
void createBlockchain(Blockchain *bc);

/* 
* Verifies whether a new block and the previous block are valid by checking 
* indices and hashes and then checks to make sure block.hash is the same 
*/
int isValidBlock(Block lastBlock, Block newBlock);

/*
* This method takes in the previous block in the chain and takes in
* the string data (voting) and constructs a block based on that. 
* Then, it does a proof of work and returns the newest block
*/
Block createNewBlock(Block lastBlock, const char *data);

/* Takes a blockchain pointer and prints out each block */
void printBlockchain(Blockchain *bc);

/* Frees allocated memory for blockchain */
void freeBlockchain(Blockchain *bc);