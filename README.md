# E-Commerce System

A comprehensive console-based e-commerce application with dual interfaces for administrators and customers. This system implements product management, shopping cart functionality, user authentication, and purchase tracking.

## Table of Contents
- How to Compile and Run
- System Features
- User Guide
  - Customer Interface
  - Administrator Interface
- Technical Implementation
  - Data Structures
  - File Management
  - Core Functions
- System Flowchart
- Advanced Technical Implementation
- Challenges & Experiences
- References & Screenshots

## How to Compile and Run

### Prerequisites
- C++ compiler (g++ or equivalent)
- Basic command line knowledge

### Compilation Steps
```bash
# Copy main file to standard lowercase extension (macOS case-sensitivity workaround)
cp main.Cpp temp_main.cpp

# Compile the program
g++ -std=c++11 -o ecommerce temp_main.cpp

# Check if compilation was successful
ls -la ecommerce

# Run the program
./ecommerce
```

## System Features

### Authentication
- Multi-user system with role-based access
- User registration with profile information
- Secure login with different permissions for admins and regular users

### Product Management
- Complete CRUD operations (admin only)
- Detailed audit trail tracking product changes
- Product browsing for all users
- Inventory quantity tracking

### Shopping Experience
- Add products to shopping cart
- Manage cart items and quantities
- Checkout process with invoice generation
- Persistent purchase history
- Stock validation during checkout

### User Management
- Profile viewing and management
- Order history tracking
- Admin access to all user accounts
- Real-time join dates for new users

## User Guide

### Login Information
The system comes with two pre-configured accounts:
- **Administrator**: Username: `admin`, Password: `admin123`
- **Customer**: Username: `user`, Password: `user123`

### Customer Interface

When logged in as a regular user, you'll have access to these options:

1. **Browse & Buy Products**
   - View all available products with ID, name, and price
   - See current stock quantity for each product
   - Add products to your cart with specified quantities
   - Products remain in cart until checkout or logout

2. **View Shopping Cart**
   - See all items in cart with quantities and subtotals
   - View cart total amount
   - Option to remove items from cart

3. **Checkout & Generate Invoice**
   - Complete your purchase
   - Generate invoice (saved to `invoice.txt`)
   - Record purchase in history
   - Clear cart after successful checkout
   - Automatically update product inventory

4. **View Purchase History**
   - See all past purchases
   - Details include date, items, quantities, and totals

5. **View Profile**
   - View your account information
   - See your join date and order statistics

6. **Logout**
   - Return to login screen
   - Cart contents are cleared on logout

7. **Exit Program**
   - Close the application entirely

### Administrator Interface

When logged in as an administrator, you'll have access to additional management features:

1. **Product Management (CRUD)**
   - **Add New Products**: Create products with unique IDs, names, prices, and quantities
   - **View All Products**: See complete catalog with audit details
   - **Update Products**: Modify names, prices, and stock quantities of existing products
   - **Delete Products**: Remove products from the system
   - **View Audit Trail**: See who created, modified, or deleted products with timestamps

2. **Browse Products**
   - View the customer-facing product catalog
   - Test the browsing experience

3. **View All Orders**
   - Access the complete purchase history
   - See orders across all users

4. **Generate Reports**
   - Sales Report: Export detailed sales data to CSV
   - Inventory Report: Generate product stock and valuation in CSV
   - User Activity Report: Analyze user engagement in CSV format
   - All reports include timestamps and can be opened in Excel

5. **View All Users**
   - See complete user list
   - Access user details including order counts

6. **Save Data to File**
   - Manually trigger data persistence

7. **Load Data from File**
   - Manually reload data from files

8. **Logout**
   - Return to login screen

9. **Exit Program**
   - Close the application entirely

## Technical Implementation

### Data Structures

The system uses three main data structures designed to efficiently store and manage different aspects of the e-commerce system:

1. **Account Structure**
```cpp
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
```

2. **Product Structure**
```cpp
struct Product {
    int id;
    string name;
    double price;
    int quantity;  // Stock quantity
    // Audit fields
    string createdBy;
    string createdDateTime;
    string modifiedBy;
    string modifiedDateTime;
};
```

3. **CartItem Structure**
```cpp
struct CartItem {
    Product product;
    int quantity;
};
```

#### Data Types Used and Rationale:

