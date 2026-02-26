#include "read_from_file.h"

/* функции чтения данных из файла */
static status_t read_points_from_file(points_t &points, const FILE *filestream);
static status_t read_point_from_file(const FILE *filestream, point_t &point);
static status_t read_edges_from_file(edges_t &edges, const FILE *filestream);
static status_t read_edge_from_file(const FILE *filestream, edge_t &edge);
static status_t read_size_from_file(const FILE *filestream, size_t &number);

/* безопасное открытие и закрытие файла */
static status_t safe_file_open(const char *filename, FILE **filestream);
static status_t safe_file_close(FILE *filestream);


status_t read_figure_from_file(figure_t &figure, const char *filename)
{
    status_t sc = SUCCESS;
    figure_t local_figure;
    FILE *filestream = NULL;

    sc = safe_file_open(filename, &filestream);

    if (sc == SUCCESS)
        init_figure(local_figure);

    if (sc == SUCCESS)
    {
        sc = read_points_from_file(local_figure.points, filestream);
        if (sc == SUCCESS)
            sc = read_edges_from_file(local_figure.edges, filestream);
    }

    safe_file_close(filestream);

    if (sc == SUCCESS) sc = move_figure(figure, local_figure);
    else free_figure(local_figure);

    return sc;
}

static status_t read_points_from_file(points_t &points, const FILE *filestream)
{
    status_t sc = SUCCESS;
    size_t points_quantity = 0;
    points_t local_points =  { NULL, 0, 0 };

    if (filestream == NULL)
        sc = ERR_FILE;

    if (sc == SUCCESS)
        sc = read_size_from_file(filestream, points_quantity);

    if (sc == SUCCESS)
        sc = allocate_points_array(local_points, points_quantity);

    for (size_t i = 0; sc == SUCCESS && i < points_quantity; i++)
        sc = read_point_from_file(filestream, local_points.array[i]);

    if (sc != SUCCESS)
        free_points(local_points);

    if (sc == SUCCESS)
        points = local_points;

    return sc;
}

static status_t read_edges_from_file(edges_t &edges, const FILE *filestream)
{
    status_t sc = SUCCESS;
    size_t edges_quantity = 0;
    edges_t local_edges = { NULL, 0, 0 };

    if (filestream == NULL)
        sc = ERR_FILE;

    if (sc == SUCCESS)
        sc = read_size_from_file(filestream, edges_quantity);

    if (sc == SUCCESS)
        sc = allocate_edges_array(local_edges, edges_quantity);

    for (size_t i = 0; sc == SUCCESS && i < edges_quantity; i++)
        sc = read_edge_from_file(filestream, local_edges.array[i]);

    if (sc != SUCCESS)
        free_edges(local_edges);

    if (sc == SUCCESS)
        edges = local_edges;

    return sc;
}


static status_t read_point_from_file(const FILE *filestream, point_t &point)
{
    status_t statuc = SUCCESS;
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


static status_t read_edge_from_file(const FILE *filestream, edge_t &edge)
{
    status_t sc = SUCCESS;
    edge_t local_edge;

    if (filestream == NULL)
        sc = ERR_FILE;

    if (sc == SUCCESS)
        if (fscanf(filestream, "%lu %lu", &local_edge.p1, &local_edge.p2) != 2)
            sc = ERR_FILE;

    if (sc == SUCCESS)
        edge = local_edge;

    return sc;
}


static status_t read_size_from_file(const FILE *filestream, size_t &number)
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


static status_t safe_file_open(const char *filename, FILE **filestream)
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