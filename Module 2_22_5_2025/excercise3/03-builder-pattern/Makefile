CC = gcc
CFLAGS = -Wall -Wextra -I.

# Directories
SRC_DIR = .
UART_DIR = $(SRC_DIR)/uart

# Source files
SRCS = main.c \
       uart/uart-builder.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = uart-builder

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)
