#include "../include/i2c.h"

/*---------------------------------------
  LIFO Init
---------------------------------------*/

void lifo_init(LIFOSlave *lifo)
{
    lifo->address = LIFO_ADDR;

    lifo->top = -1;

    pthread_mutex_init(
            &lifo->lock,
            NULL);

    printf("LIFO Slave Initialized\n");
}

/*---------------------------------------
  Push
---------------------------------------*/

void lifo_push(
        LIFOSlave *lifo,
        int data)
{
    pthread_mutex_lock(
            &lifo->lock);

    if(lifo->top == LIFO_SIZE - 1)
    {
        printf("LIFO Full\n");

        pthread_mutex_unlock(
                &lifo->lock);

        return;
    }

    lifo->top++;

    lifo->stack[
        lifo->top] = data;

    printf("LIFO Push %d\n",
            data);

    pthread_mutex_unlock(
            &lifo->lock);
}

/*---------------------------------------
  Pop
---------------------------------------*/

int lifo_pop(
        LIFOSlave *lifo)
{
    int data;

    pthread_mutex_lock(
            &lifo->lock);

    if(lifo->top == -1)
    {
        printf("LIFO Empty\n");

        pthread_mutex_unlock(
                &lifo->lock);

        return -1;
    }

    data =
        lifo->stack[
            lifo->top];

    lifo->top--;

    pthread_mutex_unlock(
            &lifo->lock);

    printf("LIFO Pop %d\n",
            data);

    return data;
}
