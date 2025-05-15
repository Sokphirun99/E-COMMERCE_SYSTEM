#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include "Account.h"
#include "Product.h"
#include "CartItem.h"

class FileManager {
public:
    // Account file operations
    static bool saveAccounts(const std::vector<Account>& accounts);
    static std::vector<Account> loadAccounts();
    
    // Product file operations
    static bool saveProducts(const std::vector<Product>& products);
    static std::vector<Product> loadProducts();
    
    // Log operations
    static bool logProductAudit(const std::string& username, const std::string& action, const Product& product,
                               const std::string& oldName = "", double oldPrice = -1, int oldQuantity = -1);
    static bool logInventoryChange(const std::string& username, int productId, int quantity, int newQuantity);
    
    // Invoice and history operations
    static bool saveInvoice(const std::string& username, const std::vector<CartItem>& items, double total);
    static bool savePurchaseHistory(const std::string& username, const std::vector<CartItem>& items, double total);
    static std::vector<std::string> loadPurchaseHistory(const std::string& username = "");
    
    // Helper to get current date and time
    static std::string getCurrentDateTime();
};

#endif // FILE_MANAGER_H
