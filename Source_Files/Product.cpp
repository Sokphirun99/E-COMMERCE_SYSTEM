#include "Product.h"
#include <iostream>
#include <iomanip>

Product::Product(int id, const std::string& name, double price, int quantity,
                 const std::string& createdBy, const std::string& createdDateTime)
    : id(id), name(name), price(price), quantity(quantity),
      createdBy(createdBy), createdDateTime(createdDateTime),
      modifiedBy(createdBy), modifiedDateTime(createdDateTime) {}

void Product::update(const std::string& name, double price, int quantity, 
                     const std::string& modifiedBy, const std::string& modifiedDateTime) {
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->modifiedBy = modifiedBy;
    this->modifiedDateTime = modifiedDateTime;
}

bool Product::reduceQuantity(int amount) {
    if (amount <= 0 || amount > quantity) {
        return false;
    }
    
    quantity -= amount;
    return true;
}

void Product::display() const {
    std::cout << "ID: " << id << ", Name: " << name 
              << ", Price: $" << std::fixed << std::setprecision(2) << price 
              << ", In Stock: " << quantity << std::endl;
}

void Product::displayDetailed() const {
    display();
    std::cout << "  Created by: " << createdBy << " on " << createdDateTime << std::endl;
    if (modifiedBy != createdBy || modifiedDateTime != createdDateTime) {
        std::cout << "  Last modified by: " << modifiedBy << " on " << modifiedDateTime << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}
