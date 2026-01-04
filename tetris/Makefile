# Projekt
TARGET := tetres
SRC_DIR := src
INC_DIR := include

# Compiler
CC := gcc

# OS Detekcia
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    SDL_CFLAGS := $(shell sdl2-config --cflags)
    SDL_LIBS   := $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer
endif
ifeq ($(UNAME_S),Darwin)
    SDL_CFLAGS := $(shell sdl2-config --cflags)
    SDL_LIBS   := $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer
endif
ifeq ($(OS),Windows_NT)
    SDL_CFLAGS :=
    SDL_LIBS   := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
endif

# Warningy
WARNINGS := -Wall -Wextra -Wpedantic
COMMON   := $(WARNINGS) -I$(INC_DIR)

# Debug flags – must be in both compile and link!
DEBUG_FLAGS      := -g -fsanitize=address
DEBUG_LINK_FLAGS := -fsanitize=address -static-libasan  # static-libasan only on link

# Release flags
RELEASE_FLAGS := -O2

# Zdroje
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:.c=.o)

# Default target
all: debug

# Debug build
debug: CFLAGS  := $(COMMON) $(DEBUG_FLAGS) $(SDL_CFLAGS)
debug: LDFLAGS := $(DEBUG_LINK_FLAGS) $(SDL_LIBS)
debug: $(TARGET)

# Release build
release: CFLAGS  := $(COMMON) $(RELEASE_FLAGS) $(SDL_CFLAGS)
release: LDFLAGS := $(SDL_LIBS)
release: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

rebuild: clean all

.PHONY: all debug release run clean rebuild