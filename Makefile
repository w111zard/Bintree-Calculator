CC = gcc
CGLAGS = -Wall -g
TARGET = bintree-calculator
PREFIX = /usr/local/bin
SRCS = main.c calculator.c binary_tree.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS) *.o

install:
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)

