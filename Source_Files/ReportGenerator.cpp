#include "ReportGenerator.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>

std::string ReportGenerator::generateTimestampString() const {
    std::time_t now = std::time(nullptr);
    char buffer[20];
    std::strftime(buffer, 20, "%Y%m%d_%H%M%S", std::localtime(&now));
    return std::string(buffer);
}

void ReportGenerator::generateSalesReport() const {
    std::string timestamp = generateTimestampString();
    std::ofstream report("../Data_Files/sales_report_" + timestamp + ".csv");

    if (!report) {
        std::cerr << "Error creating sales report file.\n";
        return;
    }

    report << "Date,ProductID,ProductName,QuantitySold,UnitPrice,TotalAmount,Customer\n";

    // Parse purchase history to extract sales data
    std::vector<std::string> history = FileManager::loadPurchaseHistory();
    
    std::string currentDate = "";
    std::string currentUser = "";
    bool parsingItems = false;
    
    for (const std::string& entry : history) {
        std::istringstream iss(entry);
        std::string line;
        
        while (std::getline(iss, line)) {
            if (line.find("Date:") != std::string::npos) {
                currentDate = line.substr(6); // Extract date after "Date: "
            } 
            else if (line.find("User:") != std::string::npos) {
                currentUser = line.substr(6); // Extract username after "User: "
                parsingItems = true;
            }
            else if (line.find("Total:") != std::string::npos) {
                parsingItems = false;
            }
            else if (parsingItems && !line.empty() && line.find("--- New Purchase ---") == std::string::npos) {
                // Parse item line format: "ProductName xQuantity"
                size_t xPos = line.find(" x");
                
                if (xPos != std::string::npos) {
                    std::string productName = line.substr(0, xPos);
                    int quantity = std::stoi(line.substr(xPos + 2));
                    
                    // Find product price from current product list
                    double unitPrice = 0.0;
                    int productId = 0;
                    
                    for (const auto& product : productManager.getAllProducts()) {
                        if (product.getName() == productName) {
                            unitPrice = product.getPrice();
                            productId = product.getId();
                            break;
                        }
                    }
                    
                    double totalAmount = unitPrice * quantity;
                    
                    report << currentDate << ","
                           << productId << ","
                           << productName << ","
                           << quantity << ","
                           << std::fixed << std::setprecision(2) << unitPrice << ","
                           << std::fixed << std::setprecision(2) << totalAmount << ","
                           << currentUser << "\n";
                }
            }
        }
    }
    
    report.close();
    std::cout << "✅ Sales report generated: sales_report_" << timestamp << ".csv\n";
}

void ReportGenerator::generateInventoryReport() const {
    std::string timestamp = generateTimestampString();
    std::ofstream report("../Data_Files/inventory_report_" + timestamp + ".csv");
    
    if (!report) {
        std::cerr << "Error creating inventory report file.\n";
        return;
    }
    
    report << "ProductID,Name,Price,QuantityInStock,Value,CreatedBy,CreatedDateTime,ModifiedBy,ModifiedDateTime\n";
    
    double totalValue = 0.0;
    for (const auto& product : productManager.getAllProducts()) {
        double value = product.getPrice() * product.getQuantity();
        totalValue += value;
        
        report << product.getId() << ","
               << product.getName() << ","
               << std::fixed << std::setprecision(2) << product.getPrice() << ","
               << product.getQuantity() << ","
               << std::fixed << std::setprecision(2) << value << ","
               << product.getCreatedBy() << ","
               << product.getCreatedDateTime() << ","
               << product.getModifiedBy() << ","
               << product.getModifiedDateTime() << "\n";
    }
    
    report << ",,,,TOTAL VALUE," << std::fixed << std::setprecision(2) << totalValue << ",,,\n";
    
    report.close();
    std::cout << "✅ Inventory report generated: inventory_report_" << timestamp << ".csv\n";
}

void ReportGenerator::generateUserActivityReport() const {
    std::string timestamp = generateTimestampString();
    std::ofstream report("../Data_Files/user_activity_report_" + timestamp + ".csv");
    
    if (!report) {
        std::cerr << "Error creating user activity report file.\n";
        return;
    }
    
    report << "Username,Role,FullName,Email,JoinDate,OrderCount,TotalSpent\n";
    
    for (const auto& account : authManager.getAllAccounts()) {
        double totalSpent = 0.0;
        
        // Calculate total spent from order history
        for (const auto& orderEntry : account.getOrderHistory()) {
            size_t pos = orderEntry.find("Total: $");
            if (pos != std::string::npos) {
                std::string totalStr = orderEntry.substr(pos + 8); // Skip "Total: $"
                try {
                    totalSpent += std::stod(totalStr);
                } catch (...) {
                    // Skip if we can't parse the amount
                }
            }
        }
        
        report << account.getUsername() << ","
               << account.getRole() << ","
               << account.getFullName() << ","
               << account.getEmail() << ","
               << account.getJoinDate() << ","
               << account.getOrderHistory().size() << ","
               << std::fixed << std::setprecision(2) << totalSpent << "\n";
    }
    
    report.close();
    std::cout << "✅ User activity report generated: user_activity_report_" << timestamp << ".csv\n";
}

void ReportGenerator::displayProductAuditTrail() const {
    std::cout << "\n--- PRODUCT AUDIT TRAIL ---\n";
    std::ifstream log("product_audit.txt");
    if (!log) {
        std::cout << "No audit trail found.\n";
    } else {
        std::string line;
        while (std::getline(log, line)) {
            std::cout << line << std::endl;
        }
        log.close();
    }
}
