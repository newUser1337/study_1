#ifndef __SPARCE__
#define __SPARCE__

typedef struct sparce
{
    int **ST;
    int size;
    int log;
} sparce;

sparce *sparce_init(int *, int);
void sparce_print(sparce *);
int sparce_rmq(sparce *, int, int);
#endif