1. **std::string**
   - Used for storing text data like names, usernames, passwords, and dates
   - Chosen for its dynamic sizing and built-in string manipulation capabilities
   - More convenient than character arrays for variable-length text

2. **int**
   - Used for product IDs and cart quantities
   - Provides sufficient range for identifiers and counts
   - Efficient for numerical operations and comparisons

3. **double**
   - Used for product prices
   - Allows decimal points for precise monetary values
   - Chosen over float for higher precision in financial calculations

4. **std::vector<T>**
   - Used for dynamic collections (products, cart items, accounts, order history)
   - Provides automatic memory management and dynamic resizing
   - Offers efficient random access and iteration
   - Simplifies collection management compared to raw arrays

5. **struct**
   - Used to create custom composite data types
   - Groups related data fields together for better organization
   - Provides logical encapsulation of entity attributes
   - Makes code more readable and maintainable by treating related data as a unit

### File Management

The system uses five distinct files for data persistence, each with a specific structure and purpose:

#### 1. accounts.txt
**Purpose**: Stores user credentials and profile information.
**Format**: Comma-separated values (CSV) file.
**Structure**:
```
username,password,role,fullName,email,phone,address,joinDate,orderHistory
```
**Example**:
```
admin,admin123,admin,Admin User,admin@example.com,1234567890,Admin Address,2025-05-10 12:34:56,
user,user123,user,Regular User,user@example.com,0987654321,User Address,2025-05-10 12:35:22,Order date: 2025-05-10 - Items: Laptop x1, Total: $999.00|Order date: 2025-05-15 - Items: Headphones x1, Total: $89.99
```
**Note**: Order history is stored as pipe-separated (|) entries within the last field.

#### 2. products.txt
**Purpose**: Stores the product catalog with full audit information.
**Format**: Comma-separated values (CSV) file.
**Structure**:
```
id,name,price,quantity,createdBy,createdDateTime,modifiedBy,modifiedDateTime
```
**Example**:
```
1,Laptop,999.99,10,admin,2025-05-10 12:36:45,admin,2025-05-10 14:15:22
2,Headphones,89.99,25,user,2025-05-10 12:37:10,admin,2025-05-10 12:37:10
3,Keyboard,49.99,15,admin,2025-05-10 12:38:20,admin,2025-05-10 12:38:20
```

#### 3. invoice.txt
**Purpose**: Contains the most recent invoice generated during checkout.
**Format**: Human-readable text file.
**Structure**:
```
--- INVOICE ---
Date: [date]
Customer: [username]
[product name] x[quantity] = $[subtotal]
[product name] x[quantity] = $[subtotal]
...
Total Amount: $[total]
```
**Example**:
```
--- INVOICE ---
Date: 2025-05-15 15:44:22
Customer: user
Laptop x1 = $999.99
Headphones x2 = $179.98
Total Amount: $1179.97
```

#### 4. history.txt
**Purpose**: Maintains a record of all purchases across all users.
**Format**: Human-readable text file with purchase entries separated by blank lines.
**Structure**:
```
--- New Purchase ---
Date: [date]
User: [username]
[product name] x[quantity]
[product name] x[quantity]
...
Total: $[total]

--- New Purchase ---
...
```
**Example**:
```
--- New Purchase ---
Date: 2025-05-10 16:45:12
User: user
Laptop x1
Total: $999.99

--- New Purchase ---
Date: 2025-05-15 15:44:22
User: user
Headphones x2
Total: $179.98
```

#### 5. product_audit.txt
**Purpose**: Detailed log of all product modifications (create, update, delete).
**Format**: Human-readable text file with one entry per line.
**Structure**:
```
[dateTime] - [username] [action] product ID: [id], Name: [name], Price: $[price], Quantity: [quantity]
```
For updates:
```
[dateTime] - [username] updated product ID: [id], Name: [old name] -> [new name], Price: $[old price] -> $[new price], Quantity: [old quantity] -> [new quantity]
```
**Example**:
```
2025-05-10 00:55:27 - admin created product ID: 1, Name: ipad, Price: $500, Quantity: 10
2025-05-10 00:56:13 - admin created product ID: 2, Name: iphone 16e, Price: $1200, Quantity: 15
2025-05-10 15:42:37 - admin updated product ID: 1, Name: ipad -> iPad Pro, Price: $500 -> $899, Quantity: 10 -> 5
```

