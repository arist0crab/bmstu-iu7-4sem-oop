#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "status.h"
#include <QGraphicsScene>
#include <iostream>
#include <vector>
using namespace std;

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

typedef struct
{
    int point_1;
    int point_2;
} edge_t;

typedef struct
{
    point_t center;
    vector<edge_t> edges;
    vector<point_t> points;
} figure_t;

typedef struct
{
    QGraphicsScene *scene;
    double width;
    double height;
} draw_scene_t;

typedef struct { double dx, dy, dz; } move_data_t;
typedef struct { double kx, ky, kz; } scale_data_t;
typedef struct { double ax, ay, az; } rotate_data_t;

    
status_t figure_reset(figure_t &figure);
status_t draw_figure(figure_t &figure, draw_scene_t &scene);
status_t move_figure(figure_t &figure, const move_data_t &move_data);
status_t read_figure_from_file(figure_t &figure, const string filename);

#endif