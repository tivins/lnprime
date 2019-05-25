# lnprime

**lnprime** is a C program used to compute large prime numbers (e.g., greater than an integer).

The goal is not to get the record of the [largest known prime number](https://en.wikipedia.org/wiki/Largest_known_prime_number), but, to learn how to deal with [large numbers](https://en.wikipedia.org/wiki/Large_numbers) and to optimize a computation's process.

There are no dependency. Only standard headers are used.

### Simple usage:

```
#include "prime.h"
int main()
{
    ln_t prime;
    ln_env_init();
    ln_init(&prime);
    ln_append_str(&prime, "1234567890", 0);
    next_prime(&prime, NULL, NULL);
    ln_show(&prime, "\n");
    ln_free(&prime);
    ln_env_free();
    return 0;
}
```

outputs:

    1234567891

### Raise number into power

```
ln_t pow;
ln_init(&pow);
ln_pow(&pow, 2, 2048);
ln_show(&pow, "\n");
ln_free(&pow);
```

outputs:

    32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389437335543602135433229604645318478604952148193555853611059596230655

### Mersenne prime `2<sup>P</sup>-1`

```
ln_t mersp;
ln_init(&mersp);
ln_pow(&mersp, 2, 11213);
ln_dec(&mersp);
ln_show(&mersp, " (2^11213)-1");
ln_free(&mersp);
```

### Callback

To get a report of the processing's progress, you could provide a user-defined function, called during the process.

Callback signature: 

    void (*callback)(ln_t * number, ln_t * progress, void * userdata);

This callback should be given to the `next_prime()` function.

```
void my_callback(ln_t * number, ln_t * progress, void * userdata) {
    /* todo */
}
/* ... */
next_prime(&my_number, my_callback, NULL);
```

## Compile

```
git clone git@github.com:tivins/lnprime.git
cd lnprime
make
```

## Program structure

**Library**

* `ln.h`, `ln.c` is the "large number" library.
* `prime.h`, `prime.c` are an extension of `ln.h` for prime numbers.

**Executables sources:**

* `minimal.c` is the basic program used to compute number using the command line interpreter, without any interaction.
* `main.c` is the program used to compute number using the command line interpreter, with feedback from the process.
* `tests.c` is the program used to test the validity of some processes.

## Biggest primes

Actually, the largest known prime number is : [2^82,589,933^-1](https://www.mersenne.org/primes/?press=M82589933) (24,862,048 digits). 