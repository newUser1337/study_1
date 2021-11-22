#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "include/bigint.h"
bigint __bigint_sum_abs(bigint *, bigint *);
bigint __bigint_sub_abs(bigint *, bigint *);
char __bigint_compare_abs(bigint *, bigint *);
void __bigint_mul_digit_abs(bigint *, char);

#define max(x, y) (((x) >= (y)) ? (x) : (y))
#define min(x, y) (((x) <= (y)) ? (x) : (y))

bigint bigint_init(int bufsize, char sign)
{
    bigint b;
    b.d = (char *)calloc(bufsize, sizeof(char));
    b.bufsize = bufsize;
    b.sign = sign;
    b.size = 0;

    // printf("---ctor---\n");

    return b;
}

void bigint_init_val(bigint *a, char sign, unsigned long val)
{
    int i = 0;
    a->sign = sign;
    a->size=0;

    unsigned long reminder = val;
    do
    {
        assert(a->bufsize >= i);

        bigint_setdigit(a, i, reminder % 10);
        reminder = reminder / 10;
        i++;
    } while (reminder);
}

void bigint_setdigit(bigint *a, int pos, unsigned char c)
{
    a->d[pos] = c;
    if (pos + 1 > a->size && c != 0)
        a->size = pos + 1;
}

void bigint_free(bigint *b)
{
    free(b->d);
    b = NULL;

    // printf("---destruct---\n");
}

void bigint_print(bigint *b)
{
    printf("{%u}[%u] %c", b->size, b->bufsize, b->sign ? '-' : 0);

    int i = b->bufsize - 1;
    while (!b->d[i])
        i--;

    for (; i >= 0; i--)
    {
        printf("%c", b->d[i] + 48);
    }

    if (!b->size)
        printf("0");

    printf("\n");
}

bigint bigint_sum(bigint *a, bigint *b)
{
    if (a->sign == 0 && b->sign == 0)
        return __bigint_sum_abs(a, b);

    if (a->sign && b->sign)
    {
        bigint res = __bigint_sum_abs(a, b);
        res.sign = 1;
        return res;
    }

    if (__bigint_compare_abs(a, b) > 0)
    {
        bigint res = __bigint_sub_abs(a, b);
        if (a->sign)
            res.sign = 1;
        return res;
    }
    else if (__bigint_compare_abs(a, b) < 0)
    {
        bigint res = __bigint_sub_abs(b, a);
        if (b->sign)
            res.sign = 1;
        return res;
    }

    return bigint_init(0, 0);
}

bigint bigint_sub(bigint *a, bigint *b)
{
    if (a->sign != b->sign)
    {
        bigint res = __bigint_sum_abs(a, b);
        res.sign = a->sign;
        return res;
    }

    if (__bigint_compare_abs(a, b) > 0)
    {
        bigint res = __bigint_sub_abs(a, b);
        res.sign = a->sign;
        return res;
    }
    else if (__bigint_compare_abs(a, b) < 0)
    {
        bigint res = __bigint_sub_abs(b, a);
        if (!b->sign)
            res.sign = 1;
        return res;
    }

    return bigint_init(0, 0);
}

bigint __bigint_sum_abs(bigint *a, bigint *b)
{
    int size = (b->size > a->size) ? b->size : a->size;

    bigint res = bigint_init(size + 1, 0);

    char ac, bc, cd;
    for (int i = 0; i < size; i++)
    {
        ac = (i < a->size) ? a->d[i] : 0;
        bc = (i < b->size) ? b->d[i] : 0;

        cd = res.d[i + 1] + (res.d[i] + ac + bc) / 10;
        if (cd)
            bigint_setdigit(&res, i + 1, cd);
        bigint_setdigit(&res, i, (res.d[i] + ac + bc) % 10);
    }

    return res;
}

bigint __bigint_sub_abs(bigint *a, bigint *b)
{
    int size = (b->size > a->size) ? b->size : a->size;

    bigint res = bigint_init(size, 0);

    char ac, bc, bd = 0;
    for (int i = 0; i < size; i++)
    {
        ac = (i < a->size) ? a->d[i] : 0;
        bc = (i < b->size) ? b->d[i] : 0;

        if (ac < bc + bd)
        {
            bigint_setdigit(&res, i, 10 + ac - bc - bd);
            bd = 1;
        }
        else
        {
            bigint_setdigit(&res, i, ac - bc - bd);
            bd = 0;
        }
    }

    return res;
}

