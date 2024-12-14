#include "blockchain.h"
#include <unordered_set>
#include <string>

class VotingCounter {
public:

    /**
     * Adds a vote to the blockchain.
     * @pre the blockchain pointed to by bcPtr is in contigious memory
     * @post creates a new block with the specified username and voting data
     * and adds it to the end of the blockchain pointed to by bcPtr iff
     * the block is deemed valid (found in blockchain.h)
     * @post if the block is deemed valid then the username is added into
     * {votedSet}
     */
    static void addVote(Blockchain *bcPtr, std::string data, std::string username);
    
    /**
     * method checks whether a user has already voted
     * @post returns true iff username is in {votedSet}
     */
    static bool checkIfVoted(std::string username);

    /**
     * method adds a string into the set
     * @pre username is not already in {votedSet}
     * @post username is now in {votedSet}
     */
    static void addToVoteSet(std::string username);

    /**
     * tallies up all the votes given a blockchain head returning an unordered map
     * @pre the blockchain pointed to by bcPtr is in contigious memory
     * @post the vector pair returned is an descending order by the values in the values of the pair
     * @post the vector contains the data value from each block and tallies up how many times it is
     * referenced in the blocks excluding the genesis block.
     */
    static std::vector<std::pair<std::string, int>> tallyAndSortVotes(Blockchain *bcPtr);
    
private:
    static std::unordered_set<std::string> votedSet;
};
