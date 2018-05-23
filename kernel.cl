
typedef struct __attribute__((packed)) point_float
{
    float x;
    float y;
} Point;

typedef struct __attribute__((packed)) line_tp
{
    Point p1;
    Point p2;
} Line;

__kernel void cut_lines(
        __global const Point * polyogn, __global const int * size,
        __global const Line *tc, __global const int * max_r_size,
        __global Line * results)
{


}
