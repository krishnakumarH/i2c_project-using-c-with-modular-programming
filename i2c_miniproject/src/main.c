#include <stdio.h>

#include "../include/config.h"
#include "../include/i2c_bus.h"
#include "../include/i2c_master.h"
#include "../include/i2c_slave.h"

int main()
{
    I2CBus bus;

    Master master;

    Slave slave1;
    Slave slave2;

    bus_init(&bus);

    master_init(&master,1);

    slave_init(&slave1,SLAVE1_ADDR);
    slave_init(&slave2,SLAVE2_ADDR);

    start_condition(&bus);

    master_send_address(SLAVE1_ADDR);

    if(slave_ack(&slave1,SLAVE1_ADDR))
    {
        slave_write(&slave1,0,100);

        printf("Read Data = %d\n",
                slave_read(&slave1,0));
    }

    stop_condition(&bus);

    return 0;
}
