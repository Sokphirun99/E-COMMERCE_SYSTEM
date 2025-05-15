#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <vector>
#include "Product.h"

class ProductManager {
private:
    std::vector<Product> products;

public:
    // Constructor
    ProductManager();
    
    // Product CRUD operations
    bool addProduct(const Product& product);
    bool updateProduct(int productId, const std::string& name, double price, int quantity, 
                      const std::string& modifiedBy);
    bool deleteProduct(int productId, const std::string& deletedBy);
    
    // Product getters
    std::vector<Product>& getAllProducts() { return products; }
    Product* getProductById(int productId);
    
    // Display operations
    void displayAllProducts() const;
    void displayProductDetails(int productId) const;
    
    // Inventory operations
    bool reduceProductQuantity(int productId, int amount, const std::string& username);
    
    // Generate new unique product ID
    int generateNewProductId() const;
    
    // Save/load operations
    void saveProducts();
};

#endif // PRODUCT_MANAGER_H