char bigint_compare(bigint *a, bigint *b)
{
    if (a->sign < b->sign)
        return 1;
    if (b->sign < a->sign)
        return -1;

    if (a->sign)
        return -1 * __bigint_compare_abs(a, b);
    else
        return __bigint_compare_abs(a, b);

    return 0;
}

char __bigint_compare_abs(bigint *a, bigint *b)
{

    if (a->size > b->size)
        return 1;
    if (a->size < b->size)
        return -1;

    int i = a->size - 1;
    do
    {
        if (a->d[i] != b->d[i])
            return a->d[i] - b->d[i];
    } while (i--);

    return 0;
}

/*
* Умножает bigint на задонную цифру.
*/
void __mult_digit(const bigint *src, bigint *res, char digit)
{
    assert(res->bufsize >= src->size + 1);

    char cd = 0;
    int i = 0, tmp;

    res->size = 0;
    res->sign = src->sign;
    do
    {
        tmp = src->d[i] * digit + cd;
        bigint_setdigit(res, i, tmp % 10);
        cd = tmp / 10;
    } while (i++ != src->size);
}

/*
 * Складывает bigint с сдвинутым bigint
*/
void __mult_add_shift_abs(const bigint *src, const bigint *src_shift, bigint *res, unsigned int shift)
{
    unsigned int req_size = max(src->size, src_shift->size + shift);

    assert(res->bufsize >= req_size + 1);

    char cd = 0;
    unsigned int i = 0, tmp;

    res->size = 0;
    res->sign = 0;

    while (i < shift)
    {
        bigint_setdigit(res, i, i > src->size ? 0 : src->d[i]);
        i++;
    }

    do
    {
        tmp = (i >= src->size ? 0 : src->d[i]) +
              (i - shift >= src_shift->size ? 0 : src_shift->d[i - shift]) +
              cd;
        bigint_setdigit(res, i, tmp % 10);
        cd = tmp / 10;
    } while (i++ != req_size);
}

void bigint_mult(const bigint *a, const bigint *b, bigint *res)
{
    unsigned int req_size = a->size + b->size + 2;
    assert(res->bufsize >= req_size);

    res->size = 0;

    bigint tmp_mul = bigint_init(a->size + 1, 0);
    bigint tmp_sum = bigint_init(req_size, 0);

    bigint *op1, *op2, *tmp;
    op1 = res;
    op2 = &tmp_sum;

    for (int i = 0; i < b->size; i++)
    {
        __mult_digit(a, &tmp_mul, b->d[i]);
        __mult_add_shift_abs(op1, &tmp_mul, op2, i);
        tmp = op1;
        op1 = op2;
        op2 = tmp;
    }

    if (b->size % 2)
    {
        bigint_copy(op1, res);
    }
    bigint_free(&tmp_sum);
    bigint_free(&tmp_mul);
}

void bigint_copy(const bigint *src, bigint *dest)
{
    assert(dest->bufsize > src->size);

    dest->sign = src->sign;
    dest->size = 0;

    for (int i = 0; i < src->size; i++)
    {
        bigint_setdigit(dest, i, src->d[i]);
    }
}

void fact(unsigned int n, bigint *res)
{
    int ndc = 0;
    unsigned long reminder = n;
    do
    {
        reminder = reminder / 10;
        ndc++;
    } while (reminder);

    res->size = 0;
    bigint_setdigit(res, 0, 1);

    bigint newres = bigint_init(res->bufsize, 0);
    bigint m = bigint_init(ndc, 0);

    bigint *op1, *op2, *tmp;
    op1 = res;
    op2 = &newres;

    for (unsigned int i = 1; i <= n; i++)
    {
        bigint_init_val(&m, 0, i);
        bigint_mult(op1, &m, op2);

        tmp = op1;
        op1 = op2;
        op2 = tmp;
    }

    bigint_free(&newres);
    bigint_free(&m);
}