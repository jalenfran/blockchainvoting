#include "../include/UserManager.h"
#include "../include/VotingCounter.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

int main()
{
    Blockchain bc;
    createBlockchain(&bc);

    // Load the user database from the file
    UserManager::loadUserDatabase();

    std::cout << "Welcome to the Blockchain Voting System\n";

    int choice = 1;
    while (choice != 4)
    {
        std::string username;
        std::string password;

        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. View Blockchain\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore the newline character after std::cin

        switch (choice)
        {
        case 1:
            // Register a new user
            std::cout << "Enter username: ";
            std::getline(std::cin, username);

            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            UserManager::registerUser(username, password);
            break;
        case 2:
            // Authenticate an existing user
            std::cout << "Enter username: ";
            std::getline(std::cin, username);

            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            if (UserManager::authenticateUser(username, password))
            {
                std::string vote;
                std::cout << "Who do you wish to vote for: ";
                std::getline(std::cin, vote);
                VotingCounter::addVote(&bc, vote.c_str(), username.c_str());
            }
            break;
        case 3:
            printBlockchain(&bc);
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cerr << "Invalid choice.\n";
            break;
        }
    }

    std::vector<std::pair<std::string, int>> results = VotingCounter::tallyAndSortVotes(&bc);


    for (const auto& pair : results) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }



    printBlockchain(&bc);
    writeToWebsite(&bc);

    free(bc.blocks);
    return 0;
}
