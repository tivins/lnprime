#include "util.h"
#include <sys/time.h> /* gettimeofday */
#include <stdlib.h> 

/**
 *
 */
double get_tick()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)(tv.tv_sec + tv.tv_usec * 0.000001);
}
