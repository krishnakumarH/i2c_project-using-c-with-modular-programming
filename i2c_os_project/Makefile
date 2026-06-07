CC=gcc

CFLAGS=-Wall -pthread -Iinclude

SRC=src/main.c \
    src/ipc.c \
    src/master.c \
    src/memory_slave.c \
    src/fifo_slave.c \
    src/lifo_slave.c \
    src/logger.c

TARGET=i2c_os_sim

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
