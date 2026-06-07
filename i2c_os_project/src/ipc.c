#include "../include/i2c.h"

/*---------------------------------------
  Create Shared Memory Bus
---------------------------------------*/

I2C_Bus *create_shared_bus(void)
{
    int fd;

    fd = shm_open(
            SHM_NAME,
            O_CREAT | O_RDWR,
            0666);

    if(fd < 0)
    {
        perror("shm_open");
        exit(1);
    }

    if(ftruncate(fd,sizeof(I2C_Bus)) < 0)
    {
        perror("ftruncate");
        exit(1);
    }

    I2C_Bus *bus =
        mmap(NULL,
             sizeof(I2C_Bus),
             PROT_READ | PROT_WRITE,
             MAP_SHARED,
             fd,
             0);

    if(bus == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    bus->address = 0;
    bus->data = 0;
    bus->rw = 0;
    bus->ack = 0;
    bus->bus_busy = 0;

    /* Process Shared Mutex */

    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);

    pthread_mutexattr_setpshared(
            &attr,
            PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(
            &bus->bus_lock,
            &attr);

    return bus;
}

/*---------------------------------------
  Destroy Shared Memory Bus
---------------------------------------*/

void destroy_shared_bus(I2C_Bus *bus)
{
    pthread_mutex_destroy(
            &bus->bus_lock);

    munmap(
            bus,
            sizeof(I2C_Bus));

    shm_unlink(SHM_NAME);
}
