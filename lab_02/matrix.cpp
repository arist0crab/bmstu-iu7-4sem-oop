#include "matrix.hpp"


static bool expect_char(std::istream& is, char expected);

// ===============================
//         MatrixRow
// ===============================

template <MatrixElement T>
Matrix<T>::MatrixRow::MatrixRow(std::span<T> data) : m_data(data) {}

template <MatrixElement T>
Matrix<T>::MatrixRow::size_type Matrix<T>::MatrixRow::size() const noexcept
{
    return m_data.size();
}

template <MatrixElement T>
Matrix<T>::MatrixRow::reference Matrix<T>::MatrixRow::operator[](size_type col)
{
    if (col >= m_data.size())
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_COL_INDEX_OUT_OF_RANGE_ERROR);

    return m_data[col];
}

template <MatrixElement T>
Matrix<T>::MatrixRow::const_reference Matrix<T>::MatrixRow::operator[](size_type col) const
{
    if (col >= m_data.size())
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_COL_INDEX_OUT_OF_RANGE_ERROR);

    return m_data[col];
}

// ===============================
//         Конструкторы
// ===============================

template <MatrixElement T>
Matrix<T>::Matrix() : m_rows(0), m_cols(0), m_data(nullptr)
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);
}

template <MatrixElement T>
Matrix<T>::Matrix(size_type rows, size_type cols) : m_rows(rows), m_cols(cols), m_data(std::make_shared<value_type[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        clear();
}

template <MatrixElement T>
Matrix<T>::Matrix(size_type rows, size_type cols, const_reference value) : m_rows(rows), m_cols(cols), m_data(std::make_shared<value_type[]>(rows * cols))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0)
        clear();
    else 
        std::ranges::fill(std::span(m_data.get(), m_rows * m_cols), value);
}

template <MatrixElement T>
Matrix<T>::Matrix(size_type rows, size_type cols, T** c_matrix) : m_rows(rows), m_cols(cols)
{
    if (!c_matrix)
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_C_MATRIX_DOESNT_EXIST_ERROR); 
    
    m_data = std::make_shared<T[]>(m_rows * m_cols);
    auto indices = std::views::iota(size_type{0}, m_rows * m_cols);
    std::ranges::transform(indices, m_data.get(), [c_matrix, cols](auto idx) {
        return c_matrix[idx / cols][idx % cols];
    });
}

template<MatrixElement T>
template <ConvertibleInputIterator<T> It, Sentinel<It> Sent>
Matrix<T>::Matrix(size_type rows, size_type cols, It begin, Sent end) : m_rows(rows), m_cols(cols), m_data(std::make_shared<value_type[]>(rows * cols))
{
    auto res = std::ranges::copy(std::ranges::subrange(begin, end) | std::views::take(rows * cols), m_data.get());
    
    if (static_cast<size_type>(res.out - m_data.get()) < rows * cols)
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ITERATOR_CONSTRUCTOR_ERROR);
}

template <MatrixElement T>
template <std::ranges::input_range R>
Matrix<T>::Matrix(size_type rows, size_type cols, R&& range) : m_rows(rows), m_cols(cols), m_data(std::make_shared<value_type[]>(rows * cols))
{
    auto total_size = rows * cols;
    auto taken = range | std::views::take(total_size);
    
    auto res = std::ranges::transform(taken, m_data.get(), [](const auto& val) {
        return static_cast<value_type>(val);
    });
    
    if (static_cast<size_type>(res.out - m_data.get()) < total_size)
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ITERATOR_CONSTRUCTOR_ERROR);
}

template <MatrixElement T>
template <CommonContainer<T> Container>
Matrix<T>::Matrix(size_type rows, size_type cols, const Container& container) : m_rows(rows), m_cols(cols)
{
    m_data = std::make_shared<T[]>(m_rows * m_cols);
    std::ranges::copy(container | std::views::take(m_rows * m_cols), m_data.get());
}

