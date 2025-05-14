#include "AuthManager.h"
#include "FileManager.h"
#include <iostream>

AuthManager::AuthManager() : isLoggedIn(false) {
    accounts = FileManager::loadAccounts();
}

bool AuthManager::login(const std::string& username, const std::string& password) {
    for (const auto& acc : accounts) {
        if (acc.getUsername() == username && acc.getPassword() == password) {
            currentUserRole = acc.getRole();
            currentUsername = acc.getUsername();
            isLoggedIn = true;
            
            std::cout << "✅ Login successful! Role: " << currentUserRole << std::endl;
            return true;
        }
    }
    
    std::cout << "❌ Invalid username or password.\n";
    return false;
}

void AuthManager::logout() {
    currentUsername = "";
    currentUserRole = "";
    isLoggedIn = false;
}

bool AuthManager::registerUser(const Account& newAccount) {
    if (isUsernameTaken(newAccount.getUsername())) {
        std::cout << "❌ Username already exists. Please choose another.\n";
        return false;
    }
    
    accounts.push_back(newAccount);
    FileManager::saveAccounts(accounts);
    std::cout << "✅ Registration successful! You can now log in.\n";
    return true;
}

bool AuthManager::isUsernameTaken(const std::string& username) const {
    for (const auto& acc : accounts) {
        if (acc.getUsername() == username) {
            return true;
        }
    }
    return false;
}

Account* AuthManager::getCurrentAccount() {
    if (!isLoggedIn) {
        return nullptr;
    }
    
    return getAccountByUsername(currentUsername);
}

Account* AuthManager::getAccountByUsername(const std::string& username) {
    for (auto& acc : accounts) {
        if (acc.getUsername() == username) {
            return &acc;
        }
    }
    return nullptr;
}

void AuthManager::saveAccounts() {
    FileManager::saveAccounts(accounts);
}
