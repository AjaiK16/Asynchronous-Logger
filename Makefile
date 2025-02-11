# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source Files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Logger.cpp
OBJS = $(SRCS:.cpp=.o)

# Output
TARGET = $(BIN_DIR)/logger.exe

# Build
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile Source Files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(OBJS) $(TARGET)
