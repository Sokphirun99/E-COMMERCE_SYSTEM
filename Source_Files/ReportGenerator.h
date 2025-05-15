#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include "ProductManager.h"
#include "AuthManager.h"
#include <string>

class ReportGenerator {
private:
    ProductManager& productManager;
    AuthManager& authManager;

public:
    // Constructor
    ReportGenerator(ProductManager& productManager, AuthManager& authManager)
        : productManager(productManager), authManager(authManager) {}
    
    // Report generation methods
    void generateSalesReport() const;
    void generateInventoryReport() const;
    void generateUserActivityReport() const;
    void displayProductAuditTrail() const;
    
private:
    // Helper to get a timestamp for file naming
    std::string generateTimestampString() const;
};

#endif // REPORT_GENERATOR_H
