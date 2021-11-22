#ifndef __BIGINT__
#define __BIGINT__

typedef struct bigint
{
    unsigned char *d;
    unsigned int bufsize;
    unsigned int size;
    unsigned char sign;
} bigint;

bigint bigint_init(int, char);
void bigint_init_val(bigint *, char, unsigned long);
void bigint_setdigit(bigint *, int, unsigned char);
void bigint_free(bigint *);
void bigint_print(bigint *);
bigint bigint_sum(bigint *, bigint *);
bigint bigint_sub(bigint *, bigint *);

bigint bigint_mul(bigint *, bigint *);

char bigint_compare(bigint *, bigint *);
void bigint_copy_abs(bigint *, bigint *, unsigned int);
void mult_digit(const bigint *, bigint *, char);
void bigint_mult(const bigint *, const bigint *, bigint *);
void bigint_copy(const bigint *, bigint *);
void fact(unsigned int, bigint *);
#endif