#include "matrix.hpp"


// ===============================
//          Конструкторы
// ===============================


template <typename T>
Matrix<T>::Matrix() : m_rows(0), m_cols(0), m_data(nullptr)
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);
}


template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols) : m_rows(rows), m_cols(cols), m_data(std::make_unique<T[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        reset_matrix();
}


template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols, const T& value) : m_rows(rows), m_cols(cols), m_data(std::make_unique<T[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        reset_matrix();

    std::fill(m_data.get(), m_data.get() + rows * cols, value);
}


template <typename T>
void Matrix<T>::reset_matrix()
{
    m_rows = 0;
    m_cols = 0;
    m_data.reset();
}