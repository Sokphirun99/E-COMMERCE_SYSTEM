#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
#include <vector>
#include "Account.h"

class AuthManager {
private:
    std::vector<Account> accounts;
    std::string currentUsername;
    std::string currentUserRole;
    bool isLoggedIn;

public:
    // Constructor
    AuthManager();

    // User authentication
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool registerUser(const Account& newAccount);
    bool isUsernameTaken(const std::string& username) const;
    
    // User management
    const std::vector<Account>& getAllAccounts() const { return accounts; }
    Account* getCurrentAccount();
    Account* getAccountByUsername(const std::string& username);
    void saveAccounts();
    
    // Session information
    bool userIsLoggedIn() const { return isLoggedIn; }
    bool userIsAdmin() const { return currentUserRole == "admin"; }
    std::string getCurrentUsername() const { return currentUsername; }
    std::string getCurrentUserRole() const { return currentUserRole; }
};

#endif // AUTH_MANAGER_H
