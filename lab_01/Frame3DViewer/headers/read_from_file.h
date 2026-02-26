#ifndef __READ_FROM_FILE_H__
#define __READ_FROM_FILE_H__

#include "status.h"
#include "figure.h"
#include "point.h"
#include <stdio.h>

// чтение фигуры из файла
status_t read_figure_from_file(figure_t &figure, const char *filename);

#endif