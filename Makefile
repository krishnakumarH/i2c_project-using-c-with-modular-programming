CC=gcc

CFLAGS=-Wall -Iinclude

SRC=src/main.c \
    src/i2c_bus.c \
    src/i2c_master.c \
    src/i2c_slave.c

TARGET=i2c_sim

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
