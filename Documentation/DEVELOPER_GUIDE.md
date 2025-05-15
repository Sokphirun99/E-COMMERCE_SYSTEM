# Developer Guide

This document provides guidance for developers who want to contribute to the E-Commerce System project.

## Development Environment Setup

1. **Prerequisites**
   - C++ compiler (g++ or equivalent, supporting C++11 or later)
   - Make build system
   - Git version control
   - Text editor or IDE with C++ support (VSCode, CLion, etc.)

2. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd E-COMMERCE_SYSTEM
   ```

3. **Project Structure**
   - Source_Files/ - All C++ source code
   - Build_Files/ - Makefile and build artifacts
   - Data_Files/ - Data storage files
   - Documentation/ - Project documentation

## Build and Run

1. **Build the Project**
   ```bash
   cd Build_Files
   make
   ```

2. **Run the Application**
   ```bash
   ./ecommerce
   ```

3. **Clean Build**
   ```bash
   make clean
   ```

4. **Quick Start Script**
   ```bash
   # From project root
   ./run_ecommerce.sh
   ```

## Development Workflow

1. **Creating a New Feature**
   - Create a feature branch: `git checkout -b feature/feature-name`
   - Implement the feature
   - Test thoroughly
   - Create a pull request

2. **Adding a New Class**
   - Create header (.h) and implementation (.cpp) files in Source_Files/
   - Follow the naming convention: PascalCase for class names
   - Update Makefile to include new source files
   - Document class purpose and relationships

3. **Code Style Guidelines**
   - Use consistent indentation (4 spaces recommended)
   - Follow C++ best practices
   - Add comments for complex code sections
   - Use meaningful variable and function names
   - Keep functions short and focused on a single task

## Testing

1. **Manual Testing**
   - Test each feature from user perspective
   - Verify edge cases and error handling
   - Check for memory leaks and performance issues

2. **Automated Testing (future)**
   - Unit tests for each class
   - Integration tests for system components
   - Run tests before submitting changes

## Documentation

1. **Code Documentation**
   - Add descriptive comments to classes and methods
   - Update class diagrams when changing class relationships
   - Document public interfaces thoroughly

2. **User Documentation**
   - Update README.md with new features
   - Keep user guide current
   - Document configuration options

## Common Tasks

1. **Adding a New Product Field**
   - Update Product.h and Product.cpp
   - Modify FileManager to persist the new field
   - Update UI components that display product information

2. **Adding a New User Role**
   - Extend Account class
   - Update AuthManager for role-specific permissions
   - Modify UI to show role-specific menus

3. **Adding a New Report**
   - Create new method in ReportGenerator
   - Implement data gathering logic
   - Format report output
   - Add UI option to access the report
