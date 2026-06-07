#include "../include/i2c.h"

/*---------------------------------------
  Initialize Memory Slave
---------------------------------------*/

void memory_init(MemorySlave *mem)
{
    int i;

    mem->address = MEMORY_ADDR;

    for(i = 0; i < MEMORY_SIZE; i++)
    {
        mem->memory[i] = 0;
    }

    printf("Memory Slave Initialized\n");
}

/*---------------------------------------
  Write Memory
---------------------------------------*/

void memory_write(
        MemorySlave *mem,
        int location,
        int data)
{
    if(location < 0 || location >= MEMORY_SIZE)
    {
        printf("Memory Write Error\n");
        return;
    }

    mem->memory[location] = data;

    printf("Memory[%d] = %d\n",
            location,
            data);
}

/*---------------------------------------
  Read Memory
---------------------------------------*/

int memory_read(
        MemorySlave *mem,
        int location)
{
    if(location < 0 || location >= MEMORY_SIZE)
    {
        printf("Memory Read Error\n");
        return -1;
    }

    return mem->memory[location];
}
