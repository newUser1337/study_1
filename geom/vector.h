#ifndef __VECTOR__
#define __VECTOR__

typedef struct vector
{
    float x;
    float y;
    float z;
} vector;

typedef struct line
{
    vector a;
    vector r0;
} line;

typedef struct plane
{
    vector n;
    vector r0;
} plane;

vector vector_mul_num(vector *, float);
vector vector_sum(vector *, vector *);
vector vector_sub(vector *, vector *);
float vector_mul_scal(vector *, vector *);
vector vector_mul_vec(vector *, vector *);
float vector_mul_cross(vector *, vector *, vector *);
float vector_module(vector *);

float vector_angle(vector *, vector *);
float vector_angle_sin(vector *, vector *);
float vector_point_line_dist(vector *, line *);
float vector_point_plane_dist(vector *, plane *);
float vector_line_line_dist(line *, line *);
vector vector_vector_plane_proj(vector *, plane *);

float vector_calc_det(float *,float *, float *, float *);
line vector_plane_plane_int(plane *, plane *);
#endif