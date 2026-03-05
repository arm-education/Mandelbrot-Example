# Compiler
CXX := g++

# Directories
BUILD_DIR := build
TARGET_NAME := mandelbrot-parallel
TARGET := $(BUILD_DIR)/$(TARGET_NAME)

# Source files
SRCS := main.cpp mandelbrot.cpp bitmap.cpp

# Flags
STD := -std=c++11
DEBUG := -g
OPT ?= -O0

CXXFLAGS := $(STD) $(DEBUG) $(OPT)

# Default target
all: $(TARGET)

# Alias target (so you can type: make mandelbrot-parallel)
$(TARGET_NAME): $(TARGET)

# Build rule
$(TARGET): $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean $(TARGET_NAME)