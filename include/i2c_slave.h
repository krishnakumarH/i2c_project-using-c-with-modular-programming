#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "config.h"

typedef struct
{
    int address;
    int memory[MEMORY_SIZE];

} Slave;

void slave_init(Slave *s,int address);

int slave_ack(Slave *s,int address);

void slave_write(Slave *s,int location,int data);

int slave_read(Slave *s,int location);

#endif
