#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ctime>
using namespace std;

struct Account {
    string username;
    string password;
    string role; // "admin" or "user"
    string fullName;
    string email;
    string phone;
    string address;
    string joinDate;
    vector<string> orderHistory;
};

vector<Account> accounts = {
    {"admin", "admin123", "admin", "Admin User", "admin@example.com", "1234567890", "Admin Address", "2023-01-01", {}},
    {"user", "user123", "user", "Regular User", "user@example.com", "0987654321", "User Address", "2023-01-01", {}}
};

string currentUserRole;
string currentUsername;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
    // Audit fields
    string createdBy;
    string createdDateTime;
    string modifiedBy;
    string modifiedDateTime;
};

struct CartItem {
    Product product;
    int quantity;
};

vector<Product> products;
vector<CartItem> cart;

// Function declarations
void productManagement();
void browseAndBuy();
void viewCart();
void removeFromCart();
void checkout();
void viewPurchaseHistory();
void generateReports();
void saveData();
void loadData();
void viewUserProfile();
void viewAllUsers();

string getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

void saveAccounts() {
    ofstream file("accounts.txt");
    if (!file) {
        cout << "Error opening accounts file for writing.\n";
        return;
    }
    for (const auto& acc : accounts) {
        file << acc.username << ","
             << acc.password << ","
             << acc.role << ","
             << acc.fullName << ","
             << acc.email << ","
             << acc.phone << ","
             << acc.address << ","
             << acc.joinDate;
        
        // Save order history
        file << ",";
        for (size_t i = 0; i < acc.orderHistory.size(); i++) {
            file << acc.orderHistory[i];
            if (i < acc.orderHistory.size() - 1) {
                file << "|";
            }
        }
        file << endl;
    }
    file.close();
    cout << "Account data saved successfully.\n";
}

void loadAccounts() {
    ifstream file("accounts.txt");
    if (!file) {
        cout << "No existing accounts file found. Using default accounts.\n";
        return;
    }
    accounts.clear();
    string line;
    while (getline(file, line)) {
        Account acc;
        vector<string> fields;
        string field;
        stringstream ss(line);
        
        // Parse the CSV line
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        
        // Basic fields check
        if (fields.size() < 8) continue;
        
        acc.username = fields[0];
        acc.password = fields[1];
        acc.role = fields[2];
        acc.fullName = fields[3];
        acc.email = fields[4];
        acc.phone = fields[5];
        acc.address = fields[6];
        acc.joinDate = fields[7];
        
        // Parse order history if it exists
        if (fields.size() > 8 && !fields[8].empty()) {
            stringstream historyStream(fields[8]);
            string order;
            while (getline(historyStream, order, '|')) {
                acc.orderHistory.push_back(order);
            }
        }
        
        accounts.push_back(acc);
    }
    file.close();
    cout << "Account data loaded successfully.\n";
}

void registerUser() {
    Account newAccount;
    cout << "===== REGISTER =====\n";
    
    cout << "Choose a username: ";
    cin >> newAccount.username;

    // Check if username already exists
    for (const auto& acc : accounts) {
        if (acc.username == newAccount.username) {
            cout << "❌ Username already exists. Please choose another.\n";
            return;
        }
    }

    cout << "Choose a password: ";
    cin >> newAccount.password;
    
    // Get additional user information
    cin.ignore(); // Clear input buffer
    cout << "Enter your full name: ";
    getline(cin, newAccount.fullName);
    
    cout << "Enter your email: ";
    getline(cin, newAccount.email);
    
    cout << "Enter your phone number: ";
    getline(cin, newAccount.phone);
    
    cout << "Enter your address: ";
    getline(cin, newAccount.address);
    
    // Set default values
    newAccount.role = "user";
    newAccount.joinDate = getCurrentDateTime();
    
    accounts.push_back(newAccount);
    saveAccounts();
    cout << "✅ Registration successful! You can now log in.\n";
}

