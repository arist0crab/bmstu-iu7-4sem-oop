#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include <exception>
#include <cstring>
#include <cstdio>

#define MATRIX_ITERATOR_RANDOM_ACCESS_CORRESPONDENCE_ERROR "MatrixIterator must meet RandomAccessIterator requirements."
#define MATRIX_CONST_ITERATOR_RANDOM_ACCESS_CORRESPONDENCE_ERROR "MatrixConstIterator must meet RandomAccessIterator requirements."
#define MATRIX_ITERATOR_VALUE_TYPE_ERROR "Iterator value_type must match Matrix value_type."

#define MATRIX_C_MATRIX_DOESNT_EXIST_ERROR "C-matrix pointer is null"
#define MATRIX_ELEMENT_TYPE_ERROR "Matrix element type must be copyable and destructible"
#define MATRIX_INITIALIZER_LIST_CONSTRUCTOR_ERROR "Inconsistent row lengths in initializer_list"
#define MATRIX_SAME_DIMENSIONS_ERROR "Matrix dimensions must match for addition"
#define MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR "Matrix row index out of range"
#define MATRIX_COL_INDEX_OUT_OF_RANGE_ERROR "Matrix column index out of range"
#define MATRIX_INDEX_OUT_OF_RANGE_ERROR "Matrix index out of range"
#define MATRIX_MULTIPLICATION_ERROR "Matrix dimensions must agree for multiplication"
#define MATRIX_EXPONENTATION_ERROR "Matrix must be square for exponentiation"
#define MATRIX_SQUARE_ERROR "Matrix must be square"
#define MATRIX_EMPTY_ERROR "Matrix must be non-empty"
#define MATRIX_TRACE_ERROR "Trace is only defined for square matrices"
#define MATRIX_SINGULAR_ERROR "Matrix is singular"


class BaseException : public std::exception 
{
    protected:
        char m_msg[512]; 

    public:
        explicit BaseException(const char* filename, int line, const char* func, const char* message) noexcept 
        {
            std::snprintf(m_msg, sizeof(m_msg), "File: %s, Line: %d, Function: %s, Info: %s", filename, line, func, message);
        }

        virtual const char* what() const noexcept override 
        {
            return m_msg;
        }
};


class MatrixException : public BaseException 
{
    public:
        MatrixException(const char* filename, int line, const char* func, const char* message) noexcept : BaseException(filename, line, func, message) 
        {
            char temp[512];
            std::snprintf(temp, sizeof(temp), "Matrix Error -> %s", m_msg);
            std::strncpy(m_msg, temp, sizeof(m_msg));
            m_msg[sizeof(m_msg) - 1] = '\0';
        }
};


class MatrixIndexException : public MatrixException 
{
    public:
        MatrixIndexException(const char* filename, int line, const char* func, const char* message) noexcept : MatrixException(filename, line, func, message) {}
};


class MatrixDimensionException : public MatrixException 
{
    public:
        MatrixDimensionException(const char* filename, int line, const char* func, const char* message) noexcept : MatrixException(filename, line, func, message) {}
};

#endif 