#ifndef CART_ITEM_H
#define CART_ITEM_H

#include "Product.h"

class CartItem {
private:
    Product product;
    int quantity;

public:
    // Constructors
    CartItem() = default;
    CartItem(const Product& product, int quantity);

    // Getters
    const Product& getProduct() const { return product; }
    int getQuantity() const { return quantity; }

    // Setters
    void setQuantity(int quantity) { this->quantity = quantity; }

    // Calculate total price for this item
    double getTotalPrice() const { return product.getPrice() * quantity; }

    // Display cart item information
    void display() const;
};

#endif // CART_ITEM_H
