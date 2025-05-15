#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <vector>
#include "CartItem.h"

class ShoppingCart {
private:
    std::vector<CartItem> items;

public:
    // Add item to cart
    void addItem(const CartItem& item);
    
    // Remove item from cart by product ID
    bool removeItem(int productId);
    
    // Check if a product is in the cart
    bool containsProduct(int productId) const;
    
    // Get cart item by product ID
    CartItem* getCartItemByProductId(int productId);
    
    // Calculate total price of all items in cart
    double getTotalPrice() const;
    
    // Check if cart is empty
    bool isEmpty() const { return items.empty(); }
    
    // Clear all items from cart
    void clear() { items.clear(); }
    
    // Get all items in cart
    const std::vector<CartItem>& getItems() const { return items; }
    
    // Display all items in cart
    void display() const;
};

#endif // SHOPPING_CART_H
