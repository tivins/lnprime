#include "prime.h"
#include <stdio.h>
#include <string.h>

int show_ln_ope(int _a, int _b, char ope) ;
void test_leak() ;
void test_ln() ;
int rnd(int min, int max) {
    return rand() % (max - min) + min ;
}

void test_leak() {
    ln_t n1, n2, n3 ;
    ln_init(&n1) ;
    ln_init(&n2) ;
    ln_init(&n3) ;
    ln_append(&n1, 2) ;
    ln_append(&n2, 6) ;
    ln_inc(&n2) ;
    ln_div(&n3, &n1, &n2, NULL) ;
    ln_free(&n1) ;
    ln_free(&n2) ;
    ln_free(&n3) ;
}


void test_ln() {
    ln_t n1, n2, n3 ;
    int nex ;

    srand(0); /* time(NULL)) ; */

    ln_init(&n1) ;
    ln_init(&n2) ;
    ln_init(&n3) ;

    // ln_append(&n1, 1) ;
    // ln_mul_int(&n2, &n1, 1);
    // ln_show(&n2, " 1x1\n") ;
    // ln_clear(&n1) ;
    // ln_clear(&n2) ;

    ln_append_str(&n1, "65321546", 0) ;
    ln_sqrt(&n2, &n1) ;
    ln_show(&n2, " = sqrt(65321546) , expected = 8082\n") ;
    ln_clear(&n2) ;

    // ==> √152 = 12,328828006
    // ==> √632 = 25,13961018
    // ==> √65321546 = 8082,174583613

    goto clear ;

    ln_clear(&n1) ;
    ln_append_str(&n1, "1524", 0) ;
    ln_sqrt(&n2, &n1) ;
    ln_show(&n2, " = sqrt(1524)\n") ;
    ln_clear(&n2) ;

    ln_clear(&n1) ;
    ln_append_str(&n1, "15244", 0) ;
    ln_sqrt(&n2, &n1) ;
    ln_show(&n2, " = sqrt(15244)\n") ;
    ln_clear(&n2) ;

    ln_clear(&n1) ;
    ln_append_str(&n1, "65435", 0) ;
    ln_sqrt(&n2, &n1) ;
    ln_show(&n2, " = sqrt(65435)\n") ;
    ln_clear(&n2) ;

    ln_show(&n1, "\n") ;

    ln_append(&n1, 2) ;
    ln_append(&n1, 3) ;
    ln_append(&n1, 4) ;
    ln_prepend(&n1, 8) ;
    ln_show(&n1, "\n") ;

    ln_dec(&n1) ; ln_show(&n1, " (dec)\n") ;
    ln_dec(&n1) ; ln_show(&n1, " (dec)\n") ;
    ln_dec(&n1) ; ln_show(&n1, " (dec)\n") ;
    ln_inc(&n1) ; ln_show(&n1, " (inc)\n") ;
    ln_inc(&n1) ; ln_show(&n1, " (inc)\n") ;
    ln_inc(&n1) ; ln_show(&n1, " (inc)\n") ;

    ln_negate(&n1) ;
    ln_show(&n1, "\n") ;

    ln_free(&n1) ;
    ln_append_str(&n1, "16546546543", 0) ;
    ln_show(&n1, "\n") ;

    show_ln_ope(9992,128,'+') ;
    show_ln_ope(99999,99999,'+') ;
    show_ln_ope(-123,-456,'+') ;
    show_ln_ope( 123,-456,'+') ;

    show_ln_ope(4,4,'*') ;
    show_ln_ope(3173,2,'*') ;
    show_ln_ope(2,3173,'*') ;
    show_ln_ope(3,3173,'*') ;
    show_ln_ope(3173,3,'*') ;

    show_ln_ope(3173,1,'/') ;
    show_ln_ope(3173,1,'%') ;

    for (nex = 0 ; nex < 100 ; nex++) {
        if (!show_ln_ope(rnd(-10000,10000),rnd(-10000,10000),'+'))
            goto clear ;
    }
    for (nex = 0 ; nex < 100 ; nex++) {
        if (!show_ln_ope(rnd(-10000,10000),rnd(-10000,10000),'-'))
            goto clear ;
    }
    for (nex = 0 ; nex < 100 ; nex++) {
        if (!show_ln_ope(rnd(-10000,10000),rnd(-10000,10000),'*'))
            goto clear ;
    }
    for (nex = 0 ; nex < 100 ; nex++) {
        if (!show_ln_ope(rnd(0,10000),rnd(0,10000),'/'))
            goto clear ;
    }
    for (nex = 0 ; nex < 100 ; nex++) {
        if (!show_ln_ope(rnd(0,10000),rnd(0,10000),'%'))
            goto clear ;
    }

clear:
    ln_free(&n1) ;
    ln_free(&n2) ;
    ln_free(&n3) ;
}


int show_ln_ope(int _a, int _b, char ope) {
    int exp = 0, success ;

    ln_t n1, n2, nr, n_res ;
    char * ns1, * ns2, * ns3, ns4[32] ;


    if (ope == '%' && _b == 0) _b = 1 ;
    if (ope == '/' && _b == 0) _b = 1 ;

    ln_init(&n1) ;
    ln_init(&n2) ;
    ln_init(&nr) ;
    ln_init(&n_res) ;

    ln_append_int(&n1, _a) ;
    ln_append_int(&n2, _b) ;

    switch (ope) {
        case '+':
            exp = _a + _b ;
            ln_add(&n_res, &n1, &n2) ;
            break ;
        case '-':
            exp = _a - _b ;
            ln_sub(&n_res, &n1, &n2) ;
            break ;
        case '/':
            exp = _a / _b ;
            ln_div(&n_res, &n1, &n2, NULL) ;
            break ;
        case '*':
            exp = _a * _b ;
            ln_mul(&n_res, &n1, &n2) ;
            break ;
        case '%':
            exp = _a % _b ;
            ln_mod(&n_res, &n1, &n2) ;
            break ;
    }


    ns1 = ln_c_str(&n1) ;
    ns2 = ln_c_str(&n2) ;
    ns3 = ln_c_str(&n_res) ;
    sprintf(ns4, "%d", exp) ;

    success = strcmp(ns4, ns3) == 0 ;
    printf("`%s` %c `%s` = `%s`", ns1, ope, ns2, ns3) ;
    if (!success) printf(" **FAIL** expected %d.", exp) ;
    else printf(" ok.") ;
    printf("\n") ;

    free(ns1) ;
    free(ns2) ;
    free(ns3) ;

    ln_free(&n1) ;
    ln_free(&n2) ;
    ln_free(&n_res) ;

    return success ;
}

static void test2_ln() {
    ln_t n1, n2;

    ln_init(&n2) ;
    ln_init(&n1) ;
    ln_append_str(&n1, "64", 0) ;

    ln_sqrt(&n2, &n1);


    ln_show(&n1, " V= ");
    ln_show(&n2, "\n");

    ln_free(&n1) ;
    ln_free(&n2) ;
}
int main() {
    test_ln();
    // test2_ln();
    return 0;
}