#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    double price;
    int quantity;
    // Audit fields
    std::string createdBy;
    std::string createdDateTime;
    std::string modifiedBy;
    std::string modifiedDateTime;

public:
    // Constructors
    Product() = default;
    Product(int id, const std::string& name, double price, int quantity,
            const std::string& createdBy, const std::string& createdDateTime);

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    std::string getCreatedBy() const { return createdBy; }
    std::string getCreatedDateTime() const { return createdDateTime; }
    std::string getModifiedBy() const { return modifiedBy; }
    std::string getModifiedDateTime() const { return modifiedDateTime; }

    // Setters
    void setId(int id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setPrice(double price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setModifiedBy(const std::string& modifiedBy) { this->modifiedBy = modifiedBy; }
    void setModifiedDateTime(const std::string& modifiedDateTime) { this->modifiedDateTime = modifiedDateTime; }
    
    // Update product details and modification information
    void update(const std::string& name, double price, int quantity, 
                const std::string& modifiedBy, const std::string& modifiedDateTime);

    // Reduce quantity (for purchases)
    bool reduceQuantity(int amount);

    // Display product information
    void display() const;
    
    // Display detailed product information including audit trail
    void displayDetailed() const;
};

#endif // PRODUCT_H
