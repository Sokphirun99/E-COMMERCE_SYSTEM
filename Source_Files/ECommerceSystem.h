#ifndef ECOMMERCE_SYSTEM_H
#define ECOMMERCE_SYSTEM_H

#include "AuthManager.h"
#include "ProductManager.h"
#include "ShoppingCart.h"
#include "CheckoutManager.h"
#include "ReportGenerator.h"

class ECommerceSystem {
private:
    AuthManager authManager;
    ProductManager productManager;
    ShoppingCart cart;
    CheckoutManager checkoutManager;
    ReportGenerator reportGenerator;

public:
    // Constructor
    ECommerceSystem();
    
    // Main system methods
    void run();
    
private:
    // Menu methods
    void showLoginMenu();
    void showMainMenu();
    void showAdminMenu();
    void showUserMenu();
    
    // Admin functions
    void handleProductManagement();
    void handleViewAllUsers();
    void handleReports();
    
    // User functions
    void handleBrowseAndBuy();
    void handleViewCart();
    void handleCheckout();
    void handleViewPurchaseHistory();
    void handleViewUserProfile();
    
    // Common functions
    void handleLogout();
    void handleSaveData();
    void handleLoadData();
};

#endif // ECOMMERCE_SYSTEM_H
