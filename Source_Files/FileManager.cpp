#include "FileManager.h"
#include "CartItem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

std::string FileManager::getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);
    return std::string(buffer);
}

bool FileManager::saveAccounts(const std::vector<Account>& accounts) {
    std::ofstream file("../Data_Files/accounts.txt");
    if (!file) {
        std::cerr << "Error opening accounts file for writing.\n";
        return false;
    }
    
    for (const auto& acc : accounts) {
        file << acc.getUsername() << ","
             << acc.getPassword() << ","
             << acc.getRole() << ","
             << acc.getFullName() << ","
             << acc.getEmail() << ","
             << acc.getPhone() << ","
             << acc.getAddress() << ","
             << acc.getJoinDate();
        
        // Save order history
        file << ",";
        const auto& history = acc.getOrderHistory();
        for (size_t i = 0; i < history.size(); i++) {
            file << history[i];
            if (i < history.size() - 1) {
                file << "|";
            }
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Account data saved successfully.\n";
    return true;
}

std::vector<Account> FileManager::loadAccounts() {
    std::vector<Account> accounts;
    std::ifstream file("../Data_Files/accounts.txt");
    
    if (!file) {
        std::cout << "No existing accounts file found. Using default accounts.\n";
        
        // Create default accounts
        Account admin("admin", "admin123", "admin", "Admin User", 
                     "admin@example.com", "1234567890", "Admin Address", getCurrentDateTime());
        
        Account user("user", "user123", "user", "Regular User", 
                    "user@example.com", "0987654321", "User Address", getCurrentDateTime());
        
        accounts.push_back(admin);
        accounts.push_back(user);
        
        return accounts;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;
        
        // Parse the CSV line
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }
        
        // Basic fields check
        if (fields.size() < 8) continue;
        
        Account acc;
        acc.setUsername(fields[0]);
        acc.setPassword(fields[1]);
        acc.setRole(fields[2]);
        acc.setFullName(fields[3]);
        acc.setEmail(fields[4]);
        acc.setPhone(fields[5]);
        acc.setAddress(fields[6]);
        acc.setJoinDate(fields[7]);
        
        // Parse order history if it exists
        if (fields.size() > 8 && !fields[8].empty()) {
            std::stringstream historyStream(fields[8]);
            std::string order;
            while (std::getline(historyStream, order, '|')) {
                acc.addOrder(order);
            }
        }
        
        accounts.push_back(acc);
    }
    
    file.close();
    std::cout << "Account data loaded successfully.\n";
    return accounts;
}

bool FileManager::saveProducts(const std::vector<Product>& products) {
    std::ofstream file("../Data_Files/products.txt");
    if (!file) {
        std::cerr << "Error opening file for writing.\n";
        return false;
    }
    
    for (const auto& p : products) {
        file << p.getId() << "," << p.getName() << "," << p.getPrice() << "," << p.getQuantity() << ","
             << p.getCreatedBy() << "," << p.getCreatedDateTime() << ","
             << p.getModifiedBy() << "," << p.getModifiedDateTime() << std::endl;
    }
    
    file.close();
    std::cout << "Product data saved successfully.\n";
    return true;
}

std::vector<Product> FileManager::loadProducts() {
    std::vector<Product> products;
    std::ifstream file("../Data_Files/products.txt");
    
    if (!file) {
        std::cout << "No existing product data found.\n";
        return products;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;
        
        // Parse CSV line
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }
        
        try {
            // Check if we have all required fields
            if (fields.size() < 8) {
                if (fields.size() >= 3) {
                    int id = std::stoi(fields[0]);
                    std::string name = fields[1];
                    double price = std::stod(fields[2]);
                    int quantity = (fields.size() >= 4) ? std::stoi(fields[3]) : 0;
                    
                    Product p(id, name, price, quantity, "system", "unknown");
                    products.push_back(p);
                }
            } else {
                int id = std::stoi(fields[0]);
                std::string name = fields[1];
                double price = std::stod(fields[2]);
                int quantity = std::stoi(fields[3]);
                
                Product p(id, name, price, quantity, fields[4], fields[5]);
                p.setModifiedBy(fields[6]);
                p.setModifiedDateTime(fields[7]);
                
                products.push_back(p);
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Warning: Skipping invalid record with conversion error: " << e.what() << "\n";
            continue;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Warning: Skipping record with out of range value: " << e.what() << "\n";
            continue;
        }
    }
    
    file.close();
    std::cout << "Product data loaded successfully.\n";
    return products;
}

bool FileManager::logProductAudit(const std::string& username, const std::string& action, 
                                 const Product& product, const std::string& oldName, 
                                 double oldPrice, int oldQuantity) {
    std::ofstream log("../Data_Files/product_audit.txt", std::ios::app);
    
    if (!log) {
        std::cerr << "Error opening audit log file.\n";
        return false;
    }
    
    log << getCurrentDateTime() << " - " << username << " " << action << " product ID: " 
        << product.getId();
    
    if (action == "updated") {
        log << ", Name: " << oldName << " -> " << product.getName()
            << ", Price: $" << oldPrice << " -> $" << product.getPrice()
            << ", Quantity: " << oldQuantity << " -> " << product.getQuantity();
    } else if (action == "added" || action == "deleted") {
        log << ", Name: " << product.getName() << ", Price: $" << product.getPrice()
            << ", Quantity: " << product.getQuantity();
    }
    
    log << std::endl;
    log.close();
    return true;
}

bool FileManager::logInventoryChange(const std::string& username, int productId, 
                                     int quantity, int newQuantity) {
    std::ofstream log("../Data_Files/inventory_log.txt", std::ios::app);
    
    if (!log) {
        std::cerr << "Error opening inventory log file.\n";
        return false;
    }
    
    log << getCurrentDateTime() << " - " << username << " purchased " 
        << quantity << " of product ID: " << productId
        << ", New quantity: " << newQuantity << std::endl;
    
    log.close();
    return true;
}

bool FileManager::saveInvoice(const std::string& username, const std::vector<CartItem>& items, double total) {
    std::ofstream invoice("../Data_Files/invoice.txt");
    
    if (!invoice) {
        std::cerr << "Error opening invoice file.\n";
        return false;
    }
    
    invoice << "--- INVOICE ---\n";
    invoice << "Date: " << getCurrentDateTime() << std::endl;
    invoice << "Customer: " << username << std::endl;
    
    for (const auto& item : items) {
        invoice << item.getProduct().getName() << " x" << item.getQuantity()
                << " = $" << std::fixed << std::setprecision(2) << item.getTotalPrice() << std::endl;
    }
    
    invoice << "Total Amount: $" << std::fixed << std::setprecision(2) << total << std::endl;
    invoice.close();
    
    std::cout << "Invoice saved to invoice.txt.\n";
    return true;
}

bool FileManager::savePurchaseHistory(const std::string& username, const std::vector<CartItem>& items, double total) {
    std::ofstream history("../Data_Files/history.txt", std::ios::app);
    
    if (!history) {
        std::cerr << "Error opening history file.\n";
        return false;
    }
    
    history << "--- New Purchase ---\n";
    history << "Date: " << getCurrentDateTime() << std::endl;
    history << "User: " << username << std::endl;
    
    for (const auto& item : items) {
        history << item.getProduct().getName() << " x" << item.getQuantity() << std::endl;
    }
    
    history << "Total: $" << std::fixed << std::setprecision(2) << total << "\n\n";
    history.close();
    
    return true;
}

std::vector<std::string> FileManager::loadPurchaseHistory(const std::string& username) {
    std::vector<std::string> history;
    std::ifstream file("../Data_Files/history.txt");
    
    if (!file) {
        return history; // Return empty vector if file doesn't exist
    }
    
    std::string line;
    bool readingPurchase = false;
    std::string currentUser = "";
    std::string currentPurchase = "";
    
    while (std::getline(file, line)) {
        // Start of a new purchase record
        if (line.find("--- New Purchase ---") != std::string::npos) {
            // If we were already reading a purchase, save it if it matches our user filter
            if (readingPurchase && (username.empty() || currentUser == username)) {
                history.push_back(currentPurchase);
            }
            
            // Start a new purchase record
            readingPurchase = true;
            currentPurchase = line + "\n";
            currentUser = "";
        } 
        // Parse user info
        else if (readingPurchase && line.find("User: ") != std::string::npos) {
            currentUser = line.substr(6); // Extract username after "User: "
            currentPurchase += line + "\n";
        }
        // Add line to current purchase
        else if (readingPurchase) {
            currentPurchase += line + "\n";
        }
    }
    
    // Don't forget to add the last purchase if it's valid
    if (readingPurchase && (username.empty() || currentUser == username)) {
        history.push_back(currentPurchase);
    }
    
    file.close();
    return history;
}
