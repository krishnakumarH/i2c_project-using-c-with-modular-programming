#include "../include/i2c.h"
#include <time.h>

void *logger_thread(void *arg)
{
    while(1)
    {
        time_t now;

        now = time(NULL);

        printf("\n[LOGGER] %s",
                ctime(&now));

        sleep(5);
    }

    return NULL;
}