### File I/O Operations

The system performs the following file operations:

1. **Read Operations**:
   - Load accounts on program start
   - Load products when a user successfully logs in
   - View purchase history from both the history.txt and user's personal order history
   - View audit trail from product_audit.txt (admin only)

2. **Write Operations**:
   - Save new accounts on user registration
   - Update accounts.txt when a user completes a purchase
   - Update products.txt when products are added, modified, or deleted
   - Create/overwrite invoice.txt during checkout
   - Append to history.txt during checkout
   - Append to product_audit.txt during product management operations

3. **Error Handling**:
   - File existence checks before reading
   - Graceful handling of missing files with default values
   - Transaction safety by saving data immediately after critical operations
   - Try-catch blocks to handle data conversion issues

### Core Functions

1. **User Authentication**
   - `registerUser()`: Creates new user accounts with profile information
   - `login()`: Authenticates users and sets current role
   - `loadAccounts()` & `saveAccounts()`: Manage user data persistence

2. **Product Management**
   - `productManagement()`: Main interface for CRUD operations
   - `saveData()` & `loadData()`: Handle product data persistence
   - Detailed audit trail tracking who created/modified products and when

3. **Shopping Experience**
   - `browseAndBuy()`: View products and add to cart with stock validation
   - `viewCart()`: See current cart contents
   - `removeFromCart()`: Delete items from cart
   - `checkout()`: Complete purchase, update inventory, and generate invoice

4. **Profile & History**
   - `viewUserProfile()`: See account information
   - `viewPurchaseHistory()`: Access order history
   - `viewAllUsers()`: Admin function to see all accounts

5. **Reporting System**
   - `generateReports()`: Creates Excel-compatible CSV files with timestamps
   - Sales reports with transaction details
   - Inventory reports with stock levels and valuation
   - User activity reports with order statistics

6. **Utility Functions**
   - `getCurrentDateTime()`: Get formatted current date/time for records
   - Various menu handling and navigation functions

## System Flowchart

### Main Program Flow

```
┌─────────────────┐
│  Program Start  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Load Accounts  │
└────────┬────────┘
         │
         ▼
┌─────────────────────┐
│   Login/Register    │◄───┐
│       Screen        │    │
└─────────┬───────────┘    │
          │                │
          ▼                │
┌──────────────────────┐   │
│Load & Process Data   │   │
└──────────┬───────────┘   │
           │               │
           ▼               │
┌───────────────────────┐  │
│Role-based Menu Display│  │
└───────────┬───────────┘  │
            │              │
            ▼              │
┌───────────────────────┐  │
│Process Menu Selection │  │
└──────┬───────────┬────┘  │
       │           │       │
       ▼           ▼       │
┌────────────┐ ┌────────┐  │
│Logout?     │ │Exit?   │  │
└──────┬─────┘ └───┬────┘  │
       │Yes         │Yes   │
       │            │      │
       ▼            ▼      │
┌────────────┐ ┌────────┐  │
│Clear State │ │End     │  │
│Return to   │ │Program │  │
│Login       ├─►        │  │
└─────┬──────┘ └────────┘  │
      │                    │
      └────────────────────┘
```

### Detailed Function Flowcharts

For detailed flowcharts of key system functions including Login, Product Management, Checkout, and Browse/Buy processes, see the Full System Documentation.

## Advanced Technical Implementation

### Transaction Management

The system implements basic transaction management to ensure data integrity during operations like checkout:

1. **Pre-transaction Validation**
   - Verifies product availability before checkout
   - Checks that products still exist in database
   - Confirms sufficient quantity for purchase

2. **Atomic Operations**
   - Checkout process completes all steps or none
   - Updates inventory, user history, and global history in sequence
   - Provides rollback capability if any step fails

3. **Audit Preservation**
   - Every product modification is immediately logged
   - Complete trail of who changed what and when
   - Supports administrative oversight and accountability

### Search and Filter Capabilities

While primarily menu-driven, the system offers several ways to find products:

1. **Direct ID Lookup**
   - Products can be accessed by their unique ID
   - Fast retrieval for updates or purchases

2. **Complete Catalog Browsing**
   - Chronological listing of all products
   - Visible stock levels for purchase decisions

3. **Audit Trail Filtering** (Admin only)
   - View modifications by product ID
   - Track history of specific high-value items

### Security Implementation

The system implements several security measures:

