# Set default options
CC = clang++

CFLAGS = -g -Wall -lSDL2 -lSDL2main -lGLEW -lGL

TARGET = Game
SRCDIR = src/
BUILDDIR = build/

all: $(TARGET)

$(TARGET): $(SRCDIR)main.cpp
	$(CC) $(CFLAGS) -o  $(BUILDDIR)$(TARGET) $(SRCDIR)main.cpp

