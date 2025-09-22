# Makefile for Conway's Game of Life
# Compile with UTF-8 support for Korean text

CC = g++
CFLAGS = -Wall -Wextra -std=c++98 -O2
TARGET = game_of_life
SOURCE = source.cpp

# Default target
all: $(TARGET)

# Build the game
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Clean build files
clean:
	rm -f $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	@echo "No additional dependencies required for this game"

.PHONY: all clean run install-deps