# Compiler and flags
CC = gcc  # C compiler
CXX = g++  # C++ compiler
CFLAGS = -Iinclude -Wall -Wextra -Werror  # C flags
CXXFLAGS = -Iinclude -Wall -Wextra -Werror -std=c++17  # C++ flags

# Qt flags
#QT_DIR = /lib/Qt
#QT_INCLUDE_DIR = $(QT_DIR)/include
#QT_LIB_DIR = $(QT_DIR)/lib
#QT_LIBS = -lQt5Core -lQt5Gui -lQt5Widgets

# Directories
BINDIR = bin
BUILDDIR = build
SRCDIR = src
INCDIR = include
LIBDIR = lib

# Libraries to link (Qt libraries + other libraries)
#LIBS = -lm  # Example: link with math library, add more libraries here as needed
#LIBS += $(QT_LIBS)

# Source and object files
C_SRC = $(wildcard $(SRCDIR)/*.c)  # C source files
CXX_SRC = $(wildcard $(SRCDIR)/*.cpp)  # C++ source files
C_OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(C_SRC))  # C object files
CXX_OBJ = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(CXX_SRC))  # C++ object files

# Executable name
EXEC = $(BINDIR)/voting_program.out

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(C_OBJ) $(CXX_OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(C_OBJ) $(CXX_OBJ) -o $@ $(LDFLAGS) $(LIBS)

# Compile C source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
