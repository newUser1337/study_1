#include <math.h>
#include <stdio.h>
#include "vector.h"

vector vector_mul_num(vector *v1, float num)
{
    vector res;
    res.x = v1->x * num;
    res.y = v1->y * num;
    res.z = v1->z * num;

    return res;
}

vector vector_sum(vector *v1, vector *v2)
{
    vector res;
    res.x = v1->x + v2->x;
    res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;

    return res;
}

vector vector_sub(vector *v1, vector *v2)
{
    vector res;
    res.x = v1->x - v2->x;
    res.y = v1->y - v2->y;
    res.z = v1->z - v2->z;

    return res;
}

float vector_mul_scal(vector *v1, vector *v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

float vector_module(vector *v)
{
    return sqrt(vector_mul_scal(v, v));
}

vector vector_mul_vec(vector *v1, vector *v2)
{
    vector res;
    res.x = v1->y * v2->z - v1->z * v2->y;
    res.y = v1->z * v2->x - v1->x * v2->z;
    res.z = v1->x * v2->y - v1->y * v2->x;

    return res;
}

float vector_mul_cross(vector *v1, vector *v2, vector *v3)
{
    vector vmul = vector_mul_vec(v2, v3);
    return vector_mul_scal(v1, &vmul);
}

float vector_angle(vector *v1, vector *v2)
{
    return vector_mul_scal(v1, v2) / (vector_module(v1) * vector_module(v2));
}

float vector_angle_sin(vector *v1, vector *v2)
{
    vector vmul = vector_mul_vec(v1, v2);
    return vector_module(&vmul) / (vector_module(v1) * vector_module(v2));
}

float vector_point_line_dist(vector *r, line *l)
{
    vector vsub = vector_sub(r, &l->r0);
    vector vmul = vector_mul_vec(&vsub, &l->a);

    return vector_module(&vmul) / vector_module(&l->a);
}

float vector_point_plane_dist(vector *r, plane *p)
{
    vector vsub = vector_sub(r, &p->r0);

    return vector_mul_scal(&vsub, &p->n) / vector_module(&p->n);
}

float vector_line_line_dist(line *l1, line *l2)
{
    vector vsub = vector_sub(&l1->r0, &l2->r0);
    vector vmul = vector_mul_vec(&l1->a, &l2->a);

    return vector_mul_cross(&vsub, &l1->a, &l2->a) / vector_module(&vmul);
}

vector vector_vector_plane_proj(vector *v, plane *p)
{
    vector vsub = vector_sub(&p->r0, v);
    float mul = vector_mul_scal(&vsub, &p->n) / (vector_module(&p->n) * vector_module(&p->n));
    vector res = vector_mul_num(&p->n, mul);

    return vector_sum(&res, v);
}

float vector_calc_det(float *a11, float *a22, float *a21, float *a12)
{
    return (*a11 * *a22) - (*a12 * *a21);
}

vector vector_get_line_point(plane *p1, plane *p2)
{
    vector res;
    float d1 = vector_mul_scal(&p1->n, &p1->r0);
    float d2 = vector_mul_scal(&p2->n, &p2->r0);
    float maindet;

    do
    {
        //XY
        maindet = vector_calc_det(&p1->n.x, &p2->n.y, &p1->n.y, &p2->n.x);
        if (maindet)
        {
            res.z = 0;
            res.y = vector_calc_det(&p1->n.x, &d2, &d1, &p2->n.x) / maindet;
            res.x = vector_calc_det(&d1, &p2->n.y, &p1->n.y, &d2) / maindet;
            break;
        }

        //XZ
        maindet = vector_calc_det(&p1->n.x, &p2->n.z, &p1->n.z, &p2->n.x);
        if (maindet)
        {
            res.y = 0;
            res.z = vector_calc_det(&p1->n.x, &d2, &d1, &p2->n.x) / maindet;
            res.x = vector_calc_det(&d1, &p2->n.z, &p1->n.z, &d2) / maindet;
            break;
        }

        //YZ
        maindet = vector_calc_det(&p1->n.y, &p2->n.z, &p1->n.z, &p2->n.y);
        if (maindet)
        {
            res.x = 0;
            res.z = vector_calc_det(&p1->n.y, &d2, &d1, &p2->n.y) / maindet;
            res.y = vector_calc_det(&d1, &p2->n.z, &p1->n.z, &d2) / maindet;
            break;
        }

    } while (1);

    return res;
}

line vector_plane_plane_int(plane *p1, plane *p2)
{
    line lres;
    lres.a = vector_mul_vec(&p1->n, &p2->n);
    if (lres.a.x == 0 && lres.a.y == 0 && lres.a.z == 0)
        return lres; //Плоскости совпадают или паралелльны

    lres.r0 = vector_get_line_point(p1, p2);

    // vector vsub = vector_sub(&p1->r0, &p2->r0);
    // float scal = vector_mul_scal(&vsub, &p1->n);
    // vsub = vector_mul_num(&p1->n, scal / (vector_module(&p1->n) * vector_module(&p1->n)));
    // vsub = vector_mul_num(&vsub, 1.0 / vector_angle_sin(&p1->n, &p2->n));
    // //lres.r0 = vsub;
    // lres.r0 = vector_sum(&p2->r0,&vsub);

    return lres;
}