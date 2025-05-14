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
