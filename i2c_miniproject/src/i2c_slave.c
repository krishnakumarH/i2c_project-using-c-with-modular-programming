#include <stdio.h>
#include "../include/i2c_slave.h"

void slave_init(Slave *s,int address)
{
    int i;

    s->address = address;

    for(i=0;i<MEMORY_SIZE;i++)
    {
        s->memory[i] = 0;
    }
}

int slave_ack(Slave *s,int address)
{
    if(s->address == address)
    {
        printf("ACK Received\n");
        return 1;
    }

    printf("NACK Received\n");
    return 0;
}

void slave_write(Slave *s,int location,int data)
{
    if(location >= MEMORY_SIZE)
    {
        printf("Invalid Memory Location\n");
        return;
    }

    s->memory[location] = data;

    printf("Written %d at Location %d\n",
            data,
            location);
}

int slave_read(Slave *s,int location)
{
    if(location >= MEMORY_SIZE)
    {
        printf("Invalid Memory Location\n");
        return -1;
    }

    return s->memory[location];
}