bool login() {
    string uname, pwd;
    cout << "===== LOGIN =====\n";
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pwd;

    for (const auto& acc : accounts) {
        if (acc.username == uname && acc.password == pwd) {
            currentUserRole = acc.role;
            currentUsername = acc.username;
            cout << "✅ Login successful! Role: " << currentUserRole << endl;
            return true;
        }
    }
    cout << "❌ Invalid username or password.\n";
    return false;
}

int main() {
    loadAccounts();
    bool exitProgram = false;
    
    while (!exitProgram) {
        // Clear states when returning to login screen
        currentUsername = "";
        currentUserRole = "";
        cart.clear(); // Clear the cart when logging out
        
        // Login/Register menu
        int choice;
        cout << "===============================================\n";
        cout << "           E-COMMERCE SYSTEM LOGIN\n";
        cout << "===============================================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit Program\n";
        cout << "-----------------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";
            saveData(); // Save data before exiting
            return 0;
        } else if (choice == 2) {
            registerUser();
            continue; // Go back to login screen after registration
        } else if (choice != 1) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        // Try to log in
        if (!login()) {
            cout << "Login failed. Returning to login screen.\n";
            continue;
        }

        // Successfully logged in, load data
        loadData();
        bool loggedIn = true;

        // Main menu loop - runs while user is logged in
        while (loggedIn) {
            cout << "===============================================\n";
            cout << "           WELCOME TO E-COMMERCE SYSTEM\n";
            cout << "===============================================\n";
            cout << "Current user: " << currentUsername << " (" 
                 << (currentUserRole == "admin" ? "Administrator" : "Customer") << ")\n";
            
            // Different menu options based on role
            if (currentUserRole == "admin") {
                cout << "1. Product Management (CRUD)\n";
                cout << "2. Browse Products\n";
                cout << "3. View All Orders\n";
                cout << "4. Generate Reports\n";
                cout << "5. View All Users\n";
                cout << "6. Save Data to File\n";
                cout << "7. Load Data from File\n";
                cout << "8. Logout\n";
                cout << "9. Exit Program\n";
                cout << "-----------------------------------------------\n";
                cout << "Enter your choice (1-9): ";
            } else {
                // Regular user menu
                cout << "1. Browse & Buy Products\n";
                cout << "2. View Shopping Cart\n";
                cout << "3. Checkout & Generate Invoice\n";
                cout << "4. View Purchase History\n";
                cout << "5. View Profile\n";
                cout << "6. Logout\n";
                cout << "7. Exit Program\n";
                cout << "-----------------------------------------------\n";
                cout << "Enter your choice (1-7): ";
            }
            
            cin >> choice;

            if (currentUserRole == "admin") {
                // Admin menu options
                switch (choice) {
                    case 1: productManagement(); break;
                    case 2: browseAndBuy(); break;  // Admin can still browse products
                    case 3: /* View all orders function */ break;
                    case 4: generateReports(); break;
                    case 5: viewAllUsers(); break;
                    case 6: saveData(); break;
                    case 7: loadData(); break;
                    case 8: {
                        cout << "Logging out...\n"; 
                        loggedIn = false;
                        cout << "You have been logged out successfully.\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        string dummy;
                        getline(cin, dummy); // Wait for user to press Enter
                        break;
                    }
                    case 9: 
                        cout << "Exiting the program. Goodbye!\n"; 
                        exitProgram = true;
                        loggedIn = false;
                        break;
                    default: cout << "Invalid choice. Please try again.\n";
                }
            } else {
                // User menu options
                switch (choice) {
                    case 1: browseAndBuy(); break;
                    case 2: viewCart(); break;
                    case 3: checkout(); break;
                    case 4: viewPurchaseHistory(); break;
                    case 5: viewUserProfile(); break;
                    case 6: {
                        cout << "Logging out...\n"; 
                        loggedIn = false;
                        cout << "You have been logged out successfully.\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        string dummy;
                        getline(cin, dummy); // Wait for user to press Enter
                        break;
                    }
                    case 7: 
                        cout << "Exiting the program. Goodbye!\n"; 
                        exitProgram = true;
                        loggedIn = false;
                        break;
                    default: cout << "Invalid choice. Please try again.\n";
                }
            }
        }
    }

    return 0;
}

