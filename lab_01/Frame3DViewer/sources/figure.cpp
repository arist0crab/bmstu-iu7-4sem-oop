#include "figure.h"


// сдвиг фигуры
status_t move_point(point_t &point, const move_data_t &move_data);
status_t move_points(points_t &points, const move_data_t move_data);

// вращение фигуры
status_t rotate_points(points_t &points, const point_t &rotation_center, const rotate_data_t &rotate_data);
status_t rotate_point(point_t &point, const point_t &rotation_center, const rotate_data_t &rotate_data);
status_t rotate_x_coordinate(point_t &point, const point_t &rotation_center, const double angle);
status_t rotate_y_coordinate(point_t &point, const point_t &rotation_center, const double angle);
status_t rotate_z_coordinate(point_t &point, const point_t &rotation_center, const double angle);
status_t to_radians(const double degrees, double &radians);

// масштабирование фигуры
status_t scale_points(points_t &points, const point_t &scale_center, const scale_data_t &scale_data);
status_t scale_point(point_t &point, const point_t &scale_center, const scale_data_t &scale_data);

// отрисовка фигуры
status_t draw_lines(const points_t &points, const edges_t &edges, draw_scene_t &scene);
status_t scene_reset(draw_scene_t &scene);

// проверка валидности фигуры
status_t figure_ensure_valid(const figure_t &figure);
status_t check_edges_indexes(const points_t &points, const edges_t &edges);
status_t check_edge_indexes(const int &points_size, const edge_t &edge);
status_t check_figure_empty(const points_t &points, const edges_t &edges_t);

// чтение фигуры из файла
status_t read_points_from_file(figure_t &figure, ifstream &filestream);
status_t read_edges_from_file(figure_t &figure, ifstream &filestream);
status_t free_figure(figure_t &figure);

// ===================================
// Масштабирование фигуры
// ===================================

status_t scale_figure(figure_t &figure, const scale_data_t &scale_data)
{
    status_t sc = figure_ensure_valid(figure);

    if (sc == SUCCESS)
    {
        if (scale_data.kx == 0) sc = ERR_SCALE;
        if (scale_data.ky == 0) sc = ERR_SCALE;
        if (scale_data.kz == 0) sc = ERR_SCALE;
    }

    if (sc == SUCCESS)
        scale_points(figure.points, figure.center, scale_data);

    return sc;
}

status_t scale_points(points_t &points, const point_t &scale_center, const scale_data_t &scale_data)
{
    for (size_t i = 0; i < points.size; i++)
        scale_point(points.array[i], scale_center, scale_data);

    return SUCCESS;
}

status_t scale_point(point_t &point, const point_t &scale_center, const scale_data_t &scale_data)
{
    point.x = (point.x - scale_center.x) * scale_data.kx + scale_center.x;
    point.y = (point.y - scale_center.y) * scale_data.ky + scale_center.y;
    point.z = (point.z - scale_center.z) * scale_data.kz + scale_center.z;

    return SUCCESS;
}

// ===================================
// Поворот фигуры
// ===================================

status_t rotate_figure(figure_t &figure, const rotate_data_t &rotate_data)
{
    status_t sc = figure_ensure_valid(figure);

    if (sc == SUCCESS)
        rotate_points(figure.points, figure.center, rotate_data);

    return sc;
}

status_t rotate_points(points_t &points, const point_t &rotation_center, const rotate_data_t &rotate_data)
{
    for (size_t i = 0; i < points.size; i++)
        rotate_point(points.array[i], rotation_center, rotate_data);

    return SUCCESS;
}

status_t rotate_point(point_t &point, const point_t &rotation_center, const rotate_data_t &rotate_data)
{
    rotate_x_coordinate(point, rotation_center, rotate_data.ax);
    rotate_y_coordinate(point, rotation_center, rotate_data.ay);
    rotate_z_coordinate(point, rotation_center, rotate_data.az);

    return SUCCESS;
}

status_t rotate_x_coordinate(point_t &point, const point_t &rotation_center, const double angle)
{
    double r_cos, r_sin, radians;
    double y = point.y;

    to_radians(angle, radians);
    r_cos = cos(radians);
    r_sin = sin(radians);

    point.y = (point.y - rotation_center.y) * r_cos + (point.z - rotation_center.z) * r_sin + rotation_center.y;
    point.z = -(y - rotation_center.y) * r_sin + (point.z - rotation_center.z) * r_cos + rotation_center.z;

    return SUCCESS;
}

status_t rotate_y_coordinate(point_t &point, const point_t &rotation_center, const double angle)
{
    double r_cos, r_sin, radians;
    double x = point.x;

    to_radians(angle, radians);
    r_cos = cos(radians);
    r_sin = sin(radians);

    point.x = (point.x - rotation_center.x) * r_cos + (point.z - rotation_center.z) * r_sin + rotation_center.x;
    point.z = -(x - rotation_center.y) * r_sin + (point.z - rotation_center.z) * r_cos + rotation_center.z;

    return SUCCESS;
}

