#include "../include/i2c.h"

/*---------------------------------------
  FIFO Init
---------------------------------------*/

void fifo_init(FIFOSlave *fifo)
{
    fifo->address = FIFO_ADDR;

    fifo->front = 0;
    fifo->rear = 0;
    fifo->count = 0;

    sem_init(&fifo->empty,0,FIFO_SIZE);
    sem_init(&fifo->full,0,0);

    pthread_mutex_init(
            &fifo->lock,
            NULL);

    printf("FIFO Slave Initialized\n");
}

/*---------------------------------------
  Enqueue
---------------------------------------*/

void fifo_enqueue(
        FIFOSlave *fifo,
        int data)
{
    sem_wait(&fifo->empty);

    pthread_mutex_lock(
            &fifo->lock);

    fifo->buffer[fifo->rear] = data;

    fifo->rear =
        (fifo->rear + 1)
        % FIFO_SIZE;

    fifo->count++;

    printf("FIFO Enqueue %d\n",
            data);

    pthread_mutex_unlock(
            &fifo->lock);

    sem_post(&fifo->full);
}

/*---------------------------------------
  Dequeue
---------------------------------------*/

int fifo_dequeue(
        FIFOSlave *fifo)
{
    int data;

    sem_wait(&fifo->full);

    pthread_mutex_lock(
            &fifo->lock);

    data =
        fifo->buffer[
            fifo->front];

    fifo->front =
        (fifo->front + 1)
        % FIFO_SIZE;

    fifo->count--;

    pthread_mutex_unlock(
            &fifo->lock);

    sem_post(&fifo->empty);

    printf("FIFO Dequeue %d\n",
            data);

    return data;
}
