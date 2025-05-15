#include "ProductManager.h"
#include "FileManager.h"
#include <iostream>
#include <algorithm>

ProductManager::ProductManager() {
    products = FileManager::loadProducts();
}

bool ProductManager::addProduct(const Product& product) {
    products.push_back(product);
    FileManager::saveProducts(products);
    
    // Log the action
    FileManager::logProductAudit(product.getCreatedBy(), "added", product);
    
    return true;
}

bool ProductManager::updateProduct(int productId, const std::string& name, double price, 
                                  int quantity, const std::string& modifiedBy) {
    Product* product = getProductById(productId);
    
    if (!product) {
        std::cout << "❌ Product not found.\n";
        return false;
    }
    
    std::string oldName = product->getName();
    double oldPrice = product->getPrice();
    int oldQuantity = product->getQuantity();
    
    // Update product with audit information
    product->update(name, price, quantity, modifiedBy, FileManager::getCurrentDateTime());
    FileManager::saveProducts(products);
    
    // Log the action
    FileManager::logProductAudit(modifiedBy, "updated", *product, oldName, oldPrice, oldQuantity);
    
    std::cout << "✅ Product updated by " << modifiedBy << " on " << product->getModifiedDateTime() << "!\n";
    return true;
}

bool ProductManager::deleteProduct(int productId, const std::string& deletedBy) {
    auto it = std::find_if(products.begin(), products.end(),
                          [productId](const Product& p) { return p.getId() == productId; });
    
    if (it == products.end()) {
        std::cout << "❌ Product not found.\n";
        return false;
    }
    
    // Log the deletion before removing the product
    FileManager::logProductAudit(deletedBy, "deleted", *it);
    
    products.erase(it);
    FileManager::saveProducts(products);
    
    std::cout << "✅ Product deleted by " << deletedBy << " on " << FileManager::getCurrentDateTime() << "!\n";
    return true;
}

Product* ProductManager::getProductById(int productId) {
    auto it = std::find_if(products.begin(), products.end(),
                          [productId](const Product& p) { return p.getId() == productId; });
    
    return (it != products.end()) ? &(*it) : nullptr;
}

void ProductManager::displayAllProducts() const {
    if (products.empty()) {
        std::cout << "No products available.\n";
        return;
    }
    
    std::cout << "\n--- PRODUCT LIST ---\n";
    for (const auto& product : products) {
        product.display();
    }
}

void ProductManager::displayProductDetails(int productId) const {
    auto it = std::find_if(products.begin(), products.end(),
                          [productId](const Product& p) { return p.getId() == productId; });
    
    if (it != products.end()) {
        it->displayDetailed();
    } else {
        std::cout << "❌ Product not found.\n";
    }
}

bool ProductManager::reduceProductQuantity(int productId, int amount, const std::string& username) {
    Product* product = getProductById(productId);
    
    if (!product) {
        std::cout << "❌ Product not found.\n";
        return false;
    }
    
    if (product->getQuantity() < amount) {
        std::cout << "❌ Not enough stock available.\n";
        return false;
    }
    
    product->reduceQuantity(amount);
    FileManager::saveProducts(products);
    
    // Log inventory change
    FileManager::logInventoryChange(username, productId, amount, product->getQuantity());
    
    return true;
}

int ProductManager::generateNewProductId() const {
    int maxId = 0;
    
    for (const auto& product : products) {
        if (product.getId() > maxId) {
            maxId = product.getId();
        }
    }
    
    return maxId + 1;
}

void ProductManager::saveProducts() {
    FileManager::saveProducts(products);
}
