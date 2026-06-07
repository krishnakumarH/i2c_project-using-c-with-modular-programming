#ifndef CONFIG_H
#define CONFIG_H

/* Shared Memory */

#define SHM_NAME "/i2c_bus"

/* Number of Devices */

#define NUM_MASTERS 2
#define NUM_SLAVES 3

/* Slave Addresses */

#define MEMORY_ADDR 0x50
#define FIFO_ADDR   0x60
#define LIFO_ADDR   0x70

/* Buffer Sizes */

#define MEMORY_SIZE 32
#define FIFO_SIZE   10
#define LIFO_SIZE   10

/* Read Write */

#define READ_OP   1
#define WRITE_OP  0

#endif
