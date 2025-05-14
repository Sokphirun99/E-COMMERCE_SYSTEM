#include "CheckoutManager.h"
#include "FileManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>

bool CheckoutManager::processCheckout() {
    if (cart.isEmpty()) {
        std::cout << "Cart is empty. Nothing to checkout.\n";
        return false;
    }

    if (!validateCartItems()) {
        return false;
    }

    double total = 0.0;
    const std::vector<CartItem>& items = cart.getItems();
    std::string username = authManager.getCurrentUsername();
    
    // Update product quantities and calculate total
    for (const auto& item : items) {
        int productId = item.getProduct().getId();
        int quantity = item.getQuantity();
        
        if (!productManager.reduceProductQuantity(productId, quantity, username)) {
            std::cout << "Error reducing product quantity. Checkout failed.\n";
            return false;
        }
        
        total += item.getTotalPrice();
    }
    
    // Generate invoice and update history
    generateInvoice(total);
    updatePurchaseHistory(total);
    updateAccountOrderHistory(total);
    
    // Save updated products
    productManager.saveProducts();
    
    // Clear cart after successful checkout
    cart.clear();
    std::cout << "✅ Checkout complete. Cart is now empty.\n";
    
    return true;
}

bool CheckoutManager::validateCartItems() const {
    const std::vector<CartItem>& items = cart.getItems();
    
    for (const auto& item : items) {
        int productId = item.getProduct().getId();
        Product* product = productManager.getProductById(productId);
        
        if (!product) {
            std::cout << "Error: " << item.getProduct().getName() << " is no longer available.\n";
            std::cout << "Please remove it from your cart before checkout.\n";
            return false;
        }
        
        if (product->getQuantity() < item.getQuantity()) {
            std::cout << "Error: Not enough " << item.getProduct().getName() << " in stock.\n";
            std::cout << "Available: " << product->getQuantity() << ", In cart: " << item.getQuantity() << std::endl;
            std::cout << "Please adjust quantity before checkout.\n";
            return false;
        }
    }
    
    return true;
}

void CheckoutManager::generateInvoice(double total) const {
    const std::vector<CartItem>& items = cart.getItems();
    std::string username = authManager.getCurrentUsername();
    
    // Display invoice on screen
    std::cout << "\n--- INVOICE ---\n";
    std::cout << "Customer: " << username << std::endl;
    
    for (const auto& item : items) {
        std::cout << item.getProduct().getName() << " x" << item.getQuantity()
                 << " = $" << std::fixed << std::setprecision(2) << item.getTotalPrice() << std::endl;
    }
    
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) << total << std::endl;
    
    // Save invoice to file
    FileManager::saveInvoice(username, items, total);
}

void CheckoutManager::updatePurchaseHistory(double total) const {
    const std::vector<CartItem>& items = cart.getItems();
    std::string username = authManager.getCurrentUsername();
    
    FileManager::savePurchaseHistory(username, items, total);
}

void CheckoutManager::updateAccountOrderHistory(double total) const {
    const std::vector<CartItem>& items = cart.getItems();
    std::string username = authManager.getCurrentUsername();
    
    // Create order details string
    std::stringstream orderDetails;
    orderDetails << "Order date: " << FileManager::getCurrentDateTime() << " - Items: ";
    
    for (const auto& item : items) {
        orderDetails << item.getProduct().getName() << " x" << item.getQuantity() << ", ";
    }
    
    orderDetails << "Total: $" << std::fixed << std::setprecision(2) << total;
    
    // Add to user's order history
    Account* account = authManager.getCurrentAccount();
    if (account) {
        account->addOrder(orderDetails.str());
        authManager.saveAccounts();
    }
}
