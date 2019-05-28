
#include <ln.h>
#include "lib/util.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h> /* mkdir() */
#include <unistd.h> /* gethostname() */

time_t last_tick;
time_t tick;

void cb(ln_t * _n, float _p, void * data)
{
    time(&tick);
    if (tick - last_tick < 1) return;
    long int duration = last_tick - tick;
    last_tick = tick;

    printf("\r %lu - %.2f%% - %lds", _n->int_sz, _p, duration);
    fflush(stdout);
}

int main(int argc, char ** argv)
{
    FILE * fp;
    ln_t out;
    int val = 2048;
    int duration;
    time_t rawtime;
    char filename[255];
    char hostname[256] = {0};


    /* ultra-basic version provider */
    if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
        printf("%s\n", LIBLN_VERSION);
        return 0;
    }

    /* gets the value from the program arguments */
    if (argc >= 2)
    {
        val = atoi(argv[1]);
    }

    printf("2^%d\n", val);

    ln_env_init();
    ln_init(&out);

    ln_reserve(&out, 909526);

    time(&last_tick);

    ln_pow(&out, 2, val, cb);

    time(&tick);
    duration = tick - last_tick;
    time(&rawtime);



    if (gethostname(hostname, 256) != 0)
    {
        perror("cannot get hostname");
        sprintf(hostname, "%s", "unknown");
    }


    if (! dir_exists("run")) {
        if (mkdir("run", 0755) != 0) {
            fprintf(stderr, "Cannot create folder 'run'.\n");
            perror("mkdir");
        }
    }

    sprintf(filename, "run/pow2_%d.txt", val);
    fp = fopen(filename, "w+");
    if (fp) {
        fprintf(fp, "%d\t%ld\t%d\t%s\n", val, rawtime, duration, hostname);
        fclose(fp);
    }

    sprintf(filename, "run/pow2_%d.raw", val);
    fp = fopen(filename, "w+");
    if (fp) {
        ln_write(&out, fp);
        fclose(fp);
    }

    sprintf(filename, "run/pow2_history.txt");
    fp = fopen(filename, "a");
    if (fp) {
        fprintf(fp, "%d\t%ld\t%d\t%s\n", val, rawtime, duration, hostname);
        fclose(fp);
    }

    ln_free(&out);
    ln_env_free();
    return 0;
}