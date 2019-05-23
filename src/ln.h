#ifndef LARGE_NUMBERS_INC_
#define LARGE_NUMBERS_INC_

#include <stdlib.h>

typedef struct _ln_t {
    char * integer;
    size_t int_sz, int_cap;
    /* char * decimals;
    size_t dec_sz, dec_cap; */
    char   negative;
} ln_t;

enum { ln_Lesser = 1, ln_Equal = 2, ln_Greater = 4 };

void ln_init(ln_t * _n);
void ln_clear(ln_t * _n);
void ln_free(ln_t * _n);
void ln_copy(ln_t * _src, ln_t * _dst);
void ln_negate_copy(ln_t * _src, ln_t * _dst);
void ln_reserve(ln_t * _n, size_t _cap);
void ln_append(ln_t * _n, int _digit);
void ln_append_str(ln_t * _n, const char * _str, size_t _l);
void ln_append_int(ln_t * _n, int _val);
void ln_prepend(ln_t * _n, int _digit);
void ln_negate(ln_t * _n);
void ln_trim(ln_t * _n);
int  ln_is_zero(ln_t * _n);
int  ln_cmp(ln_t * _a, ln_t * b); /* ln_Lesser (a < b), ln_Equal (a = b), ln_Greater (a > b) */
char ln_at(ln_t * _n, size_t _i);
char ln_last_at(ln_t * _n, size_t _i);
void ln_set(ln_t * _n, size_t _i, int _digit);
char * ln_c_str(ln_t * _n);
void ln_inc(ln_t * _n);
void ln_dec(ln_t * _n);
void ln_add(ln_t * _out, ln_t * _a, ln_t * b);
void ln_sub(ln_t * _out, ln_t * _a, ln_t * b);
void ln_sub_int(ln_t * _out, ln_t * _a, int _b); /* _out = _a - _b */
void ln_mul_int(ln_t * _out, ln_t * _a, int _b);
void ln_mul_str(ln_t * _out, ln_t * _a, const char * _str, size_t _len);
void ln_mul(ln_t * _out, ln_t * _a, ln_t * b);
void ln_div(ln_t * _out, ln_t * _a, ln_t * b, ln_t * _rem);
void ln_mod(ln_t * _out, ln_t * _a, ln_t * b);
void ln_sqrt(ln_t * _out, ln_t * _n);
size_t ln_max_sz(ln_t * _a, ln_t * b);
void ln_show(ln_t * _n, const char * _sfx);
void ln_dump(ln_t * _n);
void ln_20ppx(ln_t * _out, ln_t * _p, ln_t * _x); // computes `20p + x`

#endif