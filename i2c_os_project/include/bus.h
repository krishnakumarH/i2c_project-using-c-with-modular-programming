#ifndef BUS_H
#define BUS_H

typedef struct
{
    int address;
    int data;
    int rw;
    int ack;
    int busy;
} I2C_Bus;

#endif
