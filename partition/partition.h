#ifndef _PARTITION_
#define _PARTITION_

typedef struct partition_generator {
    int *a;
    int n;
    int count;

    int *sp; 
    int *ep;
} partition_generator;

partition_generator init_partition_generator(int);
void split_arr(partition_generator *, int *);
int *_find_small(partition_generator *);
void _set_arr(partition_generator *, int *);
int partition_next(partition_generator *);
void destruct_partition_generator(partition_generator *);

#endif