#include "../ln.h"
#include "../util.h"
#include <stdio.h>

double tick;

void cb(ln_t * _n, ln_t * _t, void * data)
{
    double duration = get_tick() - tick;
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


    if (argc == 2) {
        val = atoi(argv[1]);
    }
    printf("2^%d\n", val);



    ln_env_init();
    ln_init(&out);

    tick = get_tick();
    ln_pow(&out, 2, val, cb);
    duration = get_tick() - tick;

    time(&rawtime);

    fp = fopen("run/largest_pow_2.txt", "w+");
    fprintf(fp, "%d\t%ld\t%d\n", val, rawtime, (int)duration);
    fclose(fp);
    
    fp = fopen("run/largest_pow_2.raw", "w+");
    ln_write(&out, fp);
    fclose(fp);

    ln_free(&out);
    ln_env_free();
    return 0;
}