// Product Management
void productManagement() {
    int choice;
    do {
        cout << "\n--- PRODUCT MANAGEMENT ---\n";
        cout << "1. Add New Product\n";
        cout << "2. View All Products\n";
        cout << "3. Update Product\n";
        cout << "4. Delete Product\n";
        cout << "5. Product Audit Trail\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Product p;
                cout << "Enter product ID: ";
                cin >> p.id;
                auto existing = find_if(products.begin(), products.end(),
                                      [p](const Product& prod) { return prod.id == p.id; });
                if (existing != products.end()) {
                    cout << "❌ Product ID already exists. Cannot add duplicate.\n";
                    break;
                }
                cout << "Enter product name: ";
                cin.ignore();
                getline(cin, p.name);
                cout << "Enter product price: ";
                cin >> p.price;
                cout << "Enter product quantity in stock: ";
                cin >> p.quantity;
                
                // Add audit information
                p.createdBy = currentUsername;
                p.createdDateTime = getCurrentDateTime();
                p.modifiedBy = currentUsername;
                p.modifiedDateTime = getCurrentDateTime();
                
                products.push_back(p);
                cout << "✅ Product added by " << currentUsername << " on " << getCurrentDateTime() << "!\n";
                saveData();
                
                // Log the action
                ofstream log("product_audit.txt", ios::app);
                log << getCurrentDateTime() << " - " << currentUsername << " created product ID: " 
                    << p.id << ", Name: " << p.name << ", Price: $" << p.price 
                    << ", Quantity: " << p.quantity << endl;
                log.close();
                break;
            }
            case 2: {
                cout << "\n--- PRODUCT LIST ---\n";
                if (products.empty()) {
                    cout << "No products available.\n";
                } else {
                    for (const auto& p : products) {
                        cout << "ID: " << p.id << ", Name: " << p.name 
                             << ", Price: $" << p.price 
                             << ", In Stock: " << p.quantity << endl;
                        cout << "  Created by: " << p.createdBy << " on " << p.createdDateTime << endl;
                        if (p.modifiedBy != p.createdBy || p.modifiedDateTime != p.createdDateTime) {
                            cout << "  Last modified by: " << p.modifiedBy << " on " << p.modifiedDateTime << endl;
                        }
                        cout << "------------------------\n";
                    }
                }
                break;
            }
            case 3: { // UPDATE
                int updateId;
                cout << "Enter Product ID to update: ";
                cin >> updateId;
                auto it = find_if(products.begin(), products.end(),
                                [updateId](const Product& p) { return p.id == updateId; });
                if (it != products.end()) {
                    string oldName = it->name;
                    double oldPrice = it->price;
                    int oldQuantity = it->quantity;
                    
                    cout << "Enter new name (current: " << it->name << "): ";
                    cin.ignore();
                    getline(cin, it->name);
                    cout << "Enter new price (current: $" << it->price << "): ";
                    cin >> it->price;
                    cout << "Enter new quantity (current: " << it->quantity << "): ";
                    cin >> it->quantity;
                    
                    // Update audit information
                    it->modifiedBy = currentUsername;
                    it->modifiedDateTime = getCurrentDateTime();
                    
                    cout << "✅ Product updated by " << currentUsername << " on " << getCurrentDateTime() << "!\n";
                    saveData();
                    
                    // Log the action
                    ofstream log("product_audit.txt", ios::app);
                    log << getCurrentDateTime() << " - " << currentUsername << " updated product ID: " 
                        << updateId << ", Name: " << oldName << " -> " << it->name 
                        << ", Price: $" << oldPrice << " -> $" << it->price 
                        << ", Quantity: " << oldQuantity << " -> " << it->quantity << endl;
                    log.close();
                } else {
                    cout << "❌ Product not found.\n";
                }
                break;
            }
            case 4: { // DELETE
                int deleteId;
                cout << "Enter Product ID to delete: ";
                cin >> deleteId;
                auto it = find_if(products.begin(), products.end(),
                                [deleteId](const Product& p) { return p.id == deleteId; });
                if (it != products.end()) {
                    // Log the deletion before removing the product
                    ofstream log("product_audit.txt", ios::app);
                    log << getCurrentDateTime() << " - " << currentUsername << " deleted product ID: " 
                        << it->id << ", Name: " << it->name << ", Price: $" << it->price 
                        << ", Quantity: " << it->quantity << endl;
                    log.close();
                    
                    products.erase(it);
                    cout << "✅ Product deleted by " << currentUsername << " on " << getCurrentDateTime() << "!\n";
                    saveData();
                } else {
                    cout << "❌ Product not found.\n";
                }
                break;
            }
            case 5: { // VIEW AUDIT TRAIL
                cout << "\n--- PRODUCT AUDIT TRAIL ---\n";
                ifstream log("product_audit.txt");
                if (!log) {
                    cout << "No audit trail found.\n";
                } else {
                    string line;
                    while (getline(log, line)) {
                        cout << line << endl;
                    }
                    log.close();
                }
                break;
            }
            case 6:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

// Browse and Buy
void browseAndBuy() {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    cout << "\n--- BROWSE PRODUCTS ---\n";
    for (const auto& p : products) {
        cout << "ID: " << p.id << ", Name: " << p.name 
             << ", Price: $" << p.price 
             << ", Available: " << p.quantity << endl;
    }

    int productId, quantity;
    cout << "Enter Product ID to add to cart (0 to cancel): ";
    cin >> productId;
    if (productId == 0) return;

    auto it = find_if(products.begin(), products.end(),
                      [productId](const Product& p) { return p.id == productId; });

    if (it != products.end()) {
        if (it->quantity <= 0) {
            cout << "Sorry, this product is out of stock.\n";
            return;
        }
        
        cout << "Enter quantity (available: " << it->quantity << "): ";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "Invalid quantity. Must be greater than 0.\n";
            return;
        }
        
        if (quantity > it->quantity) {
            cout << "Not enough stock available. Maximum available: " << it->quantity << endl;
            return;
        }

        auto cartIt = find_if(cart.begin(), cart.end(),
                              [productId](const CartItem& item) { return item.product.id == productId; });

        if (cartIt != cart.end()) {
            if (cartIt->quantity + quantity > it->quantity) {
                cout << "Cannot add that many. You already have " << cartIt->quantity 
                     << " in your cart. Maximum additional quantity: " 
                     << (it->quantity - cartIt->quantity) << endl;
                return;
            }
            cartIt->quantity += quantity;
        } else {
            cart.push_back({*it, quantity});
        }

        cout << "✅ Product added to cart.\n";
    } else {
        cout << "❌ Product not found.\n";
    }
}

