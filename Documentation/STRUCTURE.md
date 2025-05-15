# E-Commerce System Structure

This document provides a comprehensive view of the object-oriented structure of the e-commerce system. The diagrams presented here illustrate the relationships between classes, components, and interaction sequences.

## Table of Contents
1. [Class Diagram](#class-diagram)
2. [Component Diagram](#component-diagram)
3. [Sequence Diagram](#sequence-diagram)
4. [Directory Structure](#directory-structure)
5. [Build System](#build-system)

## Class Diagram
The class diagram shows the detailed structure of each class and their relationships:

![Class Diagram](class_diagram.md)

## Component Diagram
The component diagram provides a high-level view of the main components and their interactions:

![Component Diagram](component_diagram.md)

## Sequence Diagram
The sequence diagram illustrates the runtime interactions between different components for key operations:

![Sequence Diagram](sequence_diagram.md)

## Directory Structure
```
E-COMMERCE_SYSTEM/
├── README.md              # Top-level project documentation
├── run_ecommerce.sh       # Script to build and run the system
├── verify_structure.sh    # Script to verify project structure
│
├── Source_Files/          # Source code directory
│   ├── Account.cpp        # Implementation of Account class
│   ├── Account.h          # Header for Account class
│   ├── AuthManager.cpp    # Implementation of authentication
│   ├── AuthManager.h      # Header for authentication
│   ├── CartItem.cpp       # Implementation of cart item
│   ├── CartItem.h         # Header for cart item
│   ├── CheckoutManager.cpp # Implementation of checkout process
│   ├── CheckoutManager.h  # Header for checkout management
│   ├── ECommerceSystem.cpp # Main system implementation
│   ├── ECommerceSystem.h  # Header for main system
│   ├── FileManager.cpp    # Implementation of file operations
│   ├── FileManager.h      # Header for file management
│   ├── Product.cpp        # Implementation of Product class
│   ├── Product.h          # Header for Product class
│   ├── ProductManager.cpp # Implementation of product operations
│   ├── ProductManager.h   # Header for product management
│   ├── ReportGenerator.cpp # Implementation of report generation
│   ├── ReportGenerator.h  # Header for reporting functionality
│   ├── ShoppingCart.cpp   # Implementation of cart operations
│   ├── ShoppingCart.h     # Header for shopping cart
│   ├── main.cpp           # Program entry point
│   └── temp_main.cpp      # Original procedural implementation
│
├── Build_Files/           # Build artifacts directory
│   ├── Makefile           # Build system configuration
│   ├── *.o                # Compiled object files
│   └── ecommerce          # Executable binary
│
├── Data_Files/            # Data storage directory
│   ├── accounts.txt       # User account data
│   ├── products.txt       # Product inventory data
│   ├── history.txt        # Purchase history records
│   ├── invoice.txt        # Generated invoices
│   ├── product_audit.txt  # Product change audit trail
│   └── inventory_log.txt  # Inventory change logs
│
└── Documentation/         # Project documentation
    ├── OOP_DESIGN.md      # Object-oriented design documentation
    ├── STRUCTURE.md       # Project structure documentation (this file)
    ├── DEVELOPER_GUIDE.md # Guide for developers
    ├── FUTURE_DEVELOPMENT.md # Roadmap for future enhancements
    ├── class_diagram.md   # Class structure visualization
    ├── component_diagram.md # Component relationship visualization
    └── sequence_diagram.md # Interaction sequence visualization
```

## Build System
The system uses a Makefile for compilation, located in the Build_Files directory:

```makefile
# E-Commerce System Makefile

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I../Source_Files

# Directories
SRC_DIR = ../Source_Files
OBJ_DIR = .
DATA_DIR = ../Data_Files

# Source files
SRC_FILES = main.cpp \
       Account.cpp \
       Product.cpp \
       CartItem.cpp \
       ShoppingCart.cpp \
       FileManager.cpp \
       AuthManager.cpp \
       ProductManager.cpp \
       CheckoutManager.cpp \
       ReportGenerator.cpp \
       ECommerceSystem.cpp
       
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJS = $(SRC_FILES:.cpp=.o)

# Executable name
TARGET = ecommerce

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

## Helper Scripts

### run_ecommerce.sh
A convenience script that handles building and running the application:
- Checks if the executable exists, and if not, builds it
- Detects if source files have changed and rebuilds if necessary
- Executes the application

```bash
#!/bin/zsh

# Script to compile and run the E-Commerce System
# Created: May 15, 2025

echo "===== E-COMMERCE SYSTEM ====="

# Check if the executable exists, if not compile it
if [ ! -f "Build_Files/ecommerce" ]; then
    echo "Executable not found. Compiling project..."
    cd Build_Files
    make
    cd ..
else
    echo "Executable found."
    
    # Check if any source files are newer than the executable
    if find Source_Files -name "*.cpp" -newer Build_Files/ecommerce | grep -q .; then
        echo "Source files have been modified. Recompiling project..."
        cd Build_Files
        make
        cd ..
    fi
fi

# Check if compilation was successful
if [ -f "Build_Files/ecommerce" ]; then
    echo "Running E-Commerce System..."
    echo "------------------------------"
    cd Build_Files
    ./ecommerce
else
    echo "❌ Compilation failed. Please check for errors and try again."
fi
```

### verify_structure.sh
A script that validates the project structure:
- Checks for required directories
- Verifies source files exist
- Confirms build files are present
- Validates data files
- Ensures documentation is complete

This script helps maintain the integrity of the project structure, especially when multiple developers are working on the codebase.
```

## Data Files
The system uses several data files stored in the Data_Files directory:

### accounts.txt
Stores user account information in CSV format:
```
username,password,fullName,email,role,joinDate
admin,admin123,Administrator,admin@example.com,admin,2025-01-01
user1,pass123,John Doe,john@example.com,customer,2025-03-15
```

### products.txt
Contains the product catalog in CSV format:
```
id,name,price,quantity,description
1,Coffee Mug,12.99,25,Ceramic coffee mug with logo
2,T-Shirt,24.99,50,100% cotton t-shirt
```

### history.txt
Records purchase history for all users:
```
--- PURCHASE: user1 on 2025-04-10 15:30:22 ---
1,Coffee Mug,12.99,2,25.98
2,T-Shirt,24.99,1,24.99
Total: $50.97
```

### invoice.txt
Contains the most recently generated invoice:
```
=============== INVOICE ===============
Date: 2025-05-15 10:22:43
Customer: user1
---------------------------------------
Coffee Mug (x2): $25.98
T-Shirt (x1): $24.99
---------------------------------------
Total: $50.97
Thank you for your purchase!
```

### product_audit.txt
Maintains an audit trail of all product changes:
```
admin,ADD,1,Coffee Mug,12.99,25,2025-05-01 09:15:30
admin,UPDATE,1,Coffee Mug,14.99,20,2025-05-10 11:23:45
```

### inventory_log.txt
Logs all inventory changes:
```
2025-05-10 11:23:45,admin,UPDATE,1,Coffee Mug,25,20,-5
2025-05-15 10:22:43,user1,PURCHASE,1,Coffee Mug,20,18,-2
```
