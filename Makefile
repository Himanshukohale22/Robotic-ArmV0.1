# Compiler settings
CC      = gcc
CXX     = g++
CFLAGS  = -Wall -Wextra -O2
CXXFLAGS= -Wall -Wextra -O2

# Directories
SRC_DIR = src
BUILD_DIR = build

# Programs to build
C_PROGS   = inverse-kinematics InverseKinemarics SquareMapping
# CXX_PROGS = inverse-kinematics InverseKinemarics SquareMapping  # for cpp

# Source files
C_SRCS   = $(SRC_DIR)/inverse-kinematics.c \
           $(SRC_DIR)/InverseKinemarics.c \
           $(SRC_DIR)/SquareMapping.c

# CXX_SRCS = $(SRC_DIR)/inverse-kinematics.cpp  # for cpp 

# Default target
all: $(C_PROGS)   # $(CXX_PROGS)

# Build rules for C executables

# $(CC) $(C_SRCS) $(CFLAGS) -o $(BUILD_DIR)/$@ $< -lm

inverse-kinematics : $(SRC_DIR)/inverse-kinematics.c
	$(CC) $(C_SRCS)   -o $(BUILD_DIR)/$@ $< -lm

InverseKinemarics : $(SRC_DIR)/InverseKinemarics.c
	$(CC) $(C_SRCS) -o $(BUILD_DIR)/$@ $< -lm

SquareMapping: $(SRC_DIR)/SquareMapping.c
	$(CC) $(C_SRCS)  -o $(BUILD_DIR)/$@ $< -lm

# Build rules for C++ executables
# inverse-kinematics: $(SRC_DIR)/inverse-kinematics.cpp
# 	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $< -lm

# Clean rule
clean:
	rm -f $(BUILD_DIR)/*

# Run example (default run inversekinematics)
run: $(BUILD_DIR)/inversekinematics
	./$(BUILD_DIR)/inversekinematics