template <MatrixElement T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>> init_list) : Matrix(init_list.size(), (init_list.size() > 0 ? init_list.begin()->size() : 0))
{
    static_assert(MatrixElement<T>, MATRIX_ELEMENT_TYPE_ERROR);

    if (m_rows == 0 || m_cols == 0) 
        return;

    bool all_match = std::ranges::all_of(init_list, [this](const auto& row) { return row.size() == m_cols; });
    if (!all_match) 
    {
        clear();
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_INITIALIZER_LIST_CONSTRUCTOR_ERROR);
    }

    std::ranges::transform(
        std::views::enumerate(init_list),
        std::ranges::begin(std::views::iota(size_type{0}, m_rows)),
        [this](const auto& item) {
            const auto& [row_idx, row] = item;
            std::ranges::copy(row, m_data.get() + row_idx * m_cols);
            return row_idx;
        }
    );
}

template <MatrixElement T>
Matrix<T>::Matrix(const Matrix &other_matrix) : Matrix(other_matrix.m_rows, other_matrix.m_cols)
{
    if (m_data)
        std::ranges::copy(std::span(other_matrix.m_data.get(), m_rows * m_cols), m_data.get());
}

template <MatrixElement T>
Matrix<T>::Matrix(Matrix &&other_matrix) noexcept : m_rows(other_matrix.m_rows), m_cols(other_matrix.m_cols), m_data(std::move(other_matrix.m_data))
{
    other_matrix.m_rows = 0;
    other_matrix.m_cols = 0;
}


template <MatrixElement T>
template <ConvertibleTo<T> U>
Matrix<T>::Matrix(Matrix<U> &&other_matrix) noexcept : m_rows(other_matrix.rows()), m_cols(other_matrix.cols()), m_data(std::make_shared<T[]>(other_matrix.rows() * other_matrix.cols()))
{
    std::ranges::transform(
        std::views::iota(size_type{0}, m_rows * m_cols),
        m_data.get(),
        [&](size_type i) {
            return T(other_matrix(i / m_cols, i % m_cols));
        }
    );
    
    other_matrix.clear();
}

template <MatrixElement T>
template <ConvertibleTo<T> U>
Matrix<T>::Matrix(const Matrix<U> &other_matrix) : m_rows(other_matrix.rows()), m_cols(other_matrix.cols()), m_data(std::make_shared<T[]>(other_matrix.rows() * other_matrix.cols()))
{
    std::ranges::transform(
        std::views::iota(size_type{0}, m_rows * m_cols),
        m_data.get(),
        [&](size_type i) {
            return T(other_matrix(i / m_cols, i % m_cols));
        }
    );
}

template <MatrixElement T>
template <MatrixElement U>
requires ConvertibleTo<U, T>
Matrix<T>& Matrix<T>::operator = (const Matrix<U>& other_matrix)
{
    if (this == reinterpret_cast<const Matrix<T>*>(&other_matrix))
        return *this;
    
    m_rows = other_matrix.rows();
    m_cols = other_matrix.cols();
    m_data = std::make_shared<T[]>(m_rows * m_cols);
    
    std::ranges::transform(
        std::views::iota(size_type{0}, m_rows * m_cols),
        m_data.get(),
        [&](size_type i) {
            return T(other_matrix(i / m_cols, i % m_cols));
        }
    );
    
    return *this;
}

template <MatrixElement T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T> &other_matrix)
{
    if (this != &other_matrix)
    {
        Matrix<T> temp(other_matrix);
        this->swap(temp);
    }
    return *this;
}

template <MatrixElement T>
Matrix<T>& Matrix<T>::operator = (Matrix<T> &&other_matrix)
{
    if (this != &other_matrix)
        this->swap(other_matrix); 
    return *this;
}

// ===============================
//         Итераторы
// ===============================

template <MatrixElement T>
typename Matrix<T>::iterator Matrix<T>::begin() noexcept { return iterator(m_data, 0); }

template <MatrixElement T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const noexcept { return const_iterator(m_data, 0); }

