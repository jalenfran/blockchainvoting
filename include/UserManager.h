#include <unordered_map>
#include <string>

#define DATABASE_FILE "./data/users.txt" 

class UserManager {
public:
    // Load the user database from a file
    static void loadUserDatabase();

    // Save the user database to a file
    static void saveUserDatabase();

    // Register a new user
    static bool registerUser(const std::string& username, const std::string& password);

    // Authenticate a user
    static bool authenticateUser(const std::string& username, const std::string& password);
private:
    static std::unordered_map<std::string, std::string> userDatabase;
};