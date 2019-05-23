#include "prime.h"

/**
 * Updates `_number` until it reach the next prime number.
 * `_number` could be any number, including a prime number.
 *
 * @param _number
 *      The previous number. The prime number found will be
 *      greater than it.
 *
 * @param _cb
 *      The callback called at the begin of the test for each numbers
 *      until the next prime was found.
 * 
 * @param _data
 *      User data pointer given to the callback. It can be a NULL value.
 */
void next_prime(ln_t * _number, next_prime_cb _cb, void * _data)
{
    int fail;
    ln_t div; /* a divisor */
    ln_t mod; /* the remainder of the division */
    ln_t sqroot; /* the sqrt of the number (optimization) */

    /* Let start to init our numbers */
    ln_init(&div);
    ln_init(&mod);
    ln_init(&sqroot);

    /* Will we didn't reach our goal... */
    while (1)
    {
        fail = 0;

        /*
         * We need to test the next number than the given (or the previous).
         */
        ln_inc(_number);

        /*
         * Let start with 2 as divisor. 
         */
        ln_clear(&div);
        ln_append(&div, 2);

        /* 
         * Optimization :
         * A is the number to test for primality.  
         * It's not required to test all numbers until A-1,
         * it can be tested only until the square root of A.
         */
        ln_clear(&sqroot);
        ln_sqrt(&sqroot, _number);
        ln_inc(&sqroot);

        /*
         * While div is lower than the square root of A,
         * we will test for primality.
         */
        while (ln_cmp(&div, &sqroot) == ln_Lesser)
        {
            /* 
             * Call the user defined function, if defined.
             */
            if (_cb)
            {
        		_cb(_number, _data);
            }

            /*
             * Computes the modulo of _number with div.
             */
            ln_clear(&mod);
            ln_mod(&mod, _number, &div);
            if (ln_is_zero(&mod))
            {
                /* This division have no remainder. So,
                 * this number is not a prime number. 
                 * We could stop the tests for this number,
                 * it will be incremented in the next loop.
                 */
                fail = 1;
                break;
            }
            /*
             * The division have no remained. we could
             * continue the tests, with the next divisor. 
             */
            ln_inc(&div);
        }
        /*
         * The process tells that the number is a prime number.
         * We could stop the process.
         */
        if (!fail) break;
    }

    /*
     * Clean memory.
     */
    ln_free(&div);
    ln_free(&mod);
}
