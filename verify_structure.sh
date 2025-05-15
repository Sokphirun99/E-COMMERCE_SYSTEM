#!/bin/zsh

echo "===== E-COMMERCE SYSTEM STRUCTURE VERIFICATION ====="
echo "Checking project structure..."

# Check main directories
directories=("Source_Files" "Build_Files" "Data_Files" "Documentation")
missing_directories=0

for dir in "${directories[@]}"; do
    if [ -d "$dir" ]; then
        echo "✅ Directory exists: $dir"
    else
        echo "❌ Missing directory: $dir"
        missing_directories=$((missing_directories + 1))
    fi
done

# Check source files
required_source_files=(
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

echo "\n===== SOURCE FILES CHECK ====="
missing_source_files=0

for file in "${required_source_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ Source file exists: $file"
    else
        echo "❌ Missing source file: $file"
        missing_source_files=$((missing_source_files + 1))
    fi
done

# Check build files
echo "\n===== BUILD FILES CHECK ====="
if [ -f "Build_Files/Makefile" ]; then
    echo "✅ Makefile exists: Build_Files/Makefile"
else
    echo "❌ Missing Makefile: Build_Files/Makefile"
fi

if [ -f "Build_Files/ecommerce" ]; then
    echo "✅ Executable exists: Build_Files/ecommerce"
else
    echo "❌ Missing executable: Build_Files/ecommerce (run 'make' in Build_Files directory)"
fi

# Check data files
required_data_files=(
    "Data_Files/accounts.txt"
    "Data_Files/products.txt"
    "Data_Files/history.txt"
    "Data_Files/invoice.txt"
    "Data_Files/product_audit.txt"
    "Data_Files/inventory_log.txt"
)

echo "\n===== DATA FILES CHECK ====="
missing_data_files=0

for file in "${required_data_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ Data file exists: $file"
    else
        echo "❌ Missing data file: $file (this may be created when the program runs)"
        missing_data_files=$((missing_data_files + 1))
    fi
done

# Check documentation files
required_doc_files=(
    "Documentation/OOP_DESIGN.md"
    "Documentation/STRUCTURE.md"
    "Documentation/class_diagram.md"
    "Documentation/component_diagram.md"
    "Documentation/sequence_diagram.md"
)

echo "\n===== DOCUMENTATION FILES CHECK ====="
missing_doc_files=0

for file in "${required_doc_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ Documentation file exists: $file"
    else
        echo "❌ Missing documentation file: $file"
        missing_doc_files=$((missing_doc_files + 1))
    fi
done

# Check for README
if [ -f "README.md" ]; then
    echo "\n✅ README.md exists"
else
    echo "\n❌ Missing README.md"
fi

# Summary
echo "\n===== SUMMARY ====="
total_missing=$((missing_directories + missing_source_files + missing_data_files + missing_doc_files))
if [ "$total_missing" -eq 0 ]; then
    echo "✅ Project structure is correctly set up. All required files are present."
else
    echo "❌ Project structure has issues: $total_missing missing files or directories."
    
    if [ "$missing_directories" -gt 0 ]; then
        echo "   - Missing directories: $missing_directories"
    fi
    
    if [ "$missing_source_files" -gt 0 ]; then
        echo "   - Missing source files: $missing_source_files"
    fi
    
    if [ "$missing_data_files" -gt 0 ]; then
        echo "   - Missing data files: $missing_data_files (some may be generated when the program runs)"
    fi
    
    if [ "$missing_doc_files" -gt 0 ]; then
        echo "   - Missing documentation files: $missing_doc_files"
    fi
fi