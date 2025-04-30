# File: Makefile

# Directories
SRC_DIR := src
OBJ_DIR := build/bin
BIN_DIR := build

# Files
TARGET := $(BIN_DIR)/Files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Compiler
CXX := g++
CXXFLAGS := -Wall -std=c++17 -Iinclude

# Default rule
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if needed
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean