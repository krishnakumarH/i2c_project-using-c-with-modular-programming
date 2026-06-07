#ifndef I2C_MASTER_H
#define I2C_MASTER_H

typedef struct
{
    int id;
} Master;

void master_init(Master *m, int id);

void master_send_address(int address);

void master_write_data(int data);

#endif
