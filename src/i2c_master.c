#include <stdio.h>
#include "../include/i2c_master.h"

void master_init(Master *m,int id)
{
    m->id = id;
}

void master_send_address(int address)
{
    printf("Master Sending Address : 0x%X\n",address);
}