// View Cart
void viewCart() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "\n--- SHOPPING CART ---\n";
    double total = 0;
    for (const auto& item : cart) {
        double itemTotal = item.product.price * item.quantity;
        cout << "ID: " << item.product.id
             << ", Name: " << item.product.name
             << ", Quantity: " << item.quantity
             << ", Total: $" << fixed << setprecision(2) << itemTotal << endl;
        total += itemTotal;
    }
    cout << "Cart Total: $" << fixed << setprecision(2) << total << endl;

    int choice;
    cout << "1. Remove item from cart\n";
    cout << "2. Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1) {
        removeFromCart();
    }
}

// Remove from cart
void removeFromCart() {
    int removeId;
    cout << "Enter Product ID to remove: ";
    cin >> removeId;

    auto it = find_if(cart.begin(), cart.end(),
                      [removeId](const CartItem& item) { return item.product.id == removeId; });

    if (it != cart.end()) {
        cart.erase(it);
        cout << "Item removed from cart.\n";
    } else {
        cout << "Item not found in cart.\n";
    }
}

// Checkout and Invoice
void checkout() {
    if (cart.empty()) {
        cout << "Cart is empty. Nothing to checkout.\n";
        return;
    }

    for (const auto& item : cart) {
        auto productIt = find_if(products.begin(), products.end(),
                               [item](const Product& p) { return p.id == item.product.id; });
        
        if (productIt == products.end()) {
            cout << "Error: " << item.product.name << " is no longer available.\n";
            cout << "Please remove it from your cart before checkout.\n";
            return;
        }
        
        if (productIt->quantity < item.quantity) {
            cout << "Error: Not enough " << item.product.name << " in stock.\n";
            cout << "Available: " << productIt->quantity << ", In cart: " << item.quantity << endl;
            cout << "Please adjust quantity before checkout.\n";
            return;
        }
    }

    double total = 0;
    string orderDetails = "Order date: " + getCurrentDateTime() + " - Items: ";
    
    ofstream invoice("invoice.txt");
    invoice << "--- INVOICE ---\n";
    invoice << "Date: " << getCurrentDateTime() << endl;
    invoice << "Customer: " << currentUsername << endl;

    cout << "\n--- INVOICE ---\n";
    cout << "Customer: " << currentUsername << endl;
    
    for (const auto& item : cart) {
        double itemTotal = item.product.price * item.quantity;
        cout << item.product.name << " x" << item.quantity
             << " = $" << fixed << setprecision(2) << itemTotal << endl;
        invoice << item.product.name << " x" << item.quantity
                << " = $" << fixed << setprecision(2) << itemTotal << endl;
        
        orderDetails += item.product.name + " x" + to_string(item.quantity) + ", ";
        
        total += itemTotal;
        
        auto productIt = find_if(products.begin(), products.end(),
                               [item](const Product& p) { return p.id == item.product.id; });
        if (productIt != products.end()) {
            productIt->quantity -= item.quantity;
            
            ofstream log("inventory_log.txt", ios::app);
            log << getCurrentDateTime() << " - " << currentUsername << " purchased " 
                << item.quantity << " of product ID: " << productIt->id 
                << ", New quantity: " << productIt->quantity << endl;
            log.close();
        }
    }

    cout << "Total Amount: $" << fixed << setprecision(2) << total << endl;
    invoice << "Total Amount: $" << fixed << setprecision(2) << total << endl;

    invoice.close();
    cout << "Invoice saved to invoice.txt.\n";

    ofstream history("history.txt", ios::app);
    history << "--- New Purchase ---\n";
    history << "Date: " << getCurrentDateTime() << endl;
    history << "User: " << currentUsername << endl;
    for (const auto& item : cart) {
        history << item.product.name << " x" << item.quantity << endl;
    }
    history << "Total: $" << fixed << setprecision(2) << total << "\n\n";
    history.close();
    
    orderDetails += "Total: $" + to_string(total);
    
    for (auto& acc : accounts) {
        if (acc.username == currentUsername) {
            acc.orderHistory.push_back(orderDetails);
            break;
        }
    }
    
    saveAccounts();
    saveData();

    cart.clear();
    cout << "✅ Checkout complete. Cart is now empty.\n";
}

