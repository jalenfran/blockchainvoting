#include "../../include/logic/UserManager.h"
#include "../../include/logic/hashing.h"
#include "../../include/logic/blockchain.h"
#include <iostream>
#include <fstream>
#include <random>

std::unordered_map<std::string, std::pair<std::string, std::string>> UserManager::userDatabase; 

std::string UserManager::databaseFile;

std::string UserManager::generateSalt() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(charset) - 2); // -2 to exclude the null terminator

    std::string salt;
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        salt += charset[dis(gen)];
    }

    return salt;
}

void UserManager::loadUserDatabase(std::string fileName) {
    databaseFile = fileName;
    std::ifstream file(databaseFile);
    if (!file.is_open()) {
        std::cerr << "Error opening database file.\n";
        return;
    }

    std::string username, salt, hashedPassword;
    while (file >> username >> salt >> hashedPassword) {
        userDatabase[username] = std::make_pair(salt, hashedPassword);;
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
        file << entry.first << " " << entry.second.first << " " << entry.second.second << "\n";
    }

    file.close();
}

bool UserManager::registerUser(const std::string& username, const std::string& password) {
    if (userDatabase.find(username) != userDatabase.end()) {
        std::cerr << "Username already exists.\n";
        return false;
    }

    std::string salt = generateSalt();
    std::string saltedPassword = password + salt;

    // computes the hash
    u_int8_t hashOutput[32];
    sha256(saltedPassword.c_str(), hashOutput);
    char hashedPassword[HASH_STRING_LENGTH];
    // finds the string
    makeHashString(hashOutput, hashedPassword);
    userDatabase[username] = std::make_pair(salt, std::string(hashedPassword));
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

    // gets salted password
    std::string salt = it->second.first;
    std::string saltedPassword = password + salt;

    u_int8_t hashOutput[32];
    sha256(saltedPassword.c_str(), hashOutput);
    char hashedPassword[HASH_STRING_LENGTH];
    makeHashString(hashOutput, hashedPassword);

    if (!strcmp(hashedPassword, it->second.second.c_str())) {
        std::cout << "Login successful. You can now vote!\n";
        return true;
    }

    std::cerr << "Authentication failed.\n";
    return false;
}
