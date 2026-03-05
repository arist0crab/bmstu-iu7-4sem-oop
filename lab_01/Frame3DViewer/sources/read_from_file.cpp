#include "read_from_file.h"


/* чтение фигуры */
static status_t read_figure_from_file(FILE *filestream, figure_t &figure);

/* чтение точек из файла */
static status_t read_points_from_file(FILE *filestream, points_t &points);
static status_t read_points_to_array(FILE *filestream, points_t &points, const size_t points_quantity);
static status_t read_point_to_array(FILE *filestream, points_t &points);
static status_t read_point_from_file(FILE *filestream, point_t &point);

/* чтение сторон из файла */
static status_t read_edges_from_file(FILE *filestream, edges_t &edges);
static status_t read_edges_to_array(FILE *filestream, edges_t &edges, const size_t edges_quantity);
static status_t read_edge_to_array(FILE *filestream, edges_t &edges);
static status_t read_edge_from_file(FILE *filestream, edge_t &edge);

static status_t read_size_from_file(FILE *filestream, size_t &number);

/* безопасное открытие и закрытие файла */
static status_t safe_file_open(FILE **filestream, const char *filename);
static status_t safe_file_close(FILE *filestream);


status_t load_figure_from_file(figure_t &figure, const char *filename)
{
    figure_t local_figure;
    init_figure(local_figure);

    FILE *filestream = NULL;
    status_t sc = safe_file_open(&filestream, filename);

    if (sc == SUCCESS)
    {
        sc = read_figure_from_file(filestream, local_figure);
        safe_file_close(filestream);

        if (sc == SUCCESS)
            sc = move_figure(figure, local_figure);
    }

    if (sc != SUCCESS) 
        free_figure(local_figure);

    return sc;
}

static status_t read_figure_from_file(FILE *filestream, figure_t &figure)
{
    if (filestream == NULL)
        return ERR_FILE;

    status_t sc = read_points_from_file(filestream, figure.points);
    if (sc == SUCCESS)
        sc = read_edges_from_file(filestream, figure.edges);

    return sc;
}

static status_t read_points_from_file(FILE *filestream, points_t &points)
{
    if (filestream == NULL)
        return ERR_FILE;

    size_t points_quantity = 0;
    status_t sc = read_size_from_file(filestream, points_quantity);

    if (sc == SUCCESS)
    {
        points_t local_points =  { NULL, 0, 0 };
        sc = allocate_points_array(local_points, points_quantity);
        if (sc == SUCCESS)
        {
            sc = read_points_to_array(filestream, local_points, points_quantity);
            if (sc == SUCCESS)
                points = local_points;
        }

        if (sc != SUCCESS)
            free_points(local_points);
    }

    return sc;
}

static status_t read_points_to_array(FILE *filestream, points_t &points, const size_t points_quantity)
{
    status_t sc = SUCCESS;

    for (size_t i = 0; sc == SUCCESS && i < points_quantity; i++)
        sc = read_point_to_array(filestream, points);

    return sc;
}

static status_t read_point_to_array(FILE *filestream, points_t &points)
{
    point_t local_point = { 0, 0, 0 };

    status_t sc = read_point_from_file(filestream, local_point);
    if (sc == SUCCESS)
        sc = push_back_point(points, local_point);

    return sc;
}

static status_t read_edges_from_file(FILE *filestream, edges_t &edges)
{
    if (filestream == NULL)
        return ERR_FILE;

    size_t edges_quantity = 0;
    status_t sc = read_size_from_file(filestream, edges_quantity);

    if (sc == SUCCESS)
    {
        edges_t local_edges = { NULL, 0, 0 };
        sc = allocate_edges_array(local_edges, edges_quantity);
        if (sc == SUCCESS)
        {
            sc = read_edges_to_array(filestream, local_edges, edges_quantity);
            if (sc == SUCCESS)
                edges = local_edges;
        }

        if (sc != SUCCESS)
            free_edges(local_edges);
    }

    return sc;
}

static status_t read_edges_to_array(FILE *filestream, edges_t &edges, const size_t edges_quantity)
{
    status_t sc = SUCCESS;

    for (size_t i = 0; sc == SUCCESS && i < edges_quantity; i++)
        sc = read_edge_to_array(filestream, edges);

    return sc;
}

static status_t read_edge_to_array(FILE *filestream, edges_t &edges)
{
    edge_t local_edge = { 0, 0 };

    status_t sc = read_edge_from_file(filestream, local_edge);
    if (sc == SUCCESS)
        sc = push_back_edge(edges, local_edge);

    return sc;
}


static status_t read_point_from_file(FILE *filestream, point_t &point)
{
    status_t sc = SUCCESS;
    point_t local_point;
    
    if (filestream == NULL)
        sc = ERR_FILE;
    
    if (sc == SUCCESS)
        if (fscanf(filestream, "%lf %lf %lf", &local_point.x, &local_point.y, &local_point.z) != 3)
            sc = ERR_FILE;
    
    if (sc == SUCCESS)
        point = local_point;

    return sc;
}


static status_t read_edge_from_file(FILE *filestream, edge_t &edge)
{
    status_t sc = SUCCESS;
    edge_t local_edge;

    if (filestream == NULL)
        sc = ERR_FILE;

    if (sc == SUCCESS)
        if (fscanf(filestream, "%lu %lu", &local_edge.point_1, &local_edge.point_2) != 2)
            sc = ERR_FILE;

    if (sc == SUCCESS)
        edge = local_edge;

    return sc;
}


static status_t read_size_from_file(FILE *filestream, size_t &number)
{
    status_t sc = SUCCESS;
    size_t local_number;
    
    if (filestream == NULL)
    sc = ERR_FILE;
    
    if (sc == SUCCESS)
        if (fscanf(filestream, "%lu", &local_number) != 1)
            sc = ERR_FILE;

    if (sc == SUCCESS)
        number = local_number;

    return sc;
}


static status_t safe_file_open(FILE **filestream, const char *filename)
{
    status_t sc = SUCCESS;

    if (filestream == NULL || filename == NULL)
        sc = ERR_FILE;

    if (sc == SUCCESS)
    {
        *filestream = fopen(filename, "r");
        if (*filestream == NULL)
            sc = ERR_FILE;
    }

    return sc;
}


static status_t safe_file_close(FILE *filestream)
{
    if (filestream) 
        fclose(filestream);

    filestream = NULL;

    return SUCCESS;
}