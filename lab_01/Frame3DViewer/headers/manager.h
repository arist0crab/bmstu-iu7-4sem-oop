#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "status.h"
#include "figure.h"
#include <iostream>
using namespace std;

typedef enum
{
    LOAD_FIGURE,
    DRAW_FIGURE,
    MOVE_FIGURE,
    SCALE_FIGURE,
    ROTATE_FIGURE
} request_type_t;

typedef struct
{
    request_type_t type;
    draw_scene_t scene;
    union
    {
        const char *filename;
        move_data_t move_data;
        scale_data_t scale_data;
        rotate_data_t rotate_date;
    };
} request_t;

status_t manage_request(request_t &request, figure_t &figure);

#endif