status_t rotate_z_coordinate(point_t &point, const point_t &rotation_center, const double angle)
{
    double r_cos, r_sin, radians;
    double x = point.x;

    to_radians(angle, radians);
    r_cos = cos(radians);
    r_sin = sin(radians);

    point.x = (point.x - rotation_center.x) * r_cos + (point.y - rotation_center.y) * r_sin + rotation_center.x;
    point.y = -(x - rotation_center.y) * r_sin + (point.y - rotation_center.y) * r_cos + rotation_center.y;

    return SUCCESS;
}

status_t to_radians(const double degrees, double &radians)
{
    radians = degrees * M_PI / 180.0;

    return SUCCESS;
}

// ===================================
// Сдвиг фигуры
// ===================================

status_t move_figure(figure_t &figure, const move_data_t &move_data)
{
    status_t sc = figure_ensure_valid(figure);

    if (sc == SUCCESS)
    {
        move_point(figure.center, move_data);
        move_points(figure.points, move_data);
    }

    return sc;
}

status_t move_points(points_t &points, const move_data_t move_data)
{
    for (size_t i = 0; i < points.size; i++)
        move_point(points.array[i], move_data);

    return SUCCESS;
}

status_t move_point(point_t &point, const move_data_t &move_data)
{
    point.x += move_data.dx;
    point.y += move_data.dy;
    point.z += move_data.dz;

    return SUCCESS;
}

// ===================================
// Отрисовка фигуры
// ===================================

status_t draw_figure(figure_t &figure, draw_scene_t &scene)
{
    status_t sc = figure_ensure_valid(figure);

    if (sc == SUCCESS)
    {
        scene_reset(scene);
        draw_lines(figure.points, figure.edges, scene);
    }
    
    return sc;
}

status_t scene_reset(draw_scene_t &scene)
{
    scene.scene->clear();
    
    return SUCCESS;
}

status_t draw_lines(const points_t &points, const edges_t &edges, draw_scene_t &scene)
{
    point_t p1, p2;
    double x1, y1, x2, y2; 
    edge_t current_edge;

    for (size_t i = 0; i < edges.size; i++)
    {
        current_edge = edges.array[i];

        p1 = points.array[current_edge.point_1];
        p2 = points.array[current_edge.point_2];

        x1 = p1.x + scene.width / 2;
        y1 = p1.y + scene.height / 2;
        x2 = p2.x + scene.width / 2;
        y2 = p2.y + scene.height / 2;

        scene.scene->addLine(x1, y1, x2, y2);
    }

    return SUCCESS;
}

// ===================================
// Чтение фигуры из файла
// ===================================

status_t read_figure_from_file(figure_t &figure, const string filename)
{
    status_t sc = SUCCESS;

    free_figure(figure);

    ifstream filestream(filename);

    if (filestream.is_open())
    {
        read_points_from_file(figure, filestream);
        read_edges_from_file(figure, filestream);
    }
    else sc = ERR_FILE;

    filestream.close();

    if (sc == SUCCESS)
        sc = figure_ensure_valid(figure);

    return sc;
}

status_t read_points_from_file(figure_t &figure, ifstream &filestream)
{
    status_t sc;
    point_t point;
    size_t points_quantity;

    filestream >> points_quantity;

    sc = allocate_points_array(figure.points, points_quantity);

    for (size_t i = 0; sc == SUCCESS && i < points_quantity; i++)
    {
        filestream >> point.x >> point.y >> point.z;
        push_back_point(figure.points, point);
    }

    return SUCCESS;
}

status_t read_edges_from_file(figure_t &figure, ifstream &filestream)
{
    status_t sc;
    edge_t edge;
    size_t edges_quantity;

    filestream >> edges_quantity;

    sc = allocate_edges_array(figure.edges, edges_quantity);
    
    for (size_t i = 0; i < edges_quantity; i++)
    {
        filestream >> edge.point_1 >> edge.point_2;
        push_back_edge(figure.edges, edge);
    }

    return sc;
}

// ===================================
// Проверка валидности фигуры
// ===================================

status_t figure_ensure_valid(const figure_t &figure)
{
    status_t sc = check_figure_empty(figure.points, figure.edges);
    if (sc == SUCCESS)
        sc = check_edges_indexes(figure.points, figure.edges);
    return sc;    
}

status_t check_edges_indexes(const points_t &points, const edges_t &edges)
{
    status_t sc = SUCCESS;

    for (size_t i = 0; sc == SUCCESS && i < edges.size; i++)
        sc = check_edge_indexes(points.size, edges.array[i]);

    return sc;
}

status_t check_edge_indexes(const int &points_size, const edge_t &edge)
{
    status_t sc = SUCCESS;

    int i1 = edge.point_1;
    int i2 = edge.point_2;

    if (i1 < 0 || i1 >= points_size || i2 < 0 || i2 >= points_size)
        sc = ERR_FIGURE_DATA;

    return sc;
}

status_t check_figure_empty(const points_t &points, const edges_t &edges)
{
    return (points.size == 0 || edges.size == 0) ? ERR_EMPTY : SUCCESS;    
}

// ===================================
// Освобождение и инициализация фигуры
// ===================================

status_t free_figure(figure_t &figure)
{
    init_point(figure.center);
    free_points(figure.points);
    free_edges(figure.edges);

    return SUCCESS;
}

status_t init_figure(figure_t &figure)
{
    init_point(figure.center);
    init_points(figure.points);
    init_edges(figure.edges);

    return SUCCESS;
}