#include "manager.h"


status_t manage_request(request_t &request, figure_t &figure)
{
    status_t sc = SUCCESS;
    switch (request.type)
    {
        case LOAD_FIGURE:
            figure_reset(figure);
            sc = read_figure_from_file(figure, request.filename);
            break;

        case DRAW_FIGURE:
            sc = draw_figure(figure, request.scene);
            break;
            
        case MOVE_FIGURE:
            sc = move_figure(figure, request.move_data);
            break;

        case SCALE_FIGURE:
            // TODO
            break;

        case ROTATE_FIGURE:
            // TODO
            break;

        default:
            sc = ERR_UNDEFINED;
    }

    return sc;
}