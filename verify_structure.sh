#!/bin/bash
# Script to verify the E-Commerce System directory structure

echo "=== E-Commerce System Structure Verification ==="
echo ""

# Check main directories
echo "Checking main directories..."
directories=("Source_Files" "Build_Files" "Data_Files" "Documentation")
for dir in "${directories[@]}"; do
    if [ -d "$dir" ]; then
        echo "✅ $dir directory exists"
    else
        echo "❌ $dir directory is missing"
    fi
done

echo ""
echo "Checking source files..."
# Check that source files exist
source_files=(
    "Source_Files/main.cpp"
    "Source_Files/Account.h" "Source_Files/Account.cpp"
    "Source_Files/Product.h" "Source_Files/Product.cpp"
    "Source_Files/CartItem.h" "Source_Files/CartItem.cpp"
    "Source_Files/ShoppingCart.h" "Source_Files/ShoppingCart.cpp"
    "Source_Files/FileManager.h" "Source_Files/FileManager.cpp"
    "Source_Files/AuthManager.h" "Source_Files/AuthManager.cpp"
    "Source_Files/ProductManager.h" "Source_Files/ProductManager.cpp"
    "Source_Files/CheckoutManager.h" "Source_Files/CheckoutManager.cpp"
    "Source_Files/ReportGenerator.h" "Source_Files/ReportGenerator.cpp"
    "Source_Files/ECommerceSystem.h" "Source_Files/ECommerceSystem.cpp"
)

for file in "${source_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file exists"
    else
        echo "❌ $file is missing"
    fi
done

echo ""
echo "Checking build files..."
# Check that build files exist
build_files=(
    "Build_Files/Makefile"
    "Build_Files/ecommerce"
)

for file in "${build_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file exists"
    else
        echo "❌ $file is missing"
    fi
done

echo ""
echo "Checking data files..."
# Check that data files exist
data_files=(
    "Data_Files/accounts.txt"
    "Data_Files/products.txt"
    "Data_Files/history.txt"
    "Data_Files/invoice.txt"
    "Data_Files/product_audit.txt"
    "Data_Files/inventory_log.txt"
)

for file in "${data_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file exists"
    else
        echo "❌ $file is missing"
    fi
done

echo ""
echo "Checking documentation files..."
# Check that documentation files exist
doc_files=(
    "Documentation/OOP_DESIGN.md"
    "Documentation/STRUCTURE.md"
    "Documentation/class_diagram.md"
    "Documentation/component_diagram.md"
    "Documentation/sequence_diagram.md"
)

for file in "${doc_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file exists"
    else
        echo "❌ $file is missing"
    fi
done

echo ""
echo "=== Verification Complete ==="