// View purchase history
void viewPurchaseHistory() {
    ifstream history("history.txt");
    if (!history) {
        cout << "No purchase history found.\n";
        return;
    }
    cout << "\n--- PURCHASE HISTORY ---\n";
    string line;
    while (getline(history, line)) {
        cout << line << endl;
    }
    history.close();
}

// View user profile
void viewUserProfile() {
    for (const auto& acc : accounts) {
        if (acc.username == currentUsername) {
            cout << "\n--- USER PROFILE ---\n";
            cout << "Username: " << acc.username << endl;
            cout << "Full Name: " << acc.fullName << endl;
            cout << "Email: " << acc.email << endl;
            cout << "Phone: " << acc.phone << endl;
            cout << "Address: " << acc.address << endl;
            cout << "Join Date: " << acc.joinDate << endl;
            cout << "Total Orders: " << acc.orderHistory.size() << endl;
            return;
        }
    }
    
    cout << "User profile not found.\n";
}

// Add an admin function to view all users
void viewAllUsers() {
    if (currentUserRole != "admin") {
        cout << "❌ Access denied. Admin privileges required.\n";
        return;
    }
    
    cout << "\n--- USER LIST ---\n";
    for (const auto& acc : accounts) {
        cout << "Username: " << acc.username << endl;
        cout << "Role: " << acc.role << endl;
        cout << "Full Name: " << acc.fullName << endl;
        cout << "Email: " << acc.email << endl;
        cout << "Phone: " << acc.phone << endl;
        cout << "Join Date: " << acc.joinDate << endl;
        cout << "Total Orders: " << acc.orderHistory.size() << endl;
        cout << "------------------------\n";
    }
}

