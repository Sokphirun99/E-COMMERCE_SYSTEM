#include "CartItem.h"
#include <iostream>
#include <iomanip>

CartItem::CartItem(const Product& product, int quantity) 
    : product(product), quantity(quantity) {}

void CartItem::display() const {
    std::cout << product.getName() << " (ID: " << product.getId() << ")" 
              << " x" << quantity << " = $" << std::fixed << std::setprecision(2) 
              << getTotalPrice() << std::endl;
}