template <MatrixElement T>
typename Matrix<T>::const_iterator Matrix<T>::cbegin() const noexcept { return begin(); }

template <MatrixElement T>
typename Matrix<T>::iterator Matrix<T>::end() noexcept { return iterator(m_data, m_rows * m_cols); }

template <MatrixElement T>
typename Matrix<T>::const_iterator Matrix<T>::end() const noexcept { return const_iterator(m_data, m_rows * m_cols); }

template <MatrixElement T>
typename Matrix<T>::const_iterator Matrix<T>::cend() const noexcept { return end(); }

template <MatrixElement T>
typename Matrix<T>::reverse_iterator Matrix<T>::rbegin() noexcept { return reverse_iterator(end()); }

template <MatrixElement T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::rbegin() const noexcept { return const_reverse_iterator(end()); }

template <MatrixElement T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::crbegin() const noexcept { return rbegin(); }

template <MatrixElement T>
typename Matrix<T>::reverse_iterator Matrix<T>::rend() noexcept { return reverse_iterator(begin()); }

template <MatrixElement T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::rend() const noexcept { return const_reverse_iterator(begin()); }

template <MatrixElement T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::crend() const noexcept { return rend(); }

// ===============================
//       Операторы доступа
// ===============================

template <MatrixElement T>
Matrix<T>::MatrixRow Matrix<T>::operator[](size_type row)
{
    if (row >= m_rows)
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);
    return MatrixRow(std::span<T>(m_data.get() + row * m_cols, m_cols));
}

template <MatrixElement T>
const Matrix<T>::MatrixRow Matrix<T>::operator[](size_type row) const
{
    if (row >= m_rows)
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);
    return MatrixRow(std::span<T>(m_data.get() + row * m_cols, m_cols));
}

template <MatrixElement T>
Matrix<T>::reference Matrix<T>::operator()(size_type row, size_type col)
{
    if (row >= m_rows || col >= m_cols)
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_INDEX_OUT_OF_RANGE_ERROR);
    return m_data[row * m_cols + col];
}

template <MatrixElement T>
Matrix<T>::const_reference Matrix<T>::operator()(size_type row, size_type col) const
{
    if (row >= m_rows || col >= m_cols)
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_INDEX_OUT_OF_RANGE_ERROR);
    return m_data[row * m_cols + col];
}

// ===============================
//            Вместимость
// ===============================

template <MatrixElement T> Matrix<T>::size_type Matrix<T>::rows() const noexcept { return m_rows; }
template <MatrixElement T> Matrix<T>::size_type Matrix<T>::cols() const noexcept { return m_cols; }
template <MatrixElement T> Matrix<T>::size_type Matrix<T>::size() const noexcept { return m_rows * m_cols; }
template <MatrixElement T> bool Matrix<T>::is_empty() const noexcept { return m_rows == 0 || m_cols == 0; }

// ===============================
//          Модификаторы
// ===============================

template <MatrixElement T>
void Matrix<T>::clear() noexcept
{
    m_rows = 0;
    m_cols = 0;
    m_data.reset();
}

template <MatrixElement T>
void Matrix<T>::swap(Matrix &other_matrix)
{
    std::swap(m_rows, other_matrix.m_rows);
    std::swap(m_cols, other_matrix.m_cols);
    std::swap(m_data, other_matrix.m_data);
}

template <MatrixElement T>
void Matrix<T>::resize(size_type new_rows, size_type new_cols)
{
    if (new_rows == m_rows && new_cols == m_cols) return;

    auto new_data = std::make_shared<T[]>(new_rows * new_cols);
    std::ranges::fill(std::span(new_data.get(), new_rows * new_cols), T{});

    size_type min_cols = std::min(m_cols, new_cols);

    auto source_rows = std::views::iota(size_type{0}, std::min(m_rows, new_rows));
    
    std::ranges::transform(
        source_rows,
        std::ranges::begin(source_rows),
        [&](size_type i) {
            std::ranges::copy(
                std::span(m_data.get() + i * m_cols, min_cols),
                new_data.get() + i * new_cols
            );
            return i;
        }
    );

    m_data = std::move(new_data);
    m_rows = new_rows;
    m_cols = new_cols;
}

