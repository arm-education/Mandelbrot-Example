CXX = g++
DEBUG ?= 0

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

CXX_FLAGS = --std=c++11
CPP_FLAGS = -I${INCLUDE_DIR}

BASELINE_SRCS = main.cpp bitmap.cpp mandelbrot_baseline.cpp
NEON_SRCS     = main.cpp bitmap.cpp mandelbrot_neon.cpp

BASELINE_OBJS = $(addprefix $(BUILD_DIR)/, $(BASELINE_SRCS:.cpp=.o))
NEON_OBJS     = $(addprefix $(BUILD_DIR)/, $(NEON_SRCS:.cpp=.o))

ifeq (${DEBUG}, 1)
	CXX_FLAGS += -g -O0
	BUILD_SUFFIX = _debug
else
	CXX_FLAGS += -O3
	BUILD_SUFFIX = 
endif

all: create baseline neon

baseline: $(BASELINE_OBJS)
	$(CXX) $(CXX_FLAGS) $^ -o $(BUILD_DIR)/mandelbrot_baseline$(BUILD_SUFFIX)

neon: $(NEON_OBJS)
	$(CXX) $(CXX_FLAGS) $^ -o $(BUILD_DIR)/mandelbrot_neon$(BUILD_SUFFIX)

# Compile .cpp → build/.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | create
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -c $< -o $@

create:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean create all