#include <stdint.h>
#include <string>

#define MAX_USERNAME_LENGTH 20

/* Contains what each block will have */
typedef struct Block {
    int index;
    int nonce;
    char timestamp[64];
    char data[21];
    char username[MAX_USERNAME_LENGTH+1];
    u_int8_t previousHash[32];
    u_int8_t hash[32];
} Block;

/* Contains the structure of the blockchain */
typedef struct Blockchain{
    Block *blocks;
    int length;
} Blockchain;

/**
 * Uses multi-threading to mine a block so that the hash fits requirements found in hash.h
 * @pre all struct info that the blockPtr points to has already been defined except nonce
 * @post If you hash the block after calling this method you will have the appropriate
 * number of zeros found in hash.h
 */
/* Method for mining a block */
void mineBlock(Block *blockPtr);

/* Method to mine a certain block range. returns true iff we find a valid nonce within [startNonce, endNonce)*/
/* only modifies hash and nonce variables iff we find a valid nonce */
/**
 * This method helps isolate the mining for each individual thread.
 * @pre hash has a size allocation of 32 elemetns
 * @post if found is true then the value that nonce holds is a nonce
 * that fits the requirements
 * @post if found is true then the hash is a copy of the hash found form the block
 */
void mineBlockRange(int startNonce, int endNonce, std::string initialString, uint8_t hash[], int *nonce, std::atomic<bool>& found);

/* Function to create first block */
/**
 * Function to create first block.
 * @post returns a Block that is defined and valid 
 */
Block createGenesisBlock();

/**
 * Takes in the current blockchain and a newly created block to add it to the chain.
 * @post bc->length = bc->length +1
 * @post the last element in the blockchain is newBlock
 */
void addBlock(Blockchain *bc, Block newBlock);

/**
 * Takes a pointer to a blockchain and creates the chain by also making the genesis block.
 * @post bcPtr points to a blockchain with a valid genesis block.
 */
void createBlockchain(Blockchain *bcPtr);

/**
 * Verifies whether a new block and the previous block are valid by checking 
 * indices and hashes and then checks to make sure block.hash is the same. Also checks
 * if the user has already voted.
 * @pre lastBlock is defined
 * @pre newBlock is defined
 * @post returns true iff (newBlockPtr->index == lastBlockPtr->index+1)
 * AND (newBlockPtr->previousHash == lastBlockPtr->hash)
 * AND (newBlockPtr->username has only voted once)
 */
bool isValidBlock(Block *lastBlockPtr, Block *newBlockPtr);

/*
* This method takes in the previous block in the chain and takes in
* the string data (voting) and constructs a block based on that. 
* Then, it does a proof of work and returns the newest block
*/
Block createNewBlock(Block lastBlock, const char *data, const char *username);

/**
 * Takes a blockchain pointer and prints out each block,
 * @pre bcPtr points to a valid blockchain implemented with contigious memory allocation
 */
void printBlockchain(Blockchain *bcPtr);

/**
 * Takes a blockchain pointer and prints out each block in a formatted HTML
 * @pre bcPtr points to a valid blockchain implemented with contigious memory allocation
 * @post a formatted website will be output at the fileName
 */
void writeToWebsite(Blockchain *bcPtr, std::string fileName);

/**
 * Frees allocated memory for blockchain
 * @pre bcPtr points to a valid blockchain implemented with contigious memory allocation
 */
void freeBlockchain(Blockchain *bcPtr);

