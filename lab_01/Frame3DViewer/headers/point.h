#ifndef __POINT_H__
#define __POINT_H__

#include "status.h"
#include <stdio.h>
#include <cstdlib>

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

typedef struct
{
    point_t *array;
    size_t capacity;
    size_t size;
} points_t;


status_t allocate_points_array(points_t &points, size_t array_capacity);
status_t push_back_point(points_t &points, const point_t &point);
status_t free_points(points_t &points);
status_t init_points(points_t &points);
status_t init_point(point_t &point);

#endif