// ===============================
//    Математические операторы
// ===============================

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::operator += (const Matrix<U>& other_matrix)
{
    return add(other_matrix);
}

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::operator -= (const Matrix<U>& other_matrix)
{
    return sub(other_matrix);
}

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::operator *= (const Matrix<U>& other_matrix)
{
    return mult(other_matrix);
}

template <MatrixElement T>
Matrix<T>& Matrix<T>::operator *= (const_reference number)
{
    return mult_scalar(number);
}

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::operator &= (const Matrix<U>& other_matrix)
{
    return mult_hadamard(other_matrix);
}

template <MatrixElement T, MatrixElement U>
requires HasCommon<T, U> && SameSizeMatrices<Matrix<T>, Matrix<U>>
auto operator + (const Matrix<T>& lhs, const Matrix<U>& rhs)
{
    using CommonType = std::common_type_t<T, U>;
    Matrix<CommonType> result = lhs;
    result += rhs;
    return result;
}

template <MatrixElement T, MatrixElement U>
requires HasCommon<T, U> && SameSizeMatrices<Matrix<T>, Matrix<U>>
auto operator - (const Matrix<T>& lhs, const Matrix<U>& rhs)
{
    using CommonType = std::common_type_t<T, U>;
    Matrix<CommonType> result = lhs;
    result -= rhs;
    return result;
}

template <MatrixElement T, ArithmeticScalar U>
requires HasCommon<T, U>
auto operator * (const Matrix<T>& lhs, const U& number)
{
    using CommonType = std::common_type_t<T, U>;
    Matrix<CommonType> result = lhs;
    result *= number;
    return result;
}

template <ArithmeticScalar T, MatrixElement U>
requires HasCommon<T, U>
auto operator * (const T& number, const Matrix<U>& rhs)
{
    using CommonType = std::common_type_t<T, U>;
    Matrix<CommonType> result = rhs;
    result *= number;
    return result;
}

template <MatrixElement T, MatrixElement U>
requires HasCommon<T, U> && MultipliableMatrices<Matrix<T>, Matrix<U>>
auto operator * (const Matrix<T>& lhs, const Matrix<U>& rhs)
{
    using CommonType = std::common_type_t<T, U>;
    Matrix<CommonType> result(lhs.rows(), lhs.cols());
    result = lhs;
    result *= rhs;
    return result;
}

// ===============================
//       Операторы сравнения
// ===============================

template <MatrixElement T>
template <MatrixElement U>
requires EqualityComparable<T, U>
auto Matrix<T>::operator<=>(const Matrix<U>& other) const
{
    if (m_rows != other.rows() || m_cols != other.cols())
        return m_rows * m_cols <=> other.rows() * other.cols();
    
    auto mismatch = std::ranges::mismatch(
        std::views::iota(size_type{0}, m_rows * m_cols),
        std::views::iota(size_type{0}, m_rows * m_cols),
        [&](size_type idx1, size_type idx2) {
            return (*this)(idx1 / m_cols, idx1 % m_cols) == other(idx2 / m_cols, idx2 % m_cols);
        }
    );
    
    if (mismatch.in1 == std::ranges::end(std::views::iota(size_type{0}, m_rows * m_cols)))
        return std::strong_ordering::equal;
    
    size_type idx = *mismatch.in1;
    return (*this)(idx / m_cols, idx % m_cols) <=> other(idx / m_cols, idx % m_cols);
}