// Generate reports (exports to CSV files for Excel)
void generateReports() {
    if (currentUserRole != "admin") {
        cout << "❌ Access denied. Admin privileges required.\n";
        return;
    }

    int choice;
    cout << "\n--- GENERATE REPORTS ---\n";
    cout << "1. Sales Report\n";
    cout << "2. Inventory Report\n";
    cout << "3. User Activity Report\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    string timestamp = getCurrentDateTime();
    timestamp.replace(timestamp.find(':'), 1, "-");  // Replace : with - for filename
    timestamp.replace(timestamp.find(':'), 1, "-");  // Replace second : with -

    switch (choice) {
        case 1: {
            // Sales Report
            ofstream salesReport("sales_report_" + timestamp + ".csv");
            if (!salesReport) {
                cout << "Error creating sales report file.\n";
                return;
            }

            // Header
            salesReport << "Date,User,Product,Quantity,Unit Price,Total\n";

            // Read from history.txt to generate sales data
            ifstream history("history.txt");
            if (!history) {
                cout << "No purchase history found. Report will be empty.\n";
                salesReport.close();
                return;
            }

            string line;
            string date = "";
            string user = "";
            double reportTotal = 0;
            int totalItems = 0;

            while (getline(history, line)) {
                if (line.find("--- New Purchase ---") != string::npos) {
                    // Skip the header line
                    continue;
                } else if (line.find("Date: ") != string::npos) {
                    date = line.substr(line.find("Date: ") + 6);
                } else if (line.find("User: ") != string::npos) {
                    user = line.substr(line.find("User: ") + 6);
                } else if (line.find(" x") != string::npos) {
                    // This is a product line
                    size_t xPos = line.find(" x");
                    string productName = line.substr(0, xPos);
                    string quantityStr = line.substr(xPos + 2);
                    int quantity = stoi(quantityStr);
                    
                    // Find product price from products list
                    double price = 0;
                    for (const auto& p : products) {
                        if (p.name == productName) {
                            price = p.price;
                            break;
                        }
                    }
                    
                    double lineTotal = price * quantity;
                    salesReport << date << "," << user << "," << productName << "," 
                              << quantity << "," << price << "," << lineTotal << "\n";
                    
                    reportTotal += lineTotal;
                    totalItems += quantity;
                }
            }
            
            // Summary row
            salesReport << "TOTAL,,,," << totalItems << "," << reportTotal << "\n";
            
            history.close();
            salesReport.close();
            cout << "✅ Sales report generated: sales_report_" << timestamp << ".csv\n";
            break;
        }
        
        case 2: {
            // Inventory Report
            ofstream inventoryReport("inventory_report_" + timestamp + ".csv");
            if (!inventoryReport) {
                cout << "Error creating inventory report file.\n";
                return;
            }

            // Header
            inventoryReport << "ID,Product Name,Price,Quantity in Stock,Value,Created By,Creation Date,Last Modified By,Last Modified Date\n";

            double totalValue = 0;
            int totalItems = 0;
            
            // Write product data
            for (const auto& p : products) {
                double value = p.price * p.quantity;
                inventoryReport << p.id << "," << p.name << "," << p.price << "," 
                           << p.quantity << "," << value << "," 
                           << p.createdBy << "," << p.createdDateTime << "," 
                           << p.modifiedBy << "," << p.modifiedDateTime << "\n";
                
                totalValue += value;
                totalItems += p.quantity;
            }
            
            // Summary row
            inventoryReport << "TOTAL,,," << totalItems << "," << totalValue << ",,,,\n";
            
            inventoryReport.close();
            cout << "✅ Inventory report generated: inventory_report_" << timestamp << ".csv\n";
            break;
        }
        
        case 3: {
            // User Activity Report
            ofstream userReport("user_activity_report_" + timestamp + ".csv");
            if (!userReport) {
                cout << "Error creating user activity report file.\n";
                return;
            }

            // Header
            userReport << "Username,Role,Full Name,Email,Join Date,Order Count,Total Spent\n";

            // Process each user
            for (const auto& acc : accounts) {
                double totalSpent = 0;
                
                // Calculate total spent by parsing order history
                for (const auto& order : acc.orderHistory) {
                    size_t totalPos = order.find("Total: $");
                    if (totalPos != string::npos) {
                        string totalStr = order.substr(totalPos + 8); // Skip "Total: $"
                        try {
                            totalSpent += stod(totalStr);
                        } catch (...) {
                            // Skip if can't parse
                        }
                    }
                }
                
                userReport << acc.username << "," << acc.role << "," << acc.fullName << "," 
                        << acc.email << "," << acc.joinDate << "," 
                        << acc.orderHistory.size() << "," << totalSpent << "\n";
            }
            
            userReport.close();
            cout << "✅ User activity report generated: user_activity_report_" << timestamp << ".csv\n";
            break;
        }
        
        case 4:
            cout << "Returning to main menu...\n";
            break;
            
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}

// Save products to file
void saveData() {
    ofstream file("products.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& p : products) {
        file << p.id << "," << p.name << "," << p.price << "," << p.quantity << ","
             << p.createdBy << "," << p.createdDateTime << ","
             << p.modifiedBy << "," << p.modifiedDateTime << endl;
    }
    file.close();
    cout << "Data saved to products.txt successfully.\n";
}

// Load products from file
void loadData() {
    ifstream file("products.txt");
    if (!file) {
        cout << "No existing product data found (products.txt not present).\n";
        return;
    }
    products.clear();
    string line;
    while (getline(file, line)) {
        Product p;
        vector<string> fields;
        string field;
        stringstream ss(line);
        
        // Parse CSV line
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        
        try {
            // Check if we have all required fields
            if (fields.size() < 8) {
                if (fields.size() >= 3) {
                    p.id = stoi(fields[0]);
                    p.name = fields[1];
                    p.price = stod(fields[2]);
                    p.quantity = (fields.size() >= 4) ? stoi(fields[3]) : 0;
                    p.createdBy = "system";
                    p.createdDateTime = "unknown";
                    p.modifiedBy = "system";
                    p.modifiedDateTime = "unknown";
                } else {
                    cout << "Warning: Skipping invalid record with insufficient fields.\n";
                    continue;
                }
            } else {
                p.id = stoi(fields[0]);
                p.name = fields[1];
                p.price = stod(fields[2]);
                p.quantity = stoi(fields[3]);
                p.createdBy = fields[4];
                p.createdDateTime = fields[5];
                p.modifiedBy = fields[6];
                p.modifiedDateTime = fields[7];
            }
            
            products.push_back(p);
        }
        catch (const std::invalid_argument& e) {
            cout << "Warning: Skipping invalid record with conversion error: " << e.what() << "\n";
            continue;
        }
        catch (const std::out_of_range& e) {
            cout << "Warning: Skipping record with out of range value: " << e.what() << "\n";
            continue;
        }
    }
    file.close();
    cout << "Data loaded from products.txt successfully.\n";
}