#include "manager.h"


status_t manage_request(request_t &request)
{
    status_t sc = SUCCESS;
    static figure_t figure;

    switch (request.type)
    {
        case LOAD_FIGURE:
            sc = read_figure_from_file(figure, request.filename);
            break;

        case DRAW_FIGURE:
            sc = draw_figure(figure, request.scene);
            break;
            
        case MOVE_FIGURE:
            sc = move_figure(figure, request.move_data);
            break;

        case SCALE_FIGURE:
            sc = scale_figure(figure, request.scale_data);
            break;

        case ROTATE_FIGURE:
            sc = rotate_figure(figure, request.rotate_data);
            break;

        default:
            sc = ERR_UNDEFINED;
    }

    return sc;
}