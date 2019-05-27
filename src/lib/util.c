#include "util.h"
#include <sys/time.h> /* gettimeofday */
#include <stdlib.h>
#include <dirent.h> /* opendir */
#include <errno.h>

/**
 *
 */
double get_tick()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)(tv.tv_sec + tv.tv_usec * 0.000001);
}

int dir_exists(const char * path) {
    DIR* dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        /* Directory does not exist. */
    } else {
        /* opendir() failed for some other reason. */
    }
    return 0;
}