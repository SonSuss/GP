# Makefile for a C++ program named 'main'

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I.

# Linker flags
LDFLAGS = -L src/lib

# Libraries to link against
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Source file
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = Tiny_Football

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Rule to build object files from source files
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)


