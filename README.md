# lnprime

A simple program in C to compute large prime number (e.g., greater than an integer).

The goals is not to get the record of the (Largest known prime number)[https://en.wikipedia.org/wiki/Largest_known_prime_number], but, to learn how to deals with large number and to optimize a computation's process.

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

To get a report of the processing's progress, you could define a user function, called during the process.

Callback signature: `void (*callback)(ln_t
* number, void * userdata);`.

This callback should be given to the `next_prime()` function.
```
void my_callback(ln_t * number, void * userdata) {
    /* todo */
}
/* ... */
next_prime(&my_number, my_callback, NULL);
```

### Optimisations

* *Done* La liste des nombres n'a pas besoin d'aller jusqu'à A-1, mais seulement jusqu'à la racine carré de A.
  En effet, si `A` n'est pas premier alors il se compose d'un produit de deux nombres, soit `A = N * M`, avec nécessairement une relation d'ordre, disons `N ≤ M`. Or, si `N > A½` alors `M > A½`, par conséquent `N * M > A`, ce qui est absurde puisqu'on a `N * M = A`.
  [Source](http://fordom.free.fr/tuto/NP/TUTONP.htm)
* *Done* [Square root, Digit-by-digit calculation](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation)



### SQRT

Decimal (base 10)

Write the original number in decimal form. The numbers are written similar to the long division algorithm, and, as in long division, the root will be written on the line above. Now separate the digits into pairs, starting from the decimal point and going both left and right. The decimal point of the root will be above the decimal point of the square. One digit of the root will appear above each pair of digits of the square.

Beginning with the left-most pair of digits, do the following procedure for each pair:

* Starting on the left, bring down the most significant (leftmost) pair of digits not yet used (if all the digits have been used, write "00") and write them to the right of the remainder from the previous step (on the first step, there will be no remainder). In other words, multiply the remainder by 100 and add the two digits. This will be the current value c.
* Find p, y and x, as follows:
    * Let p be the part of the root found so far, ignoring any decimal point. (For the first step, p = 0.)
    * Determine the greatest digit x such that x ( 20 p + x ) ≤ c {\displaystyle x(20p+x)\leq c} x(20p+x)\leq c. We will use a new variable y = x(20p + x).
        * Note: 20p + x is simply twice p, with the digit x appended to the right).
        * Note: x can be found by guessing what c/(20·p) is and doing a trial calculation of y, then adjusting x upward or downward as necessary.
    * Place the digit x {\displaystyle x} x as the next digit of the root, i.e., above the two digits of the square you just brought down. Thus the next p will be the old p times 10 plus x.
* Subtract y from c to form a new remainder.
* If the remainder is zero and there are no more digits to bring down, then the algorithm has terminated. Otherwise go back to step 1 for another iteration.

```
          1  2. 3  4
       /
     \/  01 52.27 56

         01                   1*1 <= 1 < 2*2                 x = 1
         01                     y = x*x = 1*1 = 1
         00 52                22*2 <= 52 < 23*3              x = 2
         00 44                  y = (20+x)*x = 22*2 = 44
            08 27             243*3 <= 827 < 244*4           x = 3
            07 29               y = (240+x)*x = 243*3 = 729
               98 56          2464*4 <= 9856 < 2465*5        x = 4
               98 56            y = (2460+x)*x = 2464*4 = 9856
               00 00          Algorithm terminates: Answer is 12.34
```

Find the square root of 2.

```
          1. 4  1  4  2
       /
     \/  02.00 00 00 00

         02                  1*1 <= 2 < 2*2                 x = 1
         01                    y = x*x = 1*1 = 1
         01 00               24*4 <= 100 < 25*5             x = 4
         00 96                 y = (20+x)*x = 24*4 = 96
            04 00            281*1 <= 400 < 282*2           x = 1
            02 81              y = (280+x)*x = 281*1 = 281
            01 19 00         2824*4 <= 11900 < 2825*5       x = 4
            01 12 96           y = (2820+x)*x = 2824*4 = 11296
               06 04 00      28282*2 <= 60400 < 28283*3     x = 2
                             The desired precision is achieved:
                             The square root of 2 is about 1.4142

```