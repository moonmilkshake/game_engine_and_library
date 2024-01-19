SRC_DIR = src
OBJ_NAME = play
BUILD_DIR = build/debug

# Windows Compiler
CC = g++

# Compile flags
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g

# .cpp Files in folder SRC_DIR
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Include paths
INCLUDE_PATHS = -Iinclude -IC:/msys64/ucrt64/include

# Library paths
LIBRARY_PATHS = -Llib -LC:/msys64/ucrt64/lib

# SDL2 Linking flags
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)
