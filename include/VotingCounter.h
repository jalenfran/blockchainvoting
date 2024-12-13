#include "../include/blockchain.h"
#include <unordered_set>
#include <string>

class VotingCounter {
public:
    // adds a vote to the blockchain
    static void addVote(Blockchain *bc, const char *voteData, const char *username);

    // method checks whether a user has already voted
    static bool checkIfVoted(std::string username);

    // method adds a string into the set
    static void addToVoteSet(std::string username);

    // tallies up all the votes given a blockchain head returning an unordered map
    static std::vector<std::pair<std::string, int>> tallyAndSortVotes(Blockchain *bc);
    
private:
    static std::unordered_set<std::string> votedSet;
};