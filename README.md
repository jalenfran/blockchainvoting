# blockchainvoting
Voting system with UI that is implemented using a decentralized blockchain
Features
- Response GUI that checks for invalid input
- Displays a website of the blockchain if requested
- Users can create accounts and login where their passwords are stored using salted hashing
- Utilizes multi-threading when "mining" or in other words doing proof of work
- Verifies users do not vote more than once and that the current blockchain is correct
- Can view results and blockchain in realtime from the GUI
How to use
- This project utilizes Qt 6.8.1 and Cmake
- Once those are downloaded follow these steps
1. mkdir bin
2. cd bin
3. cmake ..
4. make
5. Then run the output named votingGUI
