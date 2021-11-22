#include <stdio.h>
#include "vector.h"

void printvector(vector *);

int main()
{
    vector a;
    a.x = 1;
    a.y = 2;
    a.z = 3;

    vector b;
    b.x = 2;
    b.y = 3;
    b.z = 5;

    vector c;
    c.x = 2;
    c.y = 1;
    c.z = 2;

    vector mulnum = vector_mul_num(&a, 2);
    printvector(&mulnum);

    vector sum = vector_sum(&a, &b);
    printvector(&sum);

    vector sub = vector_sub(&a, &b);
    printvector(&sub);

    float scal = vector_mul_scal(&a, &b);
    printf("scal %f\n", scal);

    vector mulvec = vector_mul_vec(&a, &b);
    printvector(&mulvec);

    float mulcross = vector_mul_cross(&a, &b, &c);
    printf("cross %f\n", mulcross);

    float module = vector_module(&a);
    printf("modul %f\n", module);

    float cosangle = vector_angle(&a, &b);
    printf("cos angle %f\n", cosangle);

    line l;
    l.a.x = 2;
    l.a.y = 2;
    l.a.z = 0;
    l.r0.x = 2;
    l.r0.y = 4;
    l.r0.z = 0;

    vector v;
    v.x = 2;
    v.y = 8;
    v.z = 0;

    float dist = vector_point_line_dist(&v, &l);
    printf("distance %f\n", dist);

    plane p;
    p.n.x = 1;
    p.n.y = 1;
    p.n.z = 1;
    p.r0.x = 0;
    p.r0.y = 0;
    p.r0.z = 1;

    v.x = 0;
    v.y = 0;
    v.z = 2;

    dist = vector_point_plane_dist(&v, &p);
    printf("distance plane %f\n", dist);

    line l1;
    l1.a.x = 1;
    l1.a.y = 1;
    l1.a.z = 0;
    l1.r0.x = 0;
    l1.r0.y = 0;
    l1.r0.z = 0;

    line l2;
    l2.a.x = 1;
    l2.a.y = 0;
    l2.a.z = 0;
    l2.r0.x = 0;
    l2.r0.y = 0;
    l2.r0.z = 1;

    dist = vector_line_line_dist(&l1, &l2);
    printf("distance line %f\n", dist);

    p.n.x = 0;
    p.n.y = 0;
    p.n.z = 1;
    p.r0.x = 1;
    p.r0.y = 2;
    p.r0.z = 2;

    v.x = 3;
    v.y = 4;
    v.z = -1;

    vector vpoint = vector_vector_plane_proj(&v, &p);
    printvector(&vpoint);
    printf("-----------------\n");
    plane p1, p2;
    p1.n.x = 1;
    p1.n.y = 2;
    p1.n.z = 1;
    p1.r0.x = -9;
    p1.r0.y = -18;
    p1.r0.z = -9;

    p2.n.x = 2;
    p2.n.y = 9;
    p2.n.z = -5;
    p2.r0.x = 2;
    p2.r0.y = -4;
    p2.r0.z = 0;

    line lines = vector_plane_plane_int(&p1, &p2);
    printvector(&lines.a);
    printvector(&lines.r0);

    return 0;
}

void printvector(vector *v)
{
    printf("(%f,%f,%f)\n", v->x, v->y, v->z);
}