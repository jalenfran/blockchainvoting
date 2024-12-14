#include "../../include/logic/UserManager.h"
#include "../../include/logic/hashing.h"
#include "../../include/logic/blockchain.h"
#include <iostream>
#include <fstream>

std::unordered_map<std::string, std::string> UserManager::userDatabase;

std::string UserManager::salt = "*]2>;YVT+S^z!;<=";

std::string UserManager::databaseFile;

void UserManager::loadUserDatabase(std::string fileName) {
    databaseFile = fileName;
    std::ifstream file(databaseFile);
    if (!file.is_open()) {
        std::cerr << "Error opening database file.\n";
        return;
    }

    std::string username, hashedPassword;
    while (file >> username >> hashedPassword) {
        userDatabase[username] = hashedPassword;
    }

    file.close();
}

void UserManager::saveUserDatabase() {
    std::ofstream file(databaseFile, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error opening database file.\n";
        return;
    }

    for (const auto& entry : userDatabase) {
        file << entry.first << " " << entry.second << "\n";
    }

    file.close();
}

bool UserManager::registerUser(const std::string& username, const std::string& password) {
    if (userDatabase.find(username) != userDatabase.end()) {
        std::cerr << "Username already exists.\n";
        return false;
    }

    // adds salt to password
    std::string saltedPassword = password +  UserManager::salt;

    // computes the hash
    u_int8_t hashOutput[32];
    sha256(saltedPassword.c_str(), hashOutput);
    char hashedPassword[HASH_STRING_LENGTH];
    // finds the string
    makeHashString(hashOutput, hashedPassword);
    userDatabase[username] = std::string(hashedPassword);
    saveUserDatabase();
    std::cout << "User registered successfully.\n";
    return true;
}

// Function to authenticate a user
bool UserManager::authenticateUser(const std::string& username, const std::string& password) {
    auto it = userDatabase.find(username);
    if (it == userDatabase.end()) {
        std::cerr << "Authentication failed.\n";
        return false;
    }

    // adds salt to password
    std::string saltedPassword = password + UserManager::salt;

    u_int8_t hashOutput[32];
    sha256(saltedPassword.c_str(), hashOutput);
    char hashedPassword[HASH_STRING_LENGTH];
    makeHashString(hashOutput, hashedPassword);

    if (!strcmp(hashedPassword, it->second.c_str())) {
        std::cout << "Login successful. You can now vote!\n";
        return true;
    }

    std::cerr << "Authentication failed.\n";
    return false;
}
