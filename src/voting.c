#include "../include/voting.h"

void addVote(Blockchain *bc, const char *voteData) {
    Block lastBlock = bc->blocks[bc->length - 1];
    Block newBlock = createNewBlock(lastBlock, voteData);
    if (isValidBlock(lastBlock, newBlock)) {
        addBlock(bc, newBlock);
    }
}