template <MatrixElement T>
auto Matrix<T>::operator<=>(const Matrix &other) const
{
    if (auto cmp = m_rows <=> other.m_rows; cmp != 0)
        return cmp;
    
    if (auto cmp = m_cols <=> other.m_cols; cmp != 0)
        return cmp;
    
    auto mismatch = std::ranges::mismatch(
        std::views::iota(size_type{0}, m_rows * m_cols),
        std::views::iota(size_type{0}, m_rows * m_cols),
        [&](size_type idx1, size_type idx2) {
            return (*this)(idx1 / m_cols, idx1 % m_cols) == other(idx2 / m_cols, idx2 % m_cols);
        }
    );
    
    if (mismatch.in1 == std::ranges::end(std::views::iota(size_type{0}, m_rows * m_cols)))
        return std::strong_ordering::equal;
    
    size_type idx = *mismatch.in1;
    return (*this)(idx / m_cols, idx % m_cols) <=> other(idx / m_cols, idx % m_cols);
}

template <MatrixElement T>
bool Matrix<T>::equal(const Matrix &other_matrix) const
{
    if (m_rows != other_matrix.m_rows || m_cols != other_matrix.m_cols) return false;
    return std::ranges::equal(*this, other_matrix);
}

// ===============================
//  Управление потоками
// ===============================

template <MatrixElement T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& matrix)
{
    if (matrix.is_empty()) return os << "[]";

    os << "[ ";

    auto rows_indices = std::views::iota(size_t{0}, matrix.rows());
    std::ranges::for_each(rows_indices, [&](auto i) {
        if (i > 0) os << ", ";
        os << "[ ";
        auto cols_indices = std::views::iota(size_t{0}, matrix.cols());
        std::ranges::for_each(cols_indices, [&](auto j) {
            if (j > 0) os << ", ";
            os << matrix(i, j);
        });
        os << " ]";
    });

    return os << " ]";
}

template <MatrixElement T>
std::istream& operator >> (std::istream& is, Matrix<T>& matrix)
{
    if (!Matrix<T>::expect_char(is, '['))
        return is;

    auto row_indices = std::views::iota(typename Matrix<T>::size_type{0}, matrix.rows());
    
    auto result = std::ranges::all_of(row_indices, [&](typename Matrix<T>::size_type i) {
        if (!Matrix<T>::read_matrix_row(is, matrix, i))
            return false;

        if (i < matrix.rows() - 1)
            if (!Matrix<T>::expect_char(is, ','))
                return false;
        
        return true;
    });

    if (!result)
        return is;

    Matrix<T>::expect_char(is, ']');
    return is;
}

template <MatrixElement T>
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

template <MatrixElement T>
bool Matrix<T>::read_matrix_row(std::istream& is, reference matrix, size_type row_idx)
{
    if (!expect_char(is, '['))
        return false;

    auto col_indices = std::views::iota(size_type{0}, matrix.cols());
    
    auto result = std::ranges::all_of(col_indices, [&](size_type j) {
        if (!(is >> matrix(row_idx, j)))
            return false;

        if (j < matrix.cols() - 1)
            if (!expect_char(is, ','))
                return false;
        
        return true;
    });

    if (!result)
        return false;

    return expect_char(is, ']');
}

// ===============================
//          Методы матрицы
// ===============================

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::add(const Matrix<U>& other_matrix)
{
    if (m_rows != other_matrix.rows() || m_cols != other_matrix.cols())
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_SAME_DIMENSIONS_ERROR);

    std::ranges::transform(
        std::views::iota(size_type{0}, m_rows * m_cols),
        m_data.get(),
        m_data.get(),
        [&](size_type i) {
            return m_data[i] + static_cast<T>(other_matrix(i / m_cols, i % m_cols));
        }
    );

    return *this;
}

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::sub(const Matrix<U>& other_matrix)
{
    if (m_rows != other_matrix.rows() || m_cols != other_matrix.cols())
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_SAME_DIMENSIONS_ERROR);

    std::ranges::transform(
        std::views::iota(size_type{0}, m_rows * m_cols),
        m_data.get(),
        m_data.get(),
        [&](size_type i) {
            return m_data[i] - static_cast<T>(other_matrix(i / m_cols, i % m_cols));
        }
    );

    return *this;
}

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::mult(const Matrix<U>& other_matrix)
{
    if (m_cols != other_matrix.rows())
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_MULTIPLICATION_ERROR);

    Matrix<T> result_matrix(m_rows, other_matrix.cols(), T{});

    auto flat_indices = std::views::iota(size_type{0}, m_rows * other_matrix.cols());
    auto k_indices = std::views::iota(size_type{0}, m_cols);

    std::ranges::transform(
        flat_indices,
        result_matrix.m_data.get(),
        [&](size_type idx) {
            size_type i = idx / other_matrix.cols();
            size_type j = idx % other_matrix.cols();
            return std::transform_reduce(
                k_indices.begin(),
                k_indices.end(),
                T{},
                std::plus{},
                [&](size_type k) {
                    return (*this)(i, k) * static_cast<T>(other_matrix(k, j));
                }
            );
        }
    );

    *this = std::move(result_matrix);
    return *this;
}

