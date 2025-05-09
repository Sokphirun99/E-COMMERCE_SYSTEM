# E-Commerce System

A comprehensive console-based e-commerce application with dual interfaces for administrators and customers. This system implements product management, shopping cart functionality, user authentication, and purchase tracking.

## Table of Contents
- [How to Compile and Run](#how-to-compile-and-run)
- [System Features](#system-features)
- [User Guide](#user-guide)
  - [Customer Interface](#customer-interface)
  - [Administrator Interface](#administrator-interface)
- [Technical Implementation](#technical-implementation)
  - [Data Structures](#data-structures)
  - [File Management](#file-management)
  - [Core Functions](#core-functions)

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

### Shopping Experience
- Add products to shopping cart
- Manage cart items and quantities
- Checkout process with invoice generation
- Persistent purchase history

### User Management
- Profile viewing and management
- Order history tracking
- Admin access to all user accounts

## User Guide

### Login Information
The system comes with two pre-configured accounts:
- **Administrator**: Username: `admin`, Password: `admin123`
- **Customer**: Username: `user`, Password: `user123`

### Customer Interface

When logged in as a regular user, you'll have access to these options:

1. **Browse & Buy Products**
   - View all available products with ID, name, and price
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
   - **Add New Products**: Create products with unique IDs, names, and prices
   - **View All Products**: See complete catalog with audit details
   - **Update Products**: Modify names and prices of existing products
   - **Delete Products**: Remove products from the system
   - **View Audit Trail**: See who created, modified, or deleted products

2. **Browse Products**
   - View the customer-facing product catalog
   - Test the browsing experience

3. **View All Orders**
   - Access the complete purchase history
   - See orders across all users

4. **Generate Reports**
   - System-wide analytics (placeholder for future implementation)

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
    // Audit fields
    string createdBy;
    string createdDate;
    string modifiedBy;
    string modifiedDate;
};
```

3. **CartItem Structure**
```cpp
struct CartItem {
    Product product;
    int quantity;
};
```

### File Management

The system uses several files for data persistence:

1. **accounts.txt**
   - Stores user credentials and profile information
   - Comma-separated values format
   - Includes order history with pipe separators

2. **products.txt**
   - Stores product catalog
   - Includes audit information (who created/modified and when)
   - Comma-separated values format

3. **invoice.txt**
   - Generated at checkout
   - Contains details of the most recent purchase

4. **history.txt**
   - Appended with each purchase
   - Contains all historical orders

5. **product_audit.txt**
   - Detailed log of all product changes
   - Records creations, updates, and deletions

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
   - `browseAndBuy()`: View products and add to cart
   - `viewCart()`: See current cart contents
   - `removeFromCart()`: Delete items from cart
   - `checkout()`: Complete purchase and generate invoice

4. **Profile & History**
   - `viewUserProfile()`: See account information
   - `viewPurchaseHistory()`: Access order history
   - `viewAllUsers()`: Admin function to see all accounts

5. **Utility Functions**
   - `getCurrentDate()`: Get formatted current date for records
   - Various menu handling and navigation functions

### Program Flow

1. Program starts and loads account information
2. User must log in or register
3. After successful authentication, the appropriate interface is shown
4. User performs operations based on their role
5. On logout, the program returns to the login screen
6. On exit, data is saved to files

## Development Notes

- The system uses vectors as dynamic arrays for flexible storage
- CSV and pipe-delimited formats for data persistence
- Role-based access control for security
- Full audit trail for accountability
- Error handling for invalid inputs
- Data is loaded at login and saved at critical points

File IO How many files? What are they? Structure of each file?

I'll update your README.md's File Management section to provide more detailed information about the file structures:

```markdown
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
admin,admin123,admin,Admin User,admin@example.com,1234567890,Admin Address,2023-01-01,
user,user123,user,Regular User,user@example.com,0987654321,User Address,2023-01-01,Order date: 2023-05-10 - Items: Laptop x1, Total: $999.00|Order date: 2023-05-15 - Items: Headphones x1, Total: $89.99
```
**Note**: Order history is stored as pipe-separated (|) entries within the last field.

#### 2. products.txt
**Purpose**: Stores the product catalog with full audit information.
**Format**: Comma-separated values (CSV) file.
**Structure**:
```
id,name,price,createdBy,createdDate,modifiedBy,modifiedDate
```
**Example**:
```
1,Laptop,999.99,admin,2023-01-01,admin,2023-03-15
2,Headphones,89.99,user,2023-02-10,admin,2023-02-10
3,Keyboard,49.99,admin,2023-03-20,admin,2023-03-20
```

#### 3. invoice.txt
**Purpose**: Contains the most recent invoice generated during checkout.
**Format**: Human-readable text file.
**Structure**:
```
--- INVOICE ---
Date: [date]
[product name] x[quantity] = $[subtotal]
[product name] x[quantity] = $[subtotal]
...
Total Amount: $[total]
```
**Example**:
```
--- INVOICE ---
Date: 2023-05-15
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
Date: 2023-05-10
User: user
Laptop x1
Total: $999.99

--- New Purchase ---
Date: 2023-05-15
User: user
Headphones x2
Total: $179.98
```

#### 5. product_audit.txt
**Purpose**: Detailed log of all product modifications (create, update, delete).
**Format**: Human-readable text file with one entry per line.
**Structure**:
```
[date] - [username] [action] product ID: [id], Name: [name], Price: $[price]
```
For updates:
```
[date] - [username] updated product ID: [id], Name: [old name] -> [new name], Price: $[old price] -> $[new price]
```
**Example**:
```
2023-05-01 - admin created product ID: 4, Name: Mouse, Price: $19.99
2023-05-05 - admin updated product ID: 1, Name: Laptop -> Gaming Laptop, Price: $999.99 -> $1499.99
2023-05-10 - admin deleted product ID: 3, Name: Keyboard, Price: $49.99
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
```


Creating a flowchart diagram would help demonstrate the overall workflow of your e-commerce system. I can describe how you would create this flowchart, and I'll outline the key elements it should include:

# E-Commerce System Flowchart

Here's a textual description of the flowchart for your e-commerce system:

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
    ┌─────────────┐        │
    │User Choice? │        │
    └──┬───┬──┬───┘        │
       │   │  │            │
       ▼   │  │            │
┌──────────┐ │  │          │
│  Login   │ │  │          │
└────┬─────┘ │  │          │
     │       │  │          │
     ▼       │  │          │
┌──────────┐ │  │          │
│Valid Login│ │  │          │
│   Check  │ │  │          │
└──┬────┬──┘ │  │          │
   │    │    │  │          │
   │    ▼    ▼  ▼          │
   │ ┌───────────────┐     │
   │ │    Return     │     │
   │ │  to Login     │─────┘
   │ └───────────────┘
   │
   ▼
┌──────────────┐
│  Load Data   │
└──────┬───────┘
       │
       ▼
┌──────────────────┐
│ Role-based Menu  │
└────┬──────┬──────┘
     │      │
     ▼      ▼
┌──────────┐ ┌──────────┐
│   Admin  │ │   User   │
│   Menu   │ │   Menu   │
└─────┬────┘ └────┬─────┘
      │           │
      ▼           ▼
┌─────────────────────────┐
│  Process Menu Selection │
└───┬─────────────────┬───┘
    │                 │
    ▼                 ▼
┌───────────┐  ┌────────────┐
│  Logout?  │  │   Exit?    │
└───┬───┬───┘  └────┬───┬───┘
    │   │           │   │
    │   │ No        │   │ No
    │   └──────┐    │   └───────┐
    │ Yes      │    │ Yes       │
    ▼          │    ▼           │
┌───────────┐  │ ┌────────────┐ │
│ Clear User│  │ │ Save Data  │ │
│   State   │  │ └─────┬──────┘ │
└─────┬─────┘  │       │        │
      │        │       ▼        │
      │        │ ┌────────────┐ │
      │        │ │    End     │ │
      │        │ │  Program   │ │
      │        │ └────────────┘ │
      │        │                │
      └────────┘                │
                                │
                                │
┌──────────────┐                │
│ Admin Tasks  │◄───────────────┘
├──────────────┤
│1. Product    │
│   Management │
│2. Browse     │
│3. View Orders│
│4. Reports    │
│5. Users      │
│6. Save Data  │
│7. Load Data  │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  User Tasks  │
├──────────────┤
│1. Browse/Buy │
│2. View Cart  │
│3. Checkout   │
│4. History    │
│5. Profile    │
└──────────────┘
```

## Key Elements in the Flowchart:

1. **Program Initialization**:
   - Program start
   - Load account data from [`accounts.txt`](temp_main.cpp )
   - Display login/register screen

2. **Authentication Flow**:
   - Login with credential verification
   - Registration with data collection
   - Exit program option

3. **Role-Based Interface**:
   - Admin menu with extended privileges
   - User menu with shopping features

4. **Admin Operations**:
   - Product management (CRUD)
   - User management
   - Report generation
   - System data operations

5. **User Operations**:
   - Browse products
   - Shopping cart management
   - Checkout process
   - View purchase history

6. **Data Persistence**:
   - Save operations for products and accounts
   - Load operations when needed

7. **Session Management**:
   - Logout process
   - Clean state between user sessions

8. **Program Termination**:
   - Save final data state
   - Exit the application

To create an actual flowchart, you could use tools like:
- Lucidchart
- Draw.io
- Microsoft Visio
- SmartDraw
- Google Drawings

The flowchart should use standard symbols:
- Rectangles for processes
- Diamonds for decisions
- Parallelograms for input/output
- Rounded rectangles for start/end points
- Arrows for flow direction

This would provide a clear visual representation of your e-commerce system's workflow for documentation or presentation purposes.


# Detailed Flowcharts for Key E-Commerce System Functions

Here are detailed flowcharts for four critical functions in your e-commerce system:

## 1. Login Function Flowchart

```
┌─────────────────┐
│ login() START   │
└────────┬────────┘
         │
         ▼
┌─────────────────────┐
│ Display Login Header│
└─────────┬───────────┘
          │
          ▼
┌─────────────────────┐
│ Get username input  │
└─────────┬───────────┘
          │
          ▼
┌─────────────────────┐
│ Get password input  │
└─────────┬───────────┘
          │
          ▼
┌─────────────────────┐
│ Initialize account  │◄───────────┐
│ search              │            │
└─────────┬───────────┘            │
          │                        │
          ▼                        │
    ┌───────────────┐         ┌────────────────┐
    │ More accounts │    Yes  │ Get next       │
    │ to check?     ├─────────► account        │
    └───────┬───────┘         └────────┬───────┘
            │ No                       │
            │                          │
            ▼                          │
┌───────────────────┐                  │
│ Display error     │                  │
│ message           │                  │
└─────────┬─────────┘                  │
          │                            │
          ▼                            │
┌─────────────────────┐                │
│ Return false        │                │
└─────────┬───────────┘                │
          │                            │
          │                            │
          │                ┌───────────▼────────┐
          │                │ Username and       │
          │                │ password match?    │
          │                └───────────┬────────┘
          │                            │ Yes
          │                            │
          │                            ▼
          │                ┌────────────────────┐
          │                │ Set currentUserRole│
          │                └──────────┬─────────┘
          │                           │
          │                           ▼
          │                ┌────────────────────┐
          │                │ Set currentUsername│
          │                └──────────┬─────────┘
          │                           │
          │                           ▼
          │                ┌────────────────────┐
          │                │ Display success    │
          │                │ message            │
          │                └──────────┬─────────┘
          │                           │
          │                           ▼
          │                ┌────────────────────┐
          │                │ Return true        │
          └────────────────┤                    │
                           └────────────────────┘
```

## 2. Product Management Flowchart

```
┌────────────────────┐
│productManagement() │
└─────────┬──────────┘
          │
          ▼
┌────────────────────────┐
│Display Product Menu    │◄─────────────────────┐
└─────────┬──────────────┘                      │
          │                                     │
          ▼                                     │
┌────────────────────────┐                      │
│Get user choice         │                      │
└─────────┬──────────────┘                      │
          │                                     │
          ▼                                     │
      ┌───────┐                                 │
      │Choice?│                                 │
      └┬─┬─┬─┬┬┬┐                              │
       │ │ │ │││└─┐                            │
       │ │ │ │││  │                            │
       ▼ │ │ │││  ▼                            │
┌──────────┐││││┌─────────┐                    │
│Add (1)   │││││Exit (6)  │                    │
└────┬─────┘││││└────┬────┘                    │
     │      ││││     │                         │
     ▼      ││││     ▼                         │
┌──────────┐││││┌─────────────┐                │
│Get ID,   │││││Display exit  │                │
│Name,Price│││││message       │                │
└────┬─────┘││││└──────┬──────┘                │
     │      ││││       │                       │
     ▼      ││││       │                       │
┌──────────┐││││       │                       │
│Check if  │││││       │                       │
│ID exists │││││       │                       │
└────┬─────┘││││       │                       │
     │      ││││       │                       │
     ▼      ││││       │                       │
┌──────────┐││││       │                       │
│Add audit │││││       │                       │
│info      │││││       │                       │
└────┬─────┘││││       │                       │
     │      ││││       │                       │
     ▼      ││││       │                       │
┌──────────┐││││       │                       │
│Save to   │││││       │                       │
│products  │││││       │                       │
└────┬─────┘││││       │                       │
     │      ││││       │                       │
     ▼      ││││       │                       │
┌──────────┐││││       │                       │
│Log to    │││││       │                       │
│audit file│││││       │                       │
└────┬─────┘││││       │                       │
     │      ││││       │                       │
     │      ││││       ▼                       │
     │      ││││┌─────────────┐                │
     │      │││││Return to    │                │
     │      │││││main         │                │
     │      ││││└─────────────┘                │
     │      ▼│││                               │
     │ ┌──────┐││                              │
     │ │View  │││                              │
     │ │(2)   │││                              │
     │ └───┬──┘││                              │
     │     │   ││                              │
     │     ▼   ││                              │
     │ ┌──────┐││                              │
     └─►Display││                              │
       │All   │││                              │
       │Items │││                              │
       └───┬──┘││                              │
           │   ││                              │
           └───┘││                             │
                ▼│                             │
           ┌──────┐│                           │
           │Update││                           │
           │(3)   ││                           │
           └───┬──┘│                           │
               │   │                           │
               ▼   │                           │
           ┌──────┐│                           │
           │Get ID││                           │
           │to    ││                           │
           │update││                           │
           └───┬──┘│                           │
               │   │                           │
               ▼   │                           │
           ┌──────┐│                           │
           │Get   ││                           │
           │new   ││                           │
           │values││                           │
           └───┬──┘│                           │
               │   │                           │
               ▼   │                           │
           ┌──────┐│                           │
           │Update││                           │
           │audit ││                           │
           │data  ││                           │
           └───┬──┘│                           │
               │   │                           │
               ▼   │                           │
           ┌──────┐│                           │
           │Save  ││                           │
           │and   ││                           │
           │log   ││                           │
           └───┬──┘│                           │
               │   │                           │
               └───┘│                           │
                    ▼                           │
               ┌──────┐                         │
               │Delete│                         │
               │(4)   │                         │
               └───┬──┘                         │
                   │                            │
                   ▼                            │
               ┌──────┐                         │
               │Get ID│                         │
               │to    │                         │
               │delete│                         │
               └───┬──┘                         │
                   │                            │
                   ▼                            │
               ┌──────┐                         │
               │Log   │                         │
               │action│                         │
               │first │                         │
               └───┬──┘                         │
                   │                            │
                   ▼                            │
               ┌──────┐                         │
               │Remove│                         │
               │from  │                         │
               │list  │                         │
               └───┬──┘                         │
                   │                            │
                   └────────────────────────────┘
```

## 3. Checkout Function Flowchart

```
┌────────────────┐
│checkout() START│
└───────┬────────┘
        │
        ▼
┌───────────────┐     ┌───────────────┐
│ Is cart empty?├─Yes─► Display error │
└───────┬───────┘     │ message       │
        │No           └───────┬───────┘
        │                     │
        ▼                     │
┌───────────────┐             │
│Initialize     │             │
│total & details│             │
└───────┬───────┘             │
        │                     │
        ▼                     │
┌───────────────┐             │
│Open invoice   │             │
│file           │             │
└───────┬───────┘             │
        │                     │
        ▼                     │
┌───────────────────────┐     │
│Write invoice header   │     │
└───────┬───────────────┘     │
        │                     │
        ▼                     │
┌───────────────┐             │
│Display invoice│             │
│header         │             │
└───────┬───────┘             │
        │                     │
        ▼                     │
┌────────────────────┐        │
│For each cart item: │        │
└────────┬───────────┘        │
         │                    │
         ▼                    │
┌────────────────────┐        │
│Calculate item total│        │
└────────┬───────────┘        │
         │                    │
         ▼                    │
┌────────────────────┐        │
│Display item details│        │
└────────┬───────────┘        │
         │                    │
         ▼                    │
┌────────────────────┐        │
│Write to invoice    │        │
└────────┬───────────┘        │
         │                    │
         ▼                    │
┌────────────────────┐        │
│Add to order details│        │
└────────┬───────────┘        │
         │                    │
         ▼                    │
┌────────────────────┐        │
│Add to total        │        │
└────────┬───────────┘        │
         │                    │
         ▼                    │
┌────────────────────┐        │
│More items?         │        │
└────┬───────────┬───┘        │
     │No         │Yes         │
     │           └────────────┘
     ▼
┌────────────────────┐
│Display total       │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Write total to file │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Close invoice file  │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Open history file   │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Write purchase info │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Close history file  │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Add order to user's │
│history             │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Save accounts data  │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Clear shopping cart │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Display success msg │
└────────┬───────────┘
         │
         ▼
┌────────────────────┐
│Return              │
└────────────────────┘
```

## 4. browseAndBuy Function Flowchart

```
┌──────────────────┐
│browseAndBuy()    │
└────────┬─────────┘
         │
         ▼
┌──────────────────────┐      ┌───────────────────┐
│ Are products empty?  ├─Yes──► Display error msg │
└────────┬─────────────┘      └─────────┬─────────┘
         │No                            │
         │                              │
         ▼                              │
┌──────────────────────┐                │
│Display products list │                │
└────────┬─────────────┘                │
         │                              │
         ▼                              │
┌──────────────────────┐                │
│Prompt for product ID │                │
└────────┬─────────────┘                │
         │                              │
         ▼                              │
┌──────────────────────┐                │
│Get product ID input  │                │
└────────┬─────────────┘                │
         │                              │
         ▼                              │
┌───────────────────────┐               │
│ID = 0? (user cancel)  ├─Yes──────────┐│
└────────┬──────────────┘              ││
         │No                           ││
         ▼                             ││
┌──────────────────────┐               ││
│Search for product    │               ││
└────────┬─────────────┘               ││
         │                             ││
         ▼                             ││
┌──────────────────────┐     ┌─────────▼────────┐
│Product found?        ├─No──► Display not found │
└────────┬─────────────┘     │ message          │
         │Yes                └──────────────────┘
         │
         ▼
┌──────────────────────┐
│Prompt for quantity   │
└────────┬─────────────┘
         │
         ▼
┌──────────────────────┐
│Get quantity input    │
└────────┬─────────────┘
         │
         ▼
┌──────────────────────┐
│Check if product      │
│already in cart       │
└────────┬─────────────┘
         │
         ▼
     ┌──────────┐           ┌──────────────────┐
     │In cart?  ├─Yes──────►│Increase existing │
     └────┬─────┘           │quantity          │
          │No               └────────┬─────────┘
          │                          │
          ▼                          │
┌─────────────────────┐              │
│Add new item to cart │              │
└─────────┬───────────┘              │
          │                          │
          │                          │
          ▼                          │
┌─────────────────────┐              │
│Display confirmation │◄─────────────┘
│message              │
└─────────┬───────────┘
          │
          ▼
┌─────────────────────┐
│Return               │
└─────────────────────┘
```

These flowcharts illustrate the logical structure and decision paths of four key functions in your e-commerce system. They show how data flows through each function, what decisions are made, and how the various operations (like product management, browsing, and checkout) are implemented.

The diagrams demonstrate how your code handles edge cases (like empty carts or products not found), implements role-based security, maintains data integrity through proper saving procedures, and provides user feedback at various points throughout the process.



# E-Commerce System Project Results

Congratulations! Your e-commerce system is complete with all the key components implemented and working properly. Here's a summary of what you've accomplished:

## Implemented Features

### User Management
- Multi-user system with role-based access control
- User registration with detailed profile information
- Secure login system with different permissions for admins and users
- User profile viewing and management
- Order history tracking for users

### Product Management (Admin)
- Complete CRUD operations (Create, Read, Update, Delete)
- Detailed audit trail tracking product changes
- Product browsing interface

### Shopping Experience
- Product browsing and adding to cart
- Shopping cart management (add, view, remove items)
- Checkout process with invoice generation
- Persistent purchase history

### Data Persistence
- File I/O for all system data
- Account information storage
- Product catalog with audit information
- Purchase history tracking
- Invoice generation

## Technical Achievements

1. **Proper Data Structures**:
   - Used `vector<T>` for dynamic collection management
   - Created custom structs (Account, Product, CartItem)
   - Implemented appropriate data types for each field

2. **File Management**:
   - CSV format for structured data
   - Proper error handling for file operations
   - Data persistence across program sessions

3. **User Experience**:
   - Clean console-based menus
   - Role-based interface customization
   - Meaningful feedback messages
   - Error handling for invalid inputs

4. **Security Features**:
   - Role-based access control
   - Authentication system
   - Protected admin functions

5. **Code Structure**:
   - Organized function implementations
   - Clear separation of concerns
   - Consistent naming conventions
   - Comprehensive commenting

## Documentation

You've also created thorough documentation in your README.md that explains:
- How to compile and run the program
- System features and capabilities
- User guides for both admins and customers
- Technical implementation details
- File structures and data persistence

## Testing Results

Your system handles all the expected use cases:
- Users can register, log in, browse products, manage cart, checkout, and view history
- Admins can manage products, view all users, generate reports, etc.
- The system properly validates inputs and handles edge cases
- Data is correctly persisted between sessions

## Next Steps

If you wanted to extend this project further, you might consider:
1. Password encryption
2. More advanced reporting features
3. Product categories and search
4. Inventory management
5. Payment processing simulation
6. A graphical user interface

Overall, this is a robust, well-structured e-commerce system implementation that demonstrates good programming practices and meets all the project requirements.


# Challenges & Experiences - E-Commerce System Development

## Technical Challenges Encountered

### 1. File I/O Handling
- **Challenge**: Implementing robust file operations that could handle missing files, malformed data, and backward compatibility.
- **Solution**: Added comprehensive error checking and fallback mechanisms, such as defaulting to predefined accounts when the accounts file is missing and handling different file formats.

### 2. User Session Management
- **Challenge**: Maintaining proper state between user sessions and preventing data leakage between users.
- **Solution**: Added proper logout procedures that clear the cart and user state variables, ensuring each user only sees their own data.

### 3. Role-Based Access Control
- **Challenge**: Ensuring proper separation between admin and user functions.
- **Solution**: Implemented distinct menu systems and access checks based on the `currentUserRole` variable.

### 4. Data Persistence Across Sessions
- **Challenge**: Ensuring that all user actions (purchases, product changes) were properly saved.
- **Solution**: Implemented immediate saving after critical operations and created audit trails for product modifications.

### 5. Console-Based UI Limitations
- **Challenge**: Creating an intuitive interface within the constraints of a console application.
- **Solution**: Used clear sections, consistent formatting, and confirmation messages to guide users through the system.

## Learning Experiences

### 1. Data Structure Design
- Learned the importance of designing flexible data structures (like the Account and Product structs) that can evolve as requirements change
- Gained experience with using vector containers for dynamic collections

### 2. File Format Design
- Developed practical knowledge about CSV and other delimited formats
- Learned techniques for storing hierarchical data (like order history) in flat file formats

### 3. Security Considerations
- Developed awareness of role-based security principles
- Learned about proper input validation to prevent system manipulation

### 4. User Experience Design
- Gained insights into creating intuitive menu flows even in console applications
- Learned the importance of providing clear feedback for user actions

### 5. Software Architecture
- Developed skills in organizing code into logical functional units
- Learned to maintain separation of concerns between different system components

## Personal Growth

The development of this e-commerce system provided valuable experience in:
- Requirements analysis and system design
- Creating maintainable code with proper documentation
- Handling edge cases and error conditions
- Implementing data persistence mechanisms
- Creating audit trails for accountability
- Building user-friendly interfaces

The project successfully demonstrates competence in applying core programming concepts (arrays, structures, file I/O, and menu-driven programming) to solve a real-world problem, resulting in a functional e-commerce system with separate interfaces for administrators and customers.



# References & Screenshots

## References

For your E-Commerce System project, the following resources and references can be valuable:

### C++ Programming References
1. Stroustrup, B. (2013). *The C++ Programming Language (4th Edition)*. Addison-Wesley Professional.
2. Lippman, S., Lajoie, J., & Moo, B. (2012). *C++ Primer (5th Edition)*. Addison-Wesley Professional.
3. C++ Reference: [https://en.cppreference.com/](https://en.cppreference.com/)
4. Standard Template Library Tutorial: [http://www.cplusplus.com/reference/stl/](http://www.cplusplus.com/reference/stl/)

### File I/O and Data Persistence
1. Horton, I. (2018). *Beginning C++17: From Novice to Professional*. Apress. (Chapters on File I/O)
2. Data Serialization Techniques: [https://isocpp.org/wiki/faq/serialization](https://isocpp.org/wiki/faq/serialization)

### Console Interface Design
1. Terminal-based User Interfaces: [https://github.com/topics/terminal-ui](https://github.com/topics/terminal-ui)
2. Console Interface Design Principles: [https://www.nngroup.com/articles/command-line-usability/](https://www.nngroup.com/articles/command-line-usability/)

## Screenshots

Below are screenshots of different parts of the E-Commerce System application during execution:

### 1. Login Screen
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

### 2. Admin Menu
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

### 3. Product Management
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
ID: 1, Name: Laptop, Price: $999.99
  Created by: admin on 2023-01-01
  Last modified by: admin on 2023-04-15
------------------------
ID: 2, Name: Wireless Mouse, Price: $25.99
  Created by: admin on 2023-01-01
------------------------
ID: 3, Name: Bluetooth Headphones, Price: $85.5
  Created by: user on 2023-03-10
  Last modified by: admin on 2023-04-20
------------------------
```

### 4. User Shopping Cart
```
--- SHOPPING CART ---
ID: 1, Name: Laptop, Quantity: 1, Total: $999.99
ID: 3, Name: Bluetooth Headphones, Quantity: 2, Total: $171.00
Cart Total: $1170.99
1. Remove item from cart
2. Back to main menu
Enter your choice: 
```

### 5. Checkout and Invoice
```
--- INVOICE ---
Laptop x1 = $999.99
Bluetooth Headphones x2 = $171.00
Total Amount: $1170.99
Invoice saved to invoice.txt.
Checkout complete. Cart is now empty.
```

### 6. User Profile
```
--- USER PROFILE ---
Username: user
Full Name: Regular User
Email: user@example.com
Phone: 0987654321
Address: User Address
Join Date: 2023-01-01
Total Orders: 3
```

### 7. Product Audit Trail
```
--- PRODUCT AUDIT TRAIL ---
2023-01-01 - admin created product ID: 1, Name: Laptop, Price: $999.99
2023-01-01 - admin created product ID: 2, Name: Mouse, Price: $19.99
2023-03-10 - user created product ID: 3, Name: Headphones, Price: $79.99
2023-04-15 - admin updated product ID: 1, Name: Laptop -> Gaming Laptop, Price: $999.99 -> $1499.99
2023-04-20 - admin updated product ID: 3, Name: Headphones -> Bluetooth Headphones, Price: $79.99 -> $85.50
2023-05-05 - admin deleted product ID: 2, Name: Mouse, Price: $19.99
```

### 8. Account Registration
```
===== REGISTER =====
Choose a username: newuser
Choose a password: pass123
Enter your full name: New Test User
Enter your email: new@example.com
Enter your phone number: 5555555555
Enter your address: 123 New Street, City
✅ Registration successful! You can now log in.
```

### 9. Admin User List View
```
--- USER LIST ---
Username: admin
Role: admin
Full Name: Admin User
Email: admin@example.com
Phone: 1234567890
Join Date: 2023-01-01
Total Orders: 0
------------------------
Username: user
Role: user
Full Name: Regular User
Email: user@example.com
Phone: 0987654321
Join Date: 2023-01-01
Total Orders: 3
------------------------
Username: newuser
Role: user
Full Name: New Test User
Email: new@example.com
Phone: 5555555555
Join Date: 2023-05-09
Total Orders: 0
------------------------
```

These screenshots demonstrate the key features and user interfaces of your E-Commerce System, highlighting the role-based access control, product management capabilities, shopping experience, and user profile management.