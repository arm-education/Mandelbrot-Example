# Compiler
CXX := g++

# Directories
BUILD_DIR := build
TARGET_NAME := mandelbrot-parallel
TARGET := $(BUILD_DIR)/$(TARGET_NAME)

NEON_NAME := mandelbrot-parallel-neon
NEON_TARGET := $(BUILD_DIR)/$(NEON_NAME)


# Source files
COMMON := main.cpp  bitmap.cpp
NEON_SOURCES := mandelbrot_neon.cpp
TARGET_SOURCES := mandelbrot.cpp

# Flags
STD := -std=c++11
DEBUG := -g
OPT ?= -O0

CXXFLAGS := $(STD) $(DEBUG) $(OPT) -I../include

NEON_FLAGS := $(CXXFLAGS) 

# Default target
all: $(TARGET) $(NEON_TARGET)

# Alias target (so you can type: make mandelbrot-parallel)
$(TARGET_NAME): $(TARGET)
$(NEON_NAME): $(NEON_TARGET)

# Build rule
$(TARGET): $(COMMON) $(TARGET_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build rule
$(NEON_TARGET): $(COMMON) $(NEON_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean $(TARGET_NAME)