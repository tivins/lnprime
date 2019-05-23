#include "prime.h"


/**
 * Update _number until it reach the next prime number.
 * _number could be any number, including a prime number.
 */
void next_prime(ln_t * _number, next_prime_cb _cb, void * _data)
{
    // double tick, diff;
    int fail;//, last_sec = -1;
    ln_t div, mod , sqroot;

    ln_init(&div);
    ln_init(&mod);
    ln_init(&sqroot);
    // tick = get_tick();

    while (1)
    {
        fail = 0;

        ln_inc(_number);
        // ln_show(_number, " (testing)\n");

        ln_clear(&div);
        ln_append(&div, 2);

        ln_clear(&sqroot);
        ln_sqrt(&sqroot, _number);
        ln_inc(&sqroot);

        while (ln_cmp(&div, &sqroot) == ln_Lesser)
        {
            // diff = get_tick() - tick;
            // if ((int)diff != last_sec) {
            //     last_sec = (int)diff;
            //     display(_number, last_sec);
            if (_cb)
            {
        		_cb(_number, _data);
            }
            // }

            ln_clear(&mod);
            ln_mod(&mod, _number, &div);
            if (ln_is_zero(&mod))
            {
                fail = 1;
                break;
            }
            ln_inc(&div);
        }
        if (!fail) break;
    }

    ln_free(&div);
    ln_free(&mod);
}
