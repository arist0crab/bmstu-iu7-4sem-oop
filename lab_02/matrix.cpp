#include "matrix.hpp"


// ===============================
//          MatrixRow
// ===============================


template <typename T>
Matrix<T>::MatrixRow::size_type Matrix<T>::MatrixRow::size() const noexcept
{
    return m_data.size();
}


template <typename T>
Matrix<T>::MatrixRow::reference Matrix<T>::MatrixRow::operator[](size_type col)
{
    if (col >= m_data.size())
        throw std::out_of_range(MATRIX_COL_INDEX_OUT_OF_RANGE_ERROR);

    return m_data[col];
}


template <typename T>
Matrix<T>::MatrixRow::const_reference Matrix<T>::MatrixRow::operator[](size_type col) const
{
    if (col >= m_data.size())
        throw std::out_of_range(MATRIX_COL_INDEX_OUT_OF_RANGE_ERROR);

    return m_data[col];
}


// ===============================
//          Конструкторы
// ===============================


template <typename T>
Matrix<T>::Matrix() : m_rows(0), m_cols(0), m_data(nullptr)
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);
}


template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols) : m_rows(rows), m_cols(cols), m_data(std::make_unique<value_type[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        reset_matrix();
}


template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols, const_reference value) : m_rows(rows), m_cols(cols), m_data(std::make_unique<value_type[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        reset_matrix();
    else 
        std::fill(m_data.get(), m_data.get() + rows * cols, value);
}


template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>> init_list) : Matrix(init_list.size(), (init_list.size() > 0 ? init_list.begin()->size() : 0))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0) 
        return;

    for (const auto& row : init_list) 
    {
        if (row.size() != m_cols) 
        {
            reset_matrix();
            throw std::invalid_argument(MATRIX_INITIALIZER_LIST_CONSTRUCTOR_ERROR);
        }
    }

    size_type row_idx = 0;
    for (const auto& row : init_list) 
    {
        std::copy(row.begin(), row.end(), m_data.get() + row_idx * m_cols);
        row_idx++;
    }
}


template <typename T>
Matrix<T>::Matrix(const Matrix &other_matrix) : Matrix(other_matrix.m_rows, other_matrix.m_cols)
{
    if (m_data)
        std::copy(other_matrix.m_data.get(), other_matrix.m_data.get() + m_rows * m_cols, m_data.get());
}


template <typename T>
Matrix<T>::Matrix(Matrix &&other_matrix) noexcept : m_rows(other_matrix.m_rows), m_cols(other_matrix.m_cols), m_data(std::move(other_matrix.m_data))
{
    other_matrix.m_rows = 0;
    other_matrix.m_cols = 0;
}


template <typename T>
void Matrix<T>::reset_matrix()
{
    m_rows = 0;
    m_cols = 0;
    m_data.reset();
}


// ===============================
//       Операторы доступа
// ===============================


template <typename T>
Matrix<T>::MatrixRow Matrix<T>::operator[](size_type row)
{
    if (row >= m_rows)
        throw std::out_of_range(MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);

    return MatrixRow(std::span<T>(m_data.get() + row * m_cols, m_cols));
}


template <typename T>
const Matrix<T>::MatrixRow Matrix<T>::operator[](size_type row) const
{
    if (row >= m_rows)
        throw std::out_of_range(MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);

    return MatrixRow(std::span<T>(m_data.get() + row * m_cols, m_cols));
}


template <typename T>
Matrix<T>::reference Matrix<T>::operator()(size_type row, size_type col)
{
    if (row >= m_rows || col >= m_cols)
        throw std::out_of_range(MATRIX_INDEX_OUT_OF_RANGE_ERROR);

    return m_data[row * m_cols + col];
}


template <typename T>
Matrix<T>::const_reference Matrix<T>::operator()(size_type row, size_type col) const
{
    if (row >= m_rows || col >= m_cols)
        throw std::out_of_range(MATRIX_INDEX_OUT_OF_RANGE_ERROR);

    return m_data[row * m_cols + col];
}


// ===============================
//           Вместимость
// ===============================


template <typename T>
Matrix<T>::size_type Matrix<T>::rows() const noexcept
{
    return m_rows;
}


template <typename T>
Matrix<T>::size_type Matrix<T>::cols() const noexcept
{
    return m_cols;
}


template <typename T>
Matrix<T>::size_type Matrix<T>::size() const noexcept
{
    return m_rows * m_cols;
}


template <typename T>
bool Matrix<T>::empty() const noexcept
{
    return m_rows == 0 || m_cols == 0;
}


// ===============================
//    Математические операторы
// ===============================


template <typename T>
Matrix<T>& Matrix<T>::operator += (const Matrix& other_matrix)
{
    if (m_rows != other_matrix.m_rows || m_cols != other_matrix.m_cols)
        throw std::invalid_argument(MATRIX_UNARY_ADD_SUB_ERR);

    for (size_type i = 0; i < m_rows * m_cols; i++)
        m_data[i] += other_matrix.m_data[i];

    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator -= (const Matrix &other_matrix)
{
    if (m_rows != other_matrix.m_rows || m_cols != other_matrix.m_cols)
        throw std::invalid_argument(MATRIX_UNARY_ADD_SUB_ERR);

    for (size_type i = 0; i < m_rows * m_cols; i++)
        m_data[i] -= other_matrix.m_data[i];

    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator *= (const Matrix &other_matrix)
{
    Matrix<T> result_matrix(m_rows, other_matrix.m_cols, 0);

    for (size_type i = 0; i < m_rows; i++)
        for (size_type j = 0; j < other_matrix.m_cols; j++)
            for (size_type k = 0; k < m_cols; k++)
                // TODO доделать операторы доступа

    *this = std::move(result_matrix);
    
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator *= (const_reference number)
{
    for (size_type i = 0; i < m_rows * m_cols; i++)
        m_data[i] *= number;

    return *this;
}


template <typename T>
Matrix<T> operator + (Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs += rhs;
    return lhs;
}


template <typename T>
Matrix<T> operator - (Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs -= rhs;
    return rhs;
}


template <typename T>
Matrix<T> operator * (Matrix<T> lhs, const T& number)
{
    lhs *= number;
    return lhs;
}


template <typename T>
Matrix<T> operator * (const T& number, Matrix<T> rhs)
{
    rhs *= number;
    return rhs;
}


template <typename T>
Matrix<T> operator * (Matrix<T> lhs, const Matrix<T>& rhs)
{
    lhs *= rhs;
    return lhs;
}