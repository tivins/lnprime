#include "prime.h"
int main() 
{
    ln_t prime;
    ln_init(&prime);
    ln_append_str(&prime, "1234567890", 0);
    next_prime(&prime, NULL, NULL);
    ln_show(&prime, "\n");
    return 0;
}