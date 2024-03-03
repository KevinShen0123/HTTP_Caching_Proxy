CXX = g++            # Compiler
CXXFLAGS = -Wall -std=c++11 -pthread # Compiler flags
TARGET = proxy        # Output executable

# List of source files
SRCS = Cache.cpp  proxy.cpp

# List of object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to avoid conflicts with files named "all" or "clean"
.PHONY: all clean
