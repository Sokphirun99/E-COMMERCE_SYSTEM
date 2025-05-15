#include "ShoppingCart.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void ShoppingCart::addItem(const CartItem& item) {
    // Check if the product already exists in the cart
    int productId = item.getProduct().getId();
    CartItem* existingItem = getCartItemByProductId(productId);
    
    if (existingItem) {
        // Update quantity if product already in cart
        existingItem->setQuantity(existingItem->getQuantity() + item.getQuantity());
    } else {
        // Add new item to cart
        items.push_back(item);
    }
}

bool ShoppingCart::removeItem(int productId) {
    auto it = std::find_if(items.begin(), items.end(),
                          [productId](const CartItem& item) {
                              return item.getProduct().getId() == productId;
                          });
    
    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    
    return false;
}

bool ShoppingCart::containsProduct(int productId) const {
    auto it = std::find_if(items.begin(), items.end(),
                          [productId](const CartItem& item) {
                              return item.getProduct().getId() == productId;
                          });
    
    return it != items.end();
}

CartItem* ShoppingCart::getCartItemByProductId(int productId) {
    auto it = std::find_if(items.begin(), items.end(),
                          [productId](CartItem& item) {
                              return item.getProduct().getId() == productId;
                          });
    
    return (it != items.end()) ? &(*it) : nullptr;
}

double ShoppingCart::getTotalPrice() const {
    double total = 0.0;
    
    for (const auto& item : items) {
        total += item.getTotalPrice();
    }
    
    return total;
}

void ShoppingCart::display() const {
    if (items.empty()) {
        std::cout << "Your shopping cart is empty." << std::endl;
        return;
    }
    
    std::cout << "\n===== YOUR SHOPPING CART =====\n";
    for (const auto& item : items) {
        item.display();
    }
    
    std::cout << "-----------------------\n";
    std::cout << "Total: $" << std::fixed << std::setprecision(2) << getTotalPrice() << std::endl;
}
