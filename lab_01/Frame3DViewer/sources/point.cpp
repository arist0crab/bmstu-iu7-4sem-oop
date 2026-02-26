#include "point.h"


status_t push_back_point(points_t &points, const point_t &point)
{
    status_t sc = SUCCESS;

    if (points.size == points.capacity)
        sc = ERR_OUT_OF_RANGE;

    if (sc == SUCCESS)
        points.array[points.size++] = point;

    return sc;
}

status_t allocate_points_array(points_t &points, const size_t array_capacity)
{
    status_t sc = SUCCESS;

    if (array_capacity == 0)
        sc = ERR_EMPTY;

    if (sc == SUCCESS)
    {
        points.array = (point_t *)calloc(array_capacity, sizeof(point_t));
        if (points.array == NULL)
            sc = ERR_MEM;
    }

    if (sc == SUCCESS)
    {
        points.size = 0;
        points.capacity = array_capacity;
    }

    return sc;
}

status_t init_points(points_t &points)
{
    points.array = NULL;
    points.capacity = 0;
    points.size = 0;

    return SUCCESS;
}

status_t init_point(point_t &point)
{
    point.x = 0;
    point.y = 0;
    point.z = 0;

    return SUCCESS;
}

status_t free_points(points_t &points)
{
    if (points.array)
        free(points.array);

    points.array = NULL;
    points.capacity = 0;
    points.size = 0;

    return SUCCESS;
}