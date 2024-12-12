# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror
LDFLAGS = -Llib

# Directories
BINDIR = bin
BUILDDIR = build
SRCDIR = src
INCDIR = include
LIBDIR = lib

# Libraries to link (for example, -lm for math library)
LIBS = -lm

# Source and object files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

# Executable name
EXEC = $(BINDIR)/voting_program.out

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

# Compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
