#include "lib/ln.h"
#include "lib/util.h"
#include <stdio.h>
#include <time.h>
#include <sys/stat.h> /* mkdir */

double tick;
double last_tick = 0;

void cb(ln_t * _n, ln_t * _t, void * data)
{
    double cur = get_tick();
    if (cur - last_tick < 1) return;
    double duration = cur - tick;
    last_tick = cur;
    printf("\r %lu - ", _n->int_sz);
    ln_show(_t, "% ");
    printf("- %ds ", (int)duration);
    fflush(stdout);
}

int main(int argc, char ** argv)
{
    FILE * fp;
    ln_t out;
    int val = 2048;
    double duration;
    time_t rawtime;
    char filename[255];


    if (argc == 2) {
        val = atoi(argv[1]);
    }
    printf("2^%d\n", val);



    ln_env_init();
    ln_init(&out);

    tick = get_tick();
    last_tick = tick;
    ln_pow(&out, 2, val, cb);
    duration = get_tick() - tick;

    time(&rawtime);

    if (! dir_exists("run")) {
        if (mkdir("run", 0755) != 0) {
            fprintf(stderr, "Cannot create folder 'run'.\n");
            perror("mkdir");
        }
    }

    sprintf(filename, "run/pow2_%d.txt", val);
    fp = fopen(filename, "w+");
    if (fp) {
        fprintf(fp, "%d\t%ld\t%d\n", val, rawtime, (int)duration);
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
        fprintf(fp, "%d\t%ld\t%d\n", val, rawtime, (int)duration);
        fclose(fp);
    }

    ln_free(&out);
    ln_env_free();
    return 0;
}