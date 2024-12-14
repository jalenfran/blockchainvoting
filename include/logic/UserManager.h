#include <unordered_map>
#include <string>

#define SALT_SIZE 16

class UserManager {
public:
    /**
     * Load the user database from a file
     * @pre fileName corresponds to a proper directory relative to the executabel
     * @post {userDatabase} will be updated to match the data in the file
     * @post {databaseFile} == fileName
     */
    static void loadUserDatabase(std::string fileName);
    /**
     * Save the user database to {databaseFile}.
     * @post all elements in {userDatabase} will be output into a file
     * at {databaseFile} with the format of pair.first pair.second separated
     * by new lines.
     */
    static void saveUserDatabase();

    /**
     * Registers a new user if the user is not in {userDatabase}.
     * @post returns true iff the username is not in {userDatabase} as a key
     * @post if we return true then a key value pair will be added into
     * {userDatabase} where the specified password is salted and then hashed
     */
    static bool registerUser(const std::string& username, const std::string& password);

    /**
     * Returns true iff the username and password combo is valid
     * @post returns true iff (username is in {userDatabase})
     * AND (the password salted and hashed matches the value found
     * at username in {userDatabase})
     */
    static bool authenticateUser(const std::string& username, const std::string& password);

    /**
     * Generates a random string of size {SALT_SIZE}
     * @post string returned will be random and of size {SALT_SIZE}
     */
    static std::string generateSalt();
private:
    // Stores username -> (salt, hashedPassword)
    static std::unordered_map<std::string, std::pair<std::string, std::string>> userDatabase;
    static std::string databaseFile;
};
