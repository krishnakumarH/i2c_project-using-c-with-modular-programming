#include <stdio.h>
#include "../include/i2c_bus.h"

void bus_init(I2CBus *bus)
{
    bus->scl = 1;
    bus->sda = 1;

    printf("Bus Initialized\n");
}

void start_condition(I2CBus *bus)
{
    bus->sda = 0;

    printf("\nSTART CONDITION\n");
}

void stop_condition(I2CBus *bus)
{
    bus->sda = 1;

    printf("STOP CONDITION\n");
}
