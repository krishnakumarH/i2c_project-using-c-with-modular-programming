#include "../include/i2c.h"

/* Global Devices */

MemorySlave memory_slave;
FIFOSlave fifo_slave;
LIFOSlave lifo_slave;

int main()
{
    I2C_Bus *bus;

    pthread_t logger;

    pid_t master1;
    pid_t master2;

    pid_t mem_slave;
    pid_t fifo_slave_pid;
    pid_t lifo_slave_pid;

    printf("\n===== I2C OS Simulator =====\n");

    /* Create Shared Bus */

    bus = create_shared_bus();

    /* Initialize Slaves */

    memory_init(&memory_slave);

    fifo_init(&fifo_slave);

    lifo_init(&lifo_slave);

    /* Logger Thread */

    pthread_create(
            &logger,
            NULL,
            logger_thread,
            NULL);

    /*-------------------------
      Master 1 Process
    -------------------------*/

    master1 = fork();

    if(master1 == 0)
    {
        printf("\nMaster1 Process PID=%d\n",
                getpid());

        run_master(1,bus);

        exit(0);
    }

    /*-------------------------
      Master 2 Process
    -------------------------*/

    master2 = fork();

    if(master2 == 0)
    {
        printf("\nMaster2 Process PID=%d\n",
                getpid());

        run_master(2,bus);

        exit(0);
    }

    /*-------------------------
      Memory Slave Process
    -------------------------*/

    mem_slave = fork();

    if(mem_slave == 0)
    {
        printf("\nMemory Slave PID=%d\n",
                getpid());

        memory_write(
                &memory_slave,
                0,
                123);

        printf(
            "Memory Read = %d\n",
            memory_read(
                &memory_slave,
                0));

        exit(0);
    }

    /*-------------------------
      FIFO Slave Process
    -------------------------*/

    fifo_slave_pid = fork();

    if(fifo_slave_pid == 0)
    {
        printf("\nFIFO Slave PID=%d\n",
                getpid());

        fifo_enqueue(
                &fifo_slave,
                10);

        fifo_enqueue(
                &fifo_slave,
                20);

        fifo_dequeue(
                &fifo_slave);

        exit(0);
    }

    /*-------------------------
      LIFO Slave Process
    -------------------------*/

    lifo_slave_pid = fork();

    if(lifo_slave_pid == 0)
    {
        printf("\nLIFO Slave PID=%d\n",
                getpid());

        lifo_push(
                &lifo_slave,
                100);

        lifo_push(
                &lifo_slave,
                200);

        lifo_pop(
                &lifo_slave);

        exit(0);
    }

    /* Wait for Children */

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("\nBus Status\n");

    printf("Address : 0x%X\n",
            bus->address);

    printf("Data    : %d\n",
            bus->data);

    printf("ACK     : %d\n",
            bus->ack);

    printf("Busy    : %d\n",
            bus->bus_busy);

    /* Cleanup */

    pthread_cancel(logger);

    pthread_join(
            logger,
            NULL);

    destroy_shared_bus(bus);

    printf(
        "\nSimulation Completed\n");

    return 0;
}
