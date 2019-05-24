#include "ln.h"
#include "prime.h"

#include <time.h>     /* localtime */
#include <sys/time.h> /* gettimeofday */
#include <math.h>     /* round */
#include <stdio.h>    /* files */
#include <unistd.h>   /* gethostname */

#define FILE_HISTORY "run/history.txt"
#define FILE_LAST    "run/last.txt"
#define FILE_HOST    "run/host_%s.txt"

int main(int _argc, char** _argv);
void find_biggest_prime(const char * _init);
int read_last(char * biggest);
void save_in_file(ln_t * _n, long _dur);
double get_tick();
void display_time(int secs, FILE * fp);
void display(ln_t * _num, int diff, ln_t * _rem);

/**
 * TODO : use getopt().
 * TODO : provide small help (-h, --help)
 */
int main(int _argc, char** _argv)
{
    if (_argc == 2) {
        find_biggest_prime(_argv[1]);
    }
    else {
        char lastest[1024] = {'0', 0};
        int use_biggest = read_last(lastest);
        find_biggest_prime(use_biggest ? lastest : NULL);
    }
    return 0;
}

/**
 *
 */
typedef struct _user_data_t {
    double tick;
    int last;
} user_data_t;

/**
 *
 */
void callback(ln_t * _num, ln_t * _rem, void * _data) {
    user_data_t * udata = (user_data_t *) _data;
    int diff = (int)(get_tick() - udata->tick);
    if (udata->last != diff) {
        udata->last = diff;
        display(_num, diff, _rem);
    }
}

/**
 *
 */
void find_biggest_prime(const char * _init)
{
    ln_t prime;
    int diff;

    user_data_t udata;
    udata.tick = get_tick();
    udata.last = -1;

    ln_init(&prime);
    ln_append_str(&prime, _init ? _init : "0", 0);

    next_prime(&prime, callback, &udata);

    diff = (int)(get_tick() - udata.tick);
    display(&prime, diff, NULL);
    printf("\n");

    save_in_file(&prime, diff);
    ln_free(&prime);
}

/**
 *
 */
int read_last(char * biggest)
{
    int use_biggest = 0;
    FILE * fp = fopen(FILE_LAST, "r");
    if (!fp) return 0;
    if (fscanf(fp, "%s", biggest) >= 1) {
        use_biggest = 1;
    }
    fclose(fp);
    return use_biggest;
}
static int file_exists(const char * filename)
{
    FILE * fp = fopen(filename, "r");
    if (! fp) return 0;
    fclose(fp);
    return 1;
}

/**
 *
 */
void save_in_file(ln_t * _n, long _dur)
{
    char hostname[256] = {0};
    if (gethostname(hostname, 256) != 0)
    {
        perror("cannot get hostname");
        sprintf(hostname, "%s", "unknown");
    }

    char hostfile[512];
    sprintf(hostfile, FILE_HOST, hostname);
    // printf("hostfile='%s'\n", hostfile);
    if (! file_exists(hostfile))
    {
        char buff[1024];
        FILE * fph = fopen(hostfile, "w");

        FILE * fp_p;

        fp_p = fopen("/proc/cpuinfo", "r");
        fread(buff, 1, 1024, fp_p);
        fwrite(buff, 1, 1024, fph);
        fclose(fp_p);

        fp_p = fopen("/proc/meminfo", "r");
        fread(buff, 1, 1024, fp_p);
        fwrite(buff, 1, 1024, fph);
        fclose(fp_p);

        fclose(fph);
    }

    FILE * fp = fopen(FILE_HISTORY, "a+");
    if (fp == NULL) {
        perror("cannot save file " FILE_HISTORY);
        return;
    }

    char * num_str;
    time_t rawtime;

    time(&rawtime);
    num_str = ln_c_str(_n);

    fprintf(fp, "%ld\t%s\t%ld\t%s\n", rawtime, num_str, _dur, hostname);
    fclose(fp);

    fp = fopen(FILE_LAST, "w+");
    if (fp) {
        fprintf(fp, "%s\t%ld\t%ld\t%s", num_str, rawtime, _dur, hostname);
        fclose(fp);
    }
    free(num_str);
}

/**
 *
 */
double get_tick()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)(tv.tv_sec + tv.tv_usec * 0.000001);
}

/**
 *
 */
void display_time(int secs, FILE * fp) {
    int days, hrs, min;
    days = secs / (3600.0*24);
    secs -= days * (3600.0*24);
    hrs = secs / 3600.0;
    secs -= hrs*3600;
    min = secs / 60.0;
    secs -= min*60;
    fprintf(fp, "\r%d.%02d:%02d:%02d ", days, hrs, min, secs);
}

/**
 *
 */
void display(ln_t * _num, int diff, ln_t * _rem)
{
    display_time(diff, stdout);
    ln_show(_num, " ");
    if (_rem) ln_show(_rem, "% ");
    fflush(stdout);
}