template <MatrixElement T>
Matrix<T>& Matrix<T>::mult_scalar(const_reference number)
{
    std::ranges::transform(
        std::span<T>(m_data.get(), m_rows * m_cols),
        m_data.get(),
        [&](const_reference value) {
            return value * number;
        }
    );

    return *this;
}

template <MatrixElement T>
template <MatrixElement U>
requires HasCommon<T, U>
Matrix<T>& Matrix<T>::mult_hadamard(const Matrix<U>& other_matrix)
{
    if (m_rows != other_matrix.rows() || m_cols != other_matrix.cols())
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_SAME_DIMENSIONS_ERROR);

    std::ranges::transform(
        std::views::iota(size_type{0}, m_rows * m_cols),
        m_data.get(),
        m_data.get(),
        [&](size_type i) {
            return m_data[i] * static_cast<T>(other_matrix(i / m_cols, i % m_cols));
        }
    );

    return *this;
}

template <MatrixElement T>
std::shared_ptr<BaseMatrix> Matrix<T>::inverse() const
{
    if (is_empty()) 
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_EMPTY_ERROR);

    if (!is_square()) 
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_SQUARE_ERROR);

    size_type n = m_rows;
    Matrix<T> aug(*this);    
    Matrix<T> inv = identity(n);   

    auto row_indices = std::views::iota(size_type{0}, n);
    
    std::ranges::all_of(row_indices, [&](size_type i) {
        size_type pivot = aug.find_pivot(i);
        if (std::abs(aug(pivot, i)) < 1e-9)
            throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_SINGULAR_ERROR);

        aug.swap_rows(i, pivot);
        inv.swap_rows(i, pivot);

        T factor = 1.0 / aug(i, i);
        aug.scale_row(i, factor);
        inv.scale_row(i, factor);

        aug.eliminate_column(i, inv);
        
        return true;
    });

    return std::make_shared<Matrix<T>>(std::move(inv));
}

template <MatrixElement T>
void Matrix<T>::swap_rows(size_type row1, size_type row2)
{
    if (row1 >= m_rows || row2 >= m_rows) throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);
    if (row1 == row2) return;
    std::ranges::swap_ranges(std::span(m_data.get() + row1 * m_cols, m_cols), std::span(m_data.get() + row2 * m_cols, m_cols));
}

template <MatrixElement T>
void Matrix<T>::scale_row(size_type row, value_type factor)
{
    if (row >= m_rows)
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);

    T* row_ptr = m_data.get() + row * m_cols;
    std::ranges::transform(std::span(row_ptr, m_cols), row_ptr, [factor](const T& val) { return val * factor; });
}

template <MatrixElement T>
void Matrix<T>::transform_rows(size_type target, size_type source, value_type factor, Matrix<T>& extra)
{
    if (target >= m_rows || source >= m_rows)
        throw MatrixIndexException(__FILE__, __LINE__, __FUNCTION__, MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR);
    
    auto target_span = std::span(m_data.get() + target * m_cols, m_cols);
    auto source_span = std::span(m_data.get() + source * m_cols, m_cols);
    std::ranges::transform(target_span, source_span, target_span.begin(),
        [factor](const T& t, const T& s) { return t - factor * s; });
    
    auto extra_target_span = std::span(extra.m_data.get() + target * extra.m_cols, extra.m_cols);
    auto extra_source_span = std::span(extra.m_data.get() + source * extra.m_cols, extra.m_cols);
    std::ranges::transform(extra_target_span, extra_source_span, extra_target_span.begin(),
        [factor](const T& t, const T& s) { return t - factor * s; });
}

