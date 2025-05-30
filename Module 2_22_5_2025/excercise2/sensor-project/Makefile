CC = gcc
CFLAGS = -Wall -Wextra -I.

# Directories
SRC_DIR = .
TEMP_DIR = $(SRC_DIR)/temperature
HUMID_DIR = $(SRC_DIR)/humidity
LIGHT_DIR = $(SRC_DIR)/light
FACTORY_DIR = $(SRC_DIR)/sensor-factory

# Source files
SRCS = $(TEMP_DIR)/temperature-sensor.c \
       $(HUMID_DIR)/humidity-sensor.c \
       $(LIGHT_DIR)/light-sensor.c \
       $(FACTORY_DIR)/sensor-factory.c \
       $(SRC_DIR)/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = sensorProject

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)
