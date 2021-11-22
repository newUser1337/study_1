#ifndef __COMPL__
#define __COMPL__

typedef enum compltype
{
    ALG = 1,
    TRIG,
    EXP
} compltype;

typedef union complval
{
    struct 
    {
        float x;
        float y;
    } alg;
    struct 
    {
        float r;
        float fi;
    } trig;
    struct 
    {
        float r;
        float fi;
    } exp;
} complval;

typedef struct Compl
{
    compltype type;
    complval val;

} Compl;

void compl_print(Compl*);

#endif