1. **Authentication**
   - Username/password validation
   - Role-based access control

2. **Authorization**
   - Function-level permission checking
   - Prevents unauthorized access to admin functions

3. **Session Management**
   - Active user tracking
   - Proper session cleanup on logout

4. **Input Validation**
   - Checks for valid product IDs and quantities
   - Prevents negative quantities or prices
   - Guards against common input errors

## Challenges & Experiences

### Technical Challenges Encountered

1. **File I/O Handling**
   - **Challenge**: Implementing robust file operations that could handle missing files, malformed data, and backward compatibility.
   - **Solution**: Added comprehensive error checking and fallback mechanisms, such as defaulting to predefined accounts when the accounts file is missing and handling different file formats.

2. **User Session Management**
   - **Challenge**: Maintaining proper state between user sessions and preventing data leakage between users.
   - **Solution**: Added proper logout procedures that clear the cart and user state variables, ensuring each user only sees their own data.

3. **Role-Based Access Control**
   - **Challenge**: Ensuring proper separation between admin and user functions.
   - **Solution**: Implemented distinct menu systems and access checks based on the `currentUserRole` variable.

4. **Data Persistence Across Sessions**
   - **Challenge**: Ensuring that all user actions (purchases, product changes) were properly saved.
   - **Solution**: Implemented immediate saving after critical operations and created audit trails for product modifications.

5. **Console-Based UI Limitations**
   - **Challenge**: Creating an intuitive interface within the constraints of a console application.
   - **Solution**: Used clear sections, consistent formatting, and confirmation messages to guide users through the system.

### Learning Experiences

1. **Data Structure Design**
   - Learned the importance of designing flexible data structures (like the Account and Product structs) that can evolve as requirements change
   - Gained experience with using vector containers for dynamic collections

2. **File Format Design**
   - Developed practical knowledge about CSV and other delimited formats
   - Learned techniques for storing hierarchical data (like order history) in flat file formats

3. **Security Considerations**
   - Developed awareness of role-based security principles
   - Learned about proper input validation to prevent system manipulation

4. **User Experience Design**
   - Gained insights into creating intuitive menu flows even in console applications
   - Learned the importance of providing clear feedback for user actions

5. **Software Architecture**
   - Developed skills in organizing code into logical functional units
   - Learned to maintain separation of concerns between different system components

## References & Screenshots

### References

For additional resources on concepts used in this project:

1. **C++ Programming**
   - Stroustrup, B. (2013). *The C++ Programming Language (4th Edition)*
   - C++ Reference: [https://en.cppreference.com/](https://en.cppreference.com/)

2. **File I/O and Data Persistence**
   - Horton, I. (2018). *Beginning C++17: From Novice to Professional*

3. **Console Interface Design**
   - Terminal-based UIs: [https://github.com/topics/terminal-ui](https://github.com/topics/terminal-ui)

### Screenshots

Below are screenshots of different parts of the E-Commerce System application during execution:

#### Login Screen
```
===============================================
           E-COMMERCE SYSTEM LOGIN
===============================================
1. Login
2. Register
3. Exit Program
-----------------------------------------------
Enter choice: 1
===== LOGIN =====
Username: admin
Password: admin123
✅ Login successful! Role: admin
```

#### Admin Menu
```
===============================================
           WELCOME TO E-COMMERCE SYSTEM
===============================================
Current user: admin (Administrator)
1. Product Management (CRUD)
2. Browse Products
3. View All Orders
4. Generate Reports
5. View All Users
6. Save Data to File
7. Load Data from File
8. Logout
9. Exit Program
-----------------------------------------------
Enter your choice (1-9): 1
```

#### Product Management
```
--- PRODUCT MANAGEMENT ---
1. Add New Product
2. View All Products
3. Update Product
4. Delete Product
5. Product Audit Trail
6. Back to Main Menu
Enter your choice (1-6): 2

--- PRODUCT LIST ---
ID: 1, Name: iPad Pro, Price: $899.00, In Stock: 5
  Created by: admin on 2025-05-10 00:55:27
  Last modified by: admin on 2025-05-10 15:42:37
------------------------
ID: 2, Name: iPhone 16e, Price: $1200.00, In Stock: 15
  Created by: admin on 2025-05-10 00:56:13
------------------------
```

For more screenshots and implementation details, refer to the full technical documentation.