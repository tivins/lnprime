#include "prime.h"
int main()
{
    ln_t prime;
    ln_env_init();
    ln_init(&prime);
    ln_append_str(&prime, "10", 0);
    next_prime(&prime, NULL, NULL);
    ln_show(&prime, "\n");
    ln_free(&prime);
    ln_env_free();
    return 0;
}