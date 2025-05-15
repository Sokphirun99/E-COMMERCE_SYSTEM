#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account {
private:
    std::string username;
    std::string password;
    std::string role; // "admin" or "user"
    std::string fullName;
    std::string email;
    std::string phone;
    std::string address;
    std::string joinDate;
    std::vector<std::string> orderHistory;

public:
    // Constructors
    Account() = default;
    Account(const std::string& username, const std::string& password, 
            const std::string& role, const std::string& fullName,
            const std::string& email, const std::string& phone,
            const std::string& address, const std::string& joinDate);

    // Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getRole() const { return role; }
    std::string getFullName() const { return fullName; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }
    std::string getAddress() const { return address; }
    std::string getJoinDate() const { return joinDate; }
    const std::vector<std::string>& getOrderHistory() const { return orderHistory; }

    // Setters
    void setUsername(const std::string& username) { this->username = username; }
    void setPassword(const std::string& password) { this->password = password; }
    void setRole(const std::string& role) { this->role = role; }
    void setFullName(const std::string& fullName) { this->fullName = fullName; }
    void setEmail(const std::string& email) { this->email = email; }
    void setPhone(const std::string& phone) { this->phone = phone; }
    void setAddress(const std::string& address) { this->address = address; }
    void setJoinDate(const std::string& joinDate) { this->joinDate = joinDate; }
    
    // Add order to history
    void addOrder(const std::string& orderDetails);

    // Display account information
    void displayInfo() const;
};

#endif // ACCOUNT_H
