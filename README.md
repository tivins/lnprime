# lnprime

**lnprime** is a C program used to compute large prime numbers (e.g., greater than an integer).

The goals is not to get the record of the [Largest known prime number](https://en.wikipedia.org/wiki/Largest_known_prime_number), but, to learn how to deals with large numbers and to optimize a computation's process.

Simple usage:

```
#include "prime.h"
int main()
{
    ln_t prime;
    ln_init(&prime);
    ln_append_str(&prime, "123450", 0);
    next_prime(&prime, NULL, NULL);
    ln_show(&prime, "\n");
    return 0;
}
```
out:
`123457`

### Callback

To get a report of the processing's progress, you could provide a user-defined function, called during the process.

Callback signature: `void (*callback)(ln_t * number, void * userdata);`.

This callback should be given to the `next_prime()` function.
```
void my_callback(ln_t * number, void * userdata) {
    /* todo */
}
/* ... */
next_prime(&my_number, my_callback, NULL);
```

## Program structure

* ln.h/ln.c is the large number library.
* prime.h/prime.c use ln.h
* main.c is the program used to compute number using the command line interpreter.
* tests.c is the program to test the integrity of the calculations.