template <MatrixElement T>
Matrix<T>::size_type Matrix<T>::find_pivot(size_type column) const
{
    auto candidates = std::views::iota(column + 1, m_rows);
    
    auto best = std::ranges::max_element(
        candidates,
        [&](size_type a, size_type b) {
            return std::abs((*this)(a, column)) < std::abs((*this)(b, column));
        }
    );
    
    if (best != std::ranges::end(candidates) && 
        std::abs((*this)(*best, column)) > std::abs((*this)(column, column)))
        return *best;
    
    return column;
}

template <MatrixElement T>
void Matrix<T>::eliminate_column(size_type pivot_idx, Matrix<T>& extra_matrix)
{
    auto k_view = std::views::iota(size_type{0}, m_rows) 
        | std::views::filter([pivot_idx](auto k) { return k != pivot_idx; });
    
    std::ranges::all_of(k_view, [&](size_type k) {
        T multiplier = -(*this)(k, pivot_idx);
        transform_rows(k, pivot_idx, multiplier, extra_matrix);
        return true;
    });
}

template <MatrixElement T>
std::shared_ptr<BaseMatrix> Matrix<T>::transpose() const
{
    if (is_empty())
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_EMPTY_ERROR);

    auto result = std::make_shared<Matrix<T>>(m_cols, m_rows);

    std::ranges::all_of(
        std::views::iota(size_type{0}, m_rows * m_cols),
        [&](size_type idx) {
            size_type i = idx / m_cols;
            size_type j = idx % m_cols;
            (*result)(j, i) = (*this)(i, j);
            return true;
        }
    );

    return result;
}

template <MatrixElement T>
Matrix<T> Matrix<T>::pow(size_type exp) const
{
    if (is_empty())
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_EMPTY_ERROR);

    if (!is_square())
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_EXPONENTATION_ERROR);

    if (exp == 0)
        return identity(m_rows);

    Matrix<T> result = identity(m_rows);
    Matrix<T> base = *this;

    std::ranges::find_if(
        std::views::iota(0),
        [&](int) {
            bool should_mult = (exp % 2 == 1);
            if (should_mult)
                result = result * base;
            base = base * base;
            exp /= 2;
            return exp == 0;
        }
    );

    return result;
}

template <MatrixElement T>
std::any Matrix<T>::trace() const
{
    if (!is_square()) throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_TRACE_ERROR);
    if (is_empty()) throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_EMPTY_ERROR);

    auto diag = std::views::iota(size_type{0}, m_rows) | std::views::transform([this](auto i) { return (*this)(i, i); });
    return std::ranges::fold_left(diag, T{0}, std::plus<T>());
}

template <MatrixElement T>
std::any Matrix<T>::determinant() const
{
    if (is_empty())
        throw MatrixException(__FILE__, __LINE__, __FUNCTION__, MATRIX_EMPTY_ERROR);

    if (!is_square())
        throw MatrixDimensionException(__FILE__, __LINE__, __FUNCTION__, MATRIX_SQUARE_ERROR);

    if (m_rows == 1)
        return (*this)(0, 0);

    if (m_rows == 2)
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);

    value_type det = value_type{};
    
    std::ranges::all_of(
        std::views::iota(size_type{0}, m_cols),
        [&](size_type col) {
            Matrix<T> minor(m_rows - 1, m_cols - 1);

            std::ranges::all_of(
                std::views::iota(size_type{1}, m_rows),
                [&](size_type i) {
                    size_type minor_col = 0;
                    std::ranges::all_of(
                        std::views::iota(size_type{0}, m_cols)
                            | std::views::filter([col](size_type j) { return j != col; }),
                        [&](size_type j) {
                            minor(i - 1, minor_col) = (*this)(i, j);
                            ++minor_col;
                            return true;
                        }
                    );
                    return true;
                }
            );

            value_type sign = (col % 2 == 0) ? value_type(1) : value_type(-1);
            det += sign * (*this)(0, col) * std::any_cast<T>(minor.determinant());
            return true;
        }
    );

    return det;
}

