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
