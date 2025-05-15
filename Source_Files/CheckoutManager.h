#ifndef CHECKOUT_MANAGER_H
#define CHECKOUT_MANAGER_H

#include "ShoppingCart.h"
#include "ProductManager.h"
#include "AuthManager.h"

class CheckoutManager {
private:
    ShoppingCart& cart;
    ProductManager& productManager;
    AuthManager& authManager;

public:
    // Constructor
    CheckoutManager(ShoppingCart& cart, ProductManager& productManager, AuthManager& authManager)
        : cart(cart), productManager(productManager), authManager(authManager) {}
    
    // Process checkout
    bool processCheckout();
    
    // Validate cart items are available in sufficient quantities
    bool validateCartItems() const;
    
    // Generate invoice and save purchase history
    void generateInvoice(double total) const;
    void updatePurchaseHistory(double total) const;
    void updateAccountOrderHistory(double total) const;
};

#endif // CHECKOUT_MANAGER_H