template <MatrixElement T>
bool Matrix<T>::is_square() const noexcept
{
    return (m_rows == m_cols);
}

template <MatrixElement T>
bool Matrix<T>::is_symmetric() const noexcept
{
    if (!is_square() || is_empty())
        return false;

    auto row_indices = std::views::iota(size_type{0}, m_rows);
    
    return std::ranges::all_of(row_indices, [&](size_type i) {
        auto col_indices = std::views::iota(i + 1, m_cols);
        return std::ranges::all_of(col_indices, [&](size_type j) {
            return (*this)(i, j) == (*this)(j, i);
        });
    });
}

template <MatrixElement T>
bool Matrix<T>::is_diagonal() const noexcept
{
    if (!is_square() || is_empty())
        return false;

    return std::ranges::all_of(
        std::views::iota(size_type{0}, m_rows * m_cols),
        [this](size_type idx) {
            size_type i = idx / m_cols;
            size_type j = idx % m_cols;
            return i == j || (*this)(i, j) == 0;
        }
    );
}

template <MatrixElement T>
bool Matrix<T>::is_identity() const noexcept
{
    if (!is_square() || is_empty())
        return false;

    return std::ranges::all_of(
        std::views::iota(size_type{0}, m_rows * m_cols),
        [this](size_type idx) {
            size_type i = idx / m_cols;
            size_type j = idx % m_cols;
            return (i == j && (*this)(i, j) == 1) || (i != j && (*this)(i, j) == 0);
        }
    );
}

template <MatrixElement T>
typename Matrix<T>::size_type Matrix<T>::rank() const
{
    if (is_empty()) return 0;

    Matrix<T> temp(*this);
    size_type r = 0;

    std::ranges::all_of(
        std::views::iota(size_type{0}, m_cols),
        [&](size_type col) {
            if (r >= m_rows) return false;

            auto pivot = std::ranges::max_element(
                std::views::iota(r, m_rows),
                [&](size_type a, size_type b) {
                    return std::abs(temp(a, col)) < std::abs(temp(b, col));
                }
            );
            
            size_type pivot_idx = *pivot;

            if (std::abs(temp(pivot_idx, col)) < 1e-9)
                return true;

            temp.swap_rows(r, pivot_idx);

            std::ranges::all_of(
                std::views::iota(r + 1, m_rows),
                [&](size_type i) {
                    T factor = temp(i, col) / temp(r, col);
                    std::ranges::all_of(
                        std::views::iota(col, m_cols),
                        [&](size_type j) {
                            temp(i, j) -= factor * temp(r, j);
                            return true;
                        }
                    );
                    return true;
                }
            );
            
            r++;
            return true;
        }
    );

    return r;
}

template <MatrixElement T>
Matrix<T> Matrix<T>::identity(Matrix<T>::size_type size) noexcept
{
    Matrix<T> res(size, size, T{0});
    auto indices = std::views::iota(size_type{0}, size);
    std::ranges::for_each(indices, [&res](auto i) { res(i, i) = 1; });
    return res;
}

template <MatrixElement T>
Matrix<T> Matrix<T>::random(size_type rows, size_type cols, value_type min_val, value_type max_val) noexcept
{
    Matrix<T> res(rows, cols);
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    auto generate_val = [&]() {
        if constexpr (std::is_floating_point_v<T>) return std::uniform_real_distribution<T>(min_val, max_val)(gen);
        else return std::uniform_int_distribution<T>(min_val, max_val)(gen);
    };

    std::ranges::generate(std::span(res.m_data.get(), rows * cols), generate_val);
    return res;
}