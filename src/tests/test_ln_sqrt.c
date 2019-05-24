#include "../ln.h"

int main()
{
    ln_t num1, out;
    ln_init(&out);
    ln_init(&num1);
    ln_append_int(&num1, 123259);
    ln_sqrt(&out, &num1);
    ln_show(&out, " (result) \n");
    ln_dump(&out);
    ln_free(&num1);
    ln_free(&out);
    return 0;
}