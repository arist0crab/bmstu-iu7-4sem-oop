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
        clear();
}


template <typename T>
Matrix<T>::Matrix(size_type rows, size_type cols, const_reference value) : m_rows(rows), m_cols(cols), m_data(std::make_unique<value_type[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        clear();
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
            clear();
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
typename Matrix<T>::reference Matrix<T>::operator=(Matrix<T> other) noexcept
{
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
    std::swap(m_data, other.m_data);

    return *this;
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
bool Matrix<T>::is_empty() const noexcept
{
    return m_rows == 0 || m_cols == 0;
}


// ===============================
//          Модификаторы
// ===============================


template <typename T>
void Matrix<T>::clear() noexcept
{
    m_rows = 0;
    m_cols = 0;
    m_data.reset();
}


template <typename T>
void Matrix<T>::swap(Matrix &other_matrix)
{
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
    std::swap(m_data, other.m_data);
}


template <typename T>
void Matrix<T>::resize(size_type new_rows, size_type new_cols)
{
    if (new_rows == m_rows || new_cols == m_cols)
        return;

    auto new_data = std::make_unique<T[]>(new_rows * new_cols);

    size_type min_rows = std::min(m_rows, new_rows);
    size_type min_cols = std::min(m_cols, new_cols);

    for (size_type i = 0; i < min_rows; i++)
        std::copy(m_data.get() + i * m_cols, m_data.get() + i * m_cols + min_cols, new_data.get() + i * new_cols);

    if (new_rows * new_cols > min_rows * min_cols)
        std::fill(new_data.get() + min_rows * new_cols, new_data.get() + new_rows * new_cols, T{});

    m_data = std::move(new_data);
    m_rows = new_cols;
    m_cols = new_cols;
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


// ===============================
//       Операторы сравнения
// ===============================


template <typename T>
bool Matrix<T>::operator == (const Matrix &other_matrix) const
{
    return equal(other_matrix);
}


template <typename T>
bool Matrix<T>::operator != (const Matrix &other_matrix) const
{
    return not_equal(other_matrix);
}


template <typename T>
bool Matrix<T>::operator < (const Matrix &other_matrix) const
{
    return less(other_matrix);
}


template <typename T>
bool Matrix<T>::operator <= (const Matrix &other_matrix) const
{
    return less_equal(other_matrix);
}


template <typename T>
bool Matrix<T>::operator > (const Matrix &other_matrix) const
{
    return greater(other_matrix);
}


template <typename T>
bool Matrix<T>::operator >= (const Matrix &other_matrix) const
{
    return greater_equal(other_matrix);
}


template <typename T>
bool Matrix<T>::equal(const Matrix &other_matrix) const
{
    if (m_rows != other_matrix.m_rows || m_cols != other_matrix.m_cols)
        return false;

    return std::equal(begin(), end(), other_matrix.begin());
}


template <typename T>
bool Matrix<T>::not_equal(const Matrix& other_matrix) const
{
    return !equal(other_matrix);
}


template <typename T>
bool Matrix<T>::less(const Matrix& other_matrix) const
{
    if (m_rows != other_matrix.m_rows || m_cols != other_matrix.m_cols)
        return size() < other_matrix.size();

    return std::lexicographical_compare(begin(), end(), other_matrix.begin(), other_matrix.end());
}


template <typename T>
bool Matrix<T>::less_equal(const Matrix& other_matrix) const
{
    return less(other_matrix) || equal(other_matrix);
}


template <typename T>
bool Matrix<T>::greater(const Matrix& other_matrix) const
{
    return other_matrix.less(*this);
}


template <typename T>
bool Matrix<T>::greater_equal(const Matrix& other_matrix) const
{
    return !less(other_matrix);
}


// ===============================
//  Операторы управления потоками
// ===============================


template <typename T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& matrix)
{
    if (matrix.get_rows() == 0 || matrix.get_cols() == 0)
        return os << "[]";

    os << "[ ";
    for (Matrix<T>::size_type i = 0; i < matrix.get_rows(); i++)
    {
        os << "[ ";
        for (Matrix<T>::size_type j = 0; j < matrix.get_cols(); j++)
        {
            os << matrix(i, j);
            if (j < matrix.get_cols() - 1)
                os << ", ";
        }
        os << " ]";
        if (i < matrix.get_rows() - 1)
            os << ", ";
    }
    os << " ]";

    return os;
}


template <typename T>
std::istream& operator >> (std::istream& is, Matrix<T>& matrix)
{
    if (!expect_char(is, '['))
        return is;

    for (Matrix<T>::size_type i = 0; i < matrix.get_rows(); i++)
    {
        if (!read_matrix_row(is, matrix, i))
            return is;

        if (i < matrix.get_rows() - 1)
            if (!expect_char(is, ','))
                return is;
    }

    expect_char(is, ']');
    return is;
}


template <typename T>
bool Matrix<T>::expect_char(std::istream& is, char expected)
{
    char actual;
    if (!(is >> actual) || actual != expected)
    {
        is.setstate(std::ios::failbit);
        return false;
    }

    return true;
}


template <typename T>
bool Matrix<T>::read_matrix_row(std::istream& is, reference matrix, size_type row_idx)
{
    if (!expect_char(is, '['))
        return false;

    for (Matrix<T>::size_type j = 0; j < matrix.get_cols(); j++)
    {
        if (!(is >> matrix(row_idx, j)))
            return false;

        if (j < matrix.get_cols() - 1)
            if (!expect_char(is, ','))
                return false;
    }

    return expect_char(is, ']');
}


// ===============================
//          Методы матрицы
// ===============================


template <typename T>
Matrix<T> Matrix<T>::inverse() const
{
    if (is_empty()) 
        throw std::invalid_argument(MATRIX_EMPTY_ERROR);

    if (!is_square()) 
        throw std::invalid_argument(MATRIX_SQUARE_ERROR);

    size_type n = m_rows;
    Matrix<T> aug = *this;    
    Matrix<T> inv = identity(n);   

    for (size_type i = 0; i < n; ++i)
    {
        size_type pivot = aug.find_pivot(i);
        if (std::abs(aug(pivot, i)) < 1e-9)
            throw std::runtime_error(MATRIX_SINGULAR_ERROR);

        aug.swap_rows(i, pivot);
        inv.swap_rows(i, pivot);

        T factor = 1.0 / aug(i, i);MATRIX_SINGULAR_ERROR
        aug.scale_row(i, factor);
        inv.scale_row(i, factor);

        aug.eliminate_column(i, inv);
    }

    return inv;
}


template <typename T>
Matrix<T>::size_type Matrix<T>::find_pivot(size_type column) const
{
    size_type pivot = column;
    for (size_type j = column + 1; j < m_rows; ++j)
    {
        if (std::abs((*this)(j, column)) > std::abs((*this)(pivot, column)))
            pivot = j;
    }
    return pivot;
}


template <typename T>
void Matrix<T>::eliminate_column(size_type pivot_idx, reference extra_matrix)
{
    for (size_type k = 0; k < m_rows; ++k)
    {
        if (k != pivot_idx)
        {
            T multiplier = -(*this)(k, pivot_idx);
            this->transform_rows(k, pivot_idx, multiplier, extra_matrix);
        }
    }
}


template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    if (is_empty())
        throw std::invalid_argument(MATRIX_EMPTY_ERROR);

    Matrix<T> result(m_cols, m_rows);

    for (Matrix<T>::size_type i = 0; i < m_rows; i++)
        for (Matrix<T>::size_type j = 0; j < m_cols; j++)
            result(j, i) = (*this)(i, j);

    return result;
}


template <typename T>
Matrix<T> Matrix<T>::pow(size_type exp) const
{
    if (is_empty())
        throw std::invalid_argument(MATRIX_EMPTY_ERROR);

    if (!is_square())
        throw std::invalid_argument(MATRIX_EXPONENTATION_ERROR);

    if (exp == 0)
        return identity(m_rows);

    Matrix<T> result = identity(m_rows);
    Matrix<T> base = *this;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = result * base;
            
        base = base * base;
        exp /= 2;
    }

    return result;
}


template <typename T>
T Matrix<T>::trace() const
{
    if (is_empty)
        throw std::invalid_argument(MATRIX_EMPTY_ERROR);

    if (!is_square())
        throw std::invalid_argument(MATRIX_TRACE_ERROR);

    T sum = 0;
    for (size_type i = 0; i < m_rows; i++)
        sum += (*this)(i, i);

    return sum;
}


template <typename T>
T Matrix<T>::determinant() const
{

}


template <typename T>
bool Matrix<T>::is_square() const noexcept
{
    return (m_rows == m_cols);
}


template <typename T>
bool Matrix<T>::is_symmetric() const noexcept
{
    if (!is_square() || is_empty())
        return false;

    for (Matrix<T>::size_type i = 0; i < m_rows; i++)
        for (Matrix<T>::size_type j = i + 1; j < m_cols; j++)
            if ((*this)(i, j) != (*this)(j, i))
                return false;

    return true;
}


template <typename T>
bool Matrix<T>::is_diagonal() const noexcept
{
    if (!is_square() || is_empty())
        return false;

    for (Matrix<T>::size_type i = 0; i < m_rows; i++)
        for (Matrix<T>::size_type j = 0; j < m_cols; j++)
            if (i != j && (*this)(i, j) != 0)
                return false;

    return true;
}


template <typename T>
bool Matrix<T>::is_identity() const noexcept
{
    if (!is_square() || is_empty())
        return false;

    for (Matrix<T>::size_type i = 0; i < m_rows; i++)
    {
        for (Matrix<T>::size_type j = 0; j < m_cols; j++)
        {
            if (i != j && (*this)(i, j) != 0)
                return false;
            if (i == j && (*this)(i, j) != 1)
                return false;
        }
    }

    return true;
}


template <typename T>
Matrix<T>::size_type Matrix<T>::rank() const
{

}


template <typename T>
Matrix<T> Matrix<T>::identity(Matrix<T>::size_type size) noexcept
{
    Matrix<T> res(size, size, 0);

    for (Matrix<T>::size_type i = 0; i < size; i++)
        res(i, i) = 1;

    return res;
}


template <typename T>
Matrix<T> Matrix<T>::random(Matrix<T>::size_type rows, Matrix<T>::size_type cols, T min_val, T max_val) noexcept
{
    Matrix<T> res(rows, cols);
    
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_floating_point_v<T>)
    {
        std::uniform_real_distribution<T> dist(min_val, max_val);
        for (Matrix<T>::size_type i = 0; i < rows * cols; ++i)
            res.m_data[i] = dist(gen);
    }
    else
    {
        std::uniform_int_distribution<T> dist(min_val, max_val);
        for (Matrix<T>::size_type i = 0; i < rows * cols; ++i)
            res.m_data[i] = dist(gen);
    }

    return res;
}