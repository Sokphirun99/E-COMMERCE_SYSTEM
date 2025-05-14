#include "Account.h"
#include <iostream>

Account::Account(const std::string& username, const std::string& password, 
                 const std::string& role, const std::string& fullName,
                 const std::string& email, const std::string& phone,
                 const std::string& address, const std::string& joinDate)
    : username(username), password(password), role(role), fullName(fullName),
      email(email), phone(phone), address(address), joinDate(joinDate) {}

void Account::addOrder(const std::string& orderDetails) {
    orderHistory.push_back(orderDetails);
}

void Account::displayInfo() const {
    std::cout << "===== USER PROFILE =====\n";
    std::cout << "Username: " << username << std::endl;
    std::cout << "Role: " << (role == "admin" ? "Administrator" : "Customer") << std::endl;
    std::cout << "Full Name: " << fullName << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Join Date: " << joinDate << std::endl;
    std::cout << "Total Orders: " << orderHistory.size() << std::endl;
}
