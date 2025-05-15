#include "ECommerceSystem.h"
#include "FileManager.h"
#include <iostream>
#include <limits>

ECommerceSystem::ECommerceSystem()
    : checkoutManager(cart, productManager, authManager),
      reportGenerator(productManager, authManager) {}

void ECommerceSystem::run() {
    bool exitProgram = false;
    
    while (!exitProgram) {
        // Clear states when returning to login screen
        authManager.logout();
        cart.clear();
        
        showLoginMenu();
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: // Login
                {
                    std::string username, password;
                    std::cout << "===== LOGIN =====\n";
                    std::cout << "Username: ";
                    std::cin >> username;
                    std::cout << "Password: ";
                    std::cin >> password;
                    
                    if (authManager.login(username, password)) {
                        showMainMenu();
                    } else {
                        std::cout << "Login failed. Returning to login screen.\n";
                    }
                }
                break;
                
            case 2: // Register
                {
                    std::cout << "===== REGISTER =====\n";
                    
                    std::string username, password, fullName, email, phone, address;
                    
                    std::cout << "Choose a username: ";
                    std::cin >> username;
                    
                    if (authManager.isUsernameTaken(username)) {
                        std::cout << "❌ Username already exists. Please choose another.\n";
                        break;
                    }
                    
                    std::cout << "Choose a password: ";
                    std::cin >> password;
                    
                    // Get additional user information
                    std::cin.ignore(); // Clear input buffer
                    std::cout << "Enter your full name: ";
                    std::getline(std::cin, fullName);
                    
                    std::cout << "Enter your email: ";
                    std::getline(std::cin, email);
                    
                    std::cout << "Enter your phone number: ";
                    std::getline(std::cin, phone);
                    
                    std::cout << "Enter your address: ";
                    std::getline(std::cin, address);
                    
                    Account newAccount(username, password, "user", fullName, email, phone, address, FileManager::getCurrentDateTime());
                    authManager.registerUser(newAccount);
                }
                break;
                
            case 3: // Exit
                std::cout << "Exiting program. Goodbye!\n";
                // Save data before exiting
                handleSaveData();
                exitProgram = true;
                break;
                
            default:
                std::cout << "Invalid choice. Please try again.\n";
                // Clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}

void ECommerceSystem::showLoginMenu() {
    std::cout << "===============================================\n";
    std::cout << "           E-COMMERCE SYSTEM LOGIN\n";
    std::cout << "===============================================\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit Program\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "Enter choice: ";
}

void ECommerceSystem::showMainMenu() {
    bool loggedIn = true;
    
    while (loggedIn) {
        std::cout << "===============================================\n";
        std::cout << "           WELCOME TO E-COMMERCE SYSTEM\n";
        std::cout << "===============================================\n";
        std::cout << "Current user: " << authManager.getCurrentUsername() << " (" 
                  << (authManager.userIsAdmin() ? "Administrator" : "Customer") << ")\n";
        
        int choice;
        
        if (authManager.userIsAdmin()) {
            showAdminMenu();
        } else {
            showUserMenu();
        }
        
        std::cin >> choice;
        
        if (authManager.userIsAdmin()) {
            switch (choice) {
                case 1: handleProductManagement(); break;
                case 2: handleBrowseAndBuy(); break;
                case 3: handleViewPurchaseHistory(); break; // View all orders
                case 4: handleReports(); break;
                case 5: handleViewAllUsers(); break;
                case 6: handleSaveData(); break;
                case 7: handleLoadData(); break;
                case 8: loggedIn = false; break; // Logout
                case 9: 
                    std::cout << "Exiting program. Goodbye!\n";
                    handleSaveData();
                    exit(0); 
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    // Clear input buffer
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        } else {
            switch (choice) {
                case 1: handleBrowseAndBuy(); break;
                case 2: handleViewCart(); break;
                case 3: handleCheckout(); break;
                case 4: handleViewPurchaseHistory(); break;
                case 5: handleViewUserProfile(); break;
                case 6: loggedIn = false; break; // Logout
                case 7: 
                    std::cout << "Exiting program. Goodbye!\n";
                    handleSaveData();
                    exit(0); 
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    // Clear input buffer
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }
}

void ECommerceSystem::showAdminMenu() {
    std::cout << "1. Product Management (CRUD)\n";
    std::cout << "2. Browse Products\n";
    std::cout << "3. View All Orders\n";
    std::cout << "4. Generate Reports\n";
    std::cout << "5. View All Users\n";
    std::cout << "6. Save Data to File\n";
    std::cout << "7. Load Data from File\n";
    std::cout << "8. Logout\n";
    std::cout << "9. Exit Program\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "Enter your choice (1-9): ";
}

void ECommerceSystem::showUserMenu() {
    std::cout << "1. Browse & Buy Products\n";
    std::cout << "2. View Shopping Cart\n";
    std::cout << "3. Checkout & Generate Invoice\n";
    std::cout << "4. View Purchase History\n";
    std::cout << "5. View Profile\n";
    std::cout << "6. Logout\n";
    std::cout << "7. Exit Program\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "Enter your choice (1-7): ";
}

void ECommerceSystem::handleProductManagement() {
    int choice;
    do {
        std::cout << "\n=== PRODUCT MANAGEMENT ===\n";
        std::cout << "1. Add New Product\n";
        std::cout << "2. View All Products\n";
        std::cout << "3. Update Product\n";
        std::cout << "4. Delete Product\n";
        std::cout << "5. View Audit Trail\n";
        std::cout << "6. Return to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::string name;
                double price;
                int quantity;
                
                std::cout << "Enter product name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                
                std::cout << "Enter price: $";
                std::cin >> price;
                
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                
                int newId = productManager.generateNewProductId();
                std::string creator = authManager.getCurrentUsername();
                std::string timestamp = FileManager::getCurrentDateTime();
                
                Product newProduct(newId, name, price, quantity, creator, timestamp);
                productManager.addProduct(newProduct);
                
                std::cout << "✅ Product added by " << creator << " on " << timestamp << "!\n";
                break;
            }
            case 2: {
                productManager.displayAllProducts();
                break;
            }
            case 3: {
                int updateId;
                std::cout << "Enter Product ID to update: ";
                std::cin >> updateId;
                
                Product* product = productManager.getProductById(updateId);
                if (!product) {
                    std::cout << "❌ Product not found.\n";
                    break;
                }
                
                std::string name;
                double price;
                int quantity;
                
                std::cout << "Enter new name (current: " << product->getName() << "): ";
                std::cin.ignore();
                std::getline(std::cin, name);
                
                std::cout << "Enter new price (current: $" << product->getPrice() << "): ";
                std::cin >> price;
                
                std::cout << "Enter new quantity (current: " << product->getQuantity() << "): ";
                std::cin >> quantity;
                
                productManager.updateProduct(updateId, name, price, quantity, authManager.getCurrentUsername());
                break;
            }
            case 4: {
                int deleteId;
                std::cout << "Enter Product ID to delete: ";
                std::cin >> deleteId;
                
                productManager.deleteProduct(deleteId, authManager.getCurrentUsername());
                break;
            }
            case 5: {
                reportGenerator.displayProductAuditTrail();
                break;
            }
            case 6:
                std::cout << "Returning to main menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                // Clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    } while (choice != 6);
}

void ECommerceSystem::handleViewAllUsers() {
    std::cout << "\n=== USER LIST ===\n";
    const auto& users = authManager.getAllAccounts();
    
    if (users.empty()) {
        std::cout << "No users found.\n";
        return;
    }
    
    for (const auto& user : users) {
        std::cout << "Username: " << user.getUsername() << "\n";
        std::cout << "Role: " << user.getRole() << "\n";
        std::cout << "Full Name: " << user.getFullName() << "\n";
        std::cout << "Email: " << user.getEmail() << "\n";
        std::cout << "Join Date: " << user.getJoinDate() << "\n";
        std::cout << "Order Count: " << user.getOrderHistory().size() << "\n";
        std::cout << "------------------------\n";
    }
}

void ECommerceSystem::handleReports() {
    int choice;
    
    do {
        std::cout << "\n=== GENERATE REPORTS ===\n";
        std::cout << "1. Sales Report\n";
        std::cout << "2. Inventory Report\n";
        std::cout << "3. User Activity Report\n";
        std::cout << "4. Return to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                reportGenerator.generateSalesReport();
                break;
            case 2:
                reportGenerator.generateInventoryReport();
                break;
            case 3:
                reportGenerator.generateUserActivityReport();
                break;
            case 4:
                std::cout << "Returning to main menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
}

void ECommerceSystem::handleBrowseAndBuy() {
    productManager.displayAllProducts();
    
    if (productManager.getAllProducts().empty()) {
        return;
    }
    
    int choice;
    std::cout << "\nDo you want to add a product to your cart?\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    
    if (choice != 1) {
        return;
    }
    
    int productId, quantity;
    std::cout << "Enter product ID to add to cart: ";
    std::cin >> productId;
    
    Product* product = productManager.getProductById(productId);
    if (!product) {
        std::cout << "❌ Product not found.\n";
        return;
    }
    
    std::cout << "Enter quantity to add: ";
    std::cin >> quantity;
    
    if (quantity <= 0) {
        std::cout << "❌ Quantity must be greater than zero.\n";
        return;
    }
    
    if (product->getQuantity() < quantity) {
        std::cout << "❌ Not enough stock. Available: " << product->getQuantity() << std::endl;
        return;
    }
    
    CartItem item(*product, quantity);
    cart.addItem(item);
    std::cout << "✅ Product added to cart.\n";
}

void ECommerceSystem::handleViewCart() {
    cart.display();
    
    if (cart.isEmpty()) {
        return;
    }
    
    int choice;
    std::cout << "\nDo you want to remove an item from your cart?\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    
    if (choice != 1) {
        return;
    }
    
    int productId;
    std::cout << "Enter product ID to remove from cart: ";
    std::cin >> productId;
    
    if (cart.removeItem(productId)) {
        std::cout << "Item removed from cart.\n";
    } else {
        std::cout << "Item not found in cart.\n";
    }
}

void ECommerceSystem::handleCheckout() {
    checkoutManager.processCheckout();
}

void ECommerceSystem::handleViewPurchaseHistory() {
    std::string username = authManager.getCurrentUsername();
    bool isAdmin = authManager.userIsAdmin();
    
    if (isAdmin) {
        std::cout << "\nView orders for:\n";
        std::cout << "1. All users\n";
        std::cout << "2. Specific user\n";
        std::cout << "Enter choice: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 2) {
            std::cout << "Enter username: ";
            std::cin >> username;
        } else if (choice != 1) {
            std::cout << "Invalid choice. Returning to main menu.\n";
            return;
        } else {
            username = ""; // Empty string to get all users' history
        }
    }
    
    std::vector<std::string> history = FileManager::loadPurchaseHistory(username);
    
    if (history.empty()) {
        std::cout << "No purchase history found.\n";
    } else {
        std::cout << "\n===== PURCHASE HISTORY =====\n";
        for (const auto& entry : history) {
            std::cout << entry << std::endl;
            std::cout << "-------------------------\n";
        }
    }
}

void ECommerceSystem::handleViewUserProfile() {
    Account* account = authManager.getCurrentAccount();
    
    if (account) {
        account->displayInfo();
    } else {
        std::cout << "Error: Could not retrieve user profile.\n";
    }
}

void ECommerceSystem::handleLogout() {
    authManager.logout();
    cart.clear();
    std::cout << "Logged out successfully.\n";
}

void ECommerceSystem::handleSaveData() {
    productManager.saveProducts();
    authManager.saveAccounts();
}

void ECommerceSystem::handleLoadData() {
    // The managers already load data in their constructors
    std::cout << "Data reloaded successfully.\n";
}
