# ==============================================================================
# Makefile for Module 01: Arrays & Strings (Safe Array Copy)
# Designed to build and execute safety-critical boundary test suites.
# ==============================================================================

CC = gcc
# Added -I. to explicitly look in the current folder for safe_array.h
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g -I.

# Target Executable
TARGET = test_suite

# Source and Object Files
SRCS = safe_array.c test_safe_array.c
OBJS = $(SRCS:.c=.o)

# Default Rule: Build and Run Tests
all: $(TARGET)
	@echo "----------------------------------------"
	@echo "Running Safety-Critical Unit Test Suite:"
	@echo "----------------------------------------"
	./$(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C Files to Object Files
%.o: %.c safe_array.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
