#ifndef I2C_BUS_H
#define I2C_BUS_H

typedef struct
{
    int scl;
    int sda;
} I2CBus;

void bus_init(I2CBus *bus);

void start_condition(I2CBus *bus);

void stop_condition(I2CBus *bus);

#endif
