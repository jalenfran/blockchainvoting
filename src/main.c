#include "../include/voting.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Blockchain bc;
    createBlockchain(&bc);

    addVote(&bc, "Voter1: CandidateA");
    addVote(&bc, "Voter2: CandidateB");
    addVote(&bc, "Voter3: CandidateA");

    printBlockchain(&bc);

    free(bc.blocks);
    return 0;
}

