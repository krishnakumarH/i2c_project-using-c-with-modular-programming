#ifndef I2C_H
#define I2C_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <semaphore.h>

#include "config.h"

/* -----------------------------
   Shared I2C Bus Structure
   ----------------------------- */

typedef struct
{
    int address;
    int data;

    int rw;

    int ack;

    int bus_busy;

    pthread_mutex_t bus_lock;

} I2C_Bus;

/* -----------------------------
   Memory Slave
   ----------------------------- */

typedef struct
{
    int address;

    int memory[MEMORY_SIZE];

} MemorySlave;

/* -----------------------------
   FIFO Slave
   ----------------------------- */

typedef struct
{
    int address;

    int buffer[FIFO_SIZE];

    int front;
    int rear;
    int count;

    sem_t empty;
    sem_t full;

    pthread_mutex_t lock;

} FIFOSlave;

/* -----------------------------
   LIFO Slave
   ----------------------------- */

typedef struct
{
    int address;

    int stack[LIFO_SIZE];

    int top;

    pthread_mutex_t lock;

} LIFOSlave;

/* -----------------------------
   Master
   ----------------------------- */

typedef struct
{
    int id;

} Master;

/* -----------------------------
   Function Prototypes
   ----------------------------- */

/* IPC */

I2C_Bus *create_shared_bus(void);

void destroy_shared_bus(I2C_Bus *bus);

/* Master */

void *command_thread(void *arg);

void *monitor_thread(void *arg);

void run_master(int id,I2C_Bus *bus);

/* Memory Slave */

void memory_init(MemorySlave *mem);

void memory_write(
        MemorySlave *mem,
        int location,
        int data);

int memory_read(
        MemorySlave *mem,
        int location);

/* FIFO Slave */

void fifo_init(FIFOSlave *fifo);

void fifo_enqueue(
        FIFOSlave *fifo,
        int data);

int fifo_dequeue(
        FIFOSlave *fifo);

/* LIFO Slave */

void lifo_init(LIFOSlave *lifo);

void lifo_push(
        LIFOSlave *lifo,
        int data);

int lifo_pop(
        LIFOSlave *lifo);

/* Logger */

void *logger_thread(void *arg);

#endif
