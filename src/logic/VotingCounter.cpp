#include "../../include/logic/VotingCounter.h"

std::unordered_set<std::string> VotingCounter::votedSet;

void VotingCounter::addVote(Blockchain *bcPtr, std::string data, std::string username) {
    Block lastBlock = bcPtr->blocks[bcPtr->length - 1];
    Block newBlock = createNewBlock(lastBlock, data.c_str(), username.c_str());
    if (isValidBlock(&lastBlock, &newBlock)) {
        addBlock(bcPtr, newBlock);
        VotingCounter::addToVoteSet(newBlock.username);
    }
}

bool VotingCounter::checkIfVoted(std::string username){
    return votedSet.find(username) != votedSet.end();
}

void VotingCounter::addToVoteSet(std::string username){
    votedSet.insert(username);
}

std::vector<std::pair<std::string, int>> VotingCounter::tallyAndSortVotes(Blockchain *bcPtr){
    std::unordered_map<std::string, int> voteTally;
    // Iterates through each block past the genesis
    for (int i = 1; i < bcPtr->length; i++){
        Block block = bcPtr->blocks[i];
        std::string username(block.data);
        // checks whether the candidate is in
        if (voteTally.find(username) != voteTally.end()) {
            voteTally[username]++;
        } else {
            voteTally[username] = 1;
        }
    }
    auto comp = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { 
        return a.second > b.second; 
    };
    std::vector<std::pair<std::string, int>> elems(voteTally.begin(), voteTally.end());
    std::sort(elems.begin(), elems.end(), comp);
    return elems;
}
