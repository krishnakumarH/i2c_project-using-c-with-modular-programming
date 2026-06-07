#include "../include/i2c.h"

/*----------------------------------
  Command Thread
----------------------------------*/

void *command_thread(void *arg)
{
    Master *master =
        (Master *)arg;

    printf(
        "Master %d Command Thread Started\n",
        master->id);

    return NULL;
}

/*----------------------------------
  Monitor Thread
----------------------------------*/

void *monitor_thread(void *arg)
{
    Master *master =
        (Master *)arg;

    printf(
        "Master %d Monitor Thread Started\n",
        master->id);

    return NULL;
}

/*----------------------------------
  Run Master
----------------------------------*/

void run_master(
        int id,
        I2C_Bus *bus)
{
    Master master;

    pthread_t cmd_thread;
    pthread_t mon_thread;

    master.id = id;

    pthread_create(
            &cmd_thread,
            NULL,
            command_thread,
            &master);

    pthread_create(
            &mon_thread,
            NULL,
            monitor_thread,
            &master);

    pthread_join(
            cmd_thread,
            NULL);

    pthread_join(
            mon_thread,
            NULL);

    pthread_mutex_lock(
            &bus->bus_lock);

    if(bus->bus_busy == 0)
    {
        bus->address =
            MEMORY_ADDR;

        bus->data =
            id * 100;

        bus->rw =
            WRITE_OP;

        bus->ack = 1;

        bus->bus_busy = 1;

        printf(
            "\nMaster %d Wrote Data %d\n",
            id,
            bus->data);
    }

    pthread_mutex_unlock(
            &bus->bus_lock);
}
