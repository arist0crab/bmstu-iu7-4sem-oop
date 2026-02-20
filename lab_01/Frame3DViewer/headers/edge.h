#ifndef __EDGES_H__
#define __EDGES_H__

#include "status.h"
#include <stdio.h>
#include <cstdlib>

typedef struct
{
    int point_1;
    int point_2;
} edge_t;

typedef struct
{
    edge_t *array;
    size_t capacity;
    size_t size;
} edges_t;

status_t allocate_edges_array(edges_t &edges, const size_t array_capacity);
status_t push_back_edge(edges_t &edges, const edge_t &edge);
status_t free_edges(edges_t &edges);
status_t init_edges(edges_t &edges);

#endif