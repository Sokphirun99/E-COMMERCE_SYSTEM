# E-Commerce System Quick Reference

## Quick Start

1. **Run the application**
   ```bash
   ./run_ecommerce.sh
   ```

2. **Verify project structure**
   ```bash
   ./verify_structure.sh
   ```

3. **Build manually**
   ```bash
   cd Build_Files
   make
   ```

## Default User Accounts

| Username | Password | Role |
|----------|----------|------|
| admin    | admin123 | Administrator |
| user     | user123  | Customer |

## Directory Structure

```
E-COMMERCE_SYSTEM/
├── Source_Files/    # Source code (.cpp, .h)
├── Build_Files/     # Build artifacts (Makefile, .o files)
├── Data_Files/      # Data storage files
└── Documentation/   # Project documentation
```

## Key Classes

- **Account**: User account data model
- **Product**: Product data model
- **ShoppingCart**: Shopping cart implementation with CartItem instances
- **AuthManager**: Handles user authentication and authorization
- **ProductManager**: Manages product operations (CRUD)
- **FileManager**: Handles all file I/O operations
- **CheckoutManager**: Processes checkout operations
- **ReportGenerator**: Generates various system reports
- **ECommerceSystem**: Main controller for the application

## File Paths

All file paths in the code are relative to the directory where the executable runs:
- Data files: `../Data_Files/filename.txt`
- Source files: `../Source_Files/filename.cpp`

## Common Development Tasks

1. **Adding a new class**
   - Create header (.h) and implementation (.cpp) files in Source_Files/
   - Add the new .cpp file to the SRC_FILES list in the Makefile
   - Update related classes to use the new class

2. **Modifying file paths**
   - All file paths should reference files in the Data_Files directory
   - Format: `../Data_Files/filename.txt`

3. **Making a code change**
   - Edit files in Source_Files/
   - Run `./run_ecommerce.sh` to build and test changes

4. **Adding documentation**
   - Add new documentation files to the Documentation/ directory
   - Update STRUCTURE.md if project structure changes

## Debugging Tips

1. Check file paths if getting "file not found" errors
2. Use the verify_structure.sh script to confirm proper project organization
3. Look for compilation errors in the Build_Files directory
4. Test with admin and user accounts to verify role-based functionality
