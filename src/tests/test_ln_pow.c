#include "../ln.h"

int main()
{
    ln_t out;
    ln_env_init();
    ln_init(&out);
    ln_pow(&out, 2, 2048);
    ln_dec(&out);
    ln_show(&out, " (exp. result 4096) \n");
    ln_dump(&out);
    ln_free(&out);
    ln_env_free();
    return 0;
}