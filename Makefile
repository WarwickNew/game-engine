# Set default options
CC = clang++

CFLAGS = -g -Wall

TARGET = Game
SRCDIR = src/
BUILDDIR = build/

all: $(TARGET)

$(TARGET): $(SRCDIR)main.cpp
	$(CC) $(CFLAGS) -o  $(BUILDDIR)$(TARGET) $(SRCDIR)main.cpp

