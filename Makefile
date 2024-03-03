CXX = g++            # Compiler
CXXFLAGS = -Wall -std=c++11  # Compiler flags
SRC_DIR = src         # Source code directory
BUILD_DIR = build     # Build directory
TARGET = proxy        # Output executable

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(BUILD_DIR) $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony target to avoid conflicts with files named "all" or "clean"
.PHONY: all clean
