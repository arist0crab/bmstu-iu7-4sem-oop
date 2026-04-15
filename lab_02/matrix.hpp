#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <concepts>
#include <memory>
#include <type_traits>
#include <random>
#include <span>

#define MATRIX_ELEMENT_TYPE_ERROR "Matrix element type must be copyable and destructible"
#define MATRIX_INITIALIZER_LIST_CONSTRUCTOR_ERROR "Inconsistent row lengths in initializer_list"
#define MATRIX_UNARY_ADD_SUB_ERR "Matrix dimensions must match for addition"
#define MATRIX_ROW_INDEX_OUT_OF_RANGE_ERROR "Matrix row index out of range"
#define MATRIX_COL_INDEX_OUT_OF_RANGE_ERROR "Matrix column index out of range"
#define MATRIX_INDEX_OUT_OF_RANGE_ERROR "Matrix index out of range"
#define MATRIX_EXPONENTATION_ERROR "Matrix must be square for exponentiation"
#define MATRIX_SQUARE_ERROR "Matrix must be square"
#define MATRIX_EMPTY_ERROR "Matrix must be non-empty"
#define MATRIX_TRACE_ERROR "Trace is only defined for square matrices"
#define MATRIX_SINGULAR_ERROR "Matrix is singular"

template <typename T>
concept MatrixElement = std::is_arithmetic_v<T>;


template <typename T>
class Matrix
{
    class MatrixRow
    {
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            // TODO using iterator
            // TODO using const_iterator
            // TODO using difference_type
            using size_type = std::size_t;

            size_type size() const noexcept;
            reference operator[](size_type col);
            const_reference operator[](size_type col) const;

        private:
            friend class Matrix;

            std::span<value_type> m_data;

            explicit MatrixRow(std::span<value_type> data);
    };

    public:

        // ===============================
        //        Алиасы контейнеров
        // ===============================

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        // TODO using iterator
        // TODO using const_iterator
        // TODO using difference_type
        using size_type = std::size_t;

        // ===============================
        //          Конструкторы
        // ===============================

        Matrix();
        Matrix(size_type rows, size_type cols); 
        Matrix(size_type rows, size_type cols, const_reference value);
        Matrix(std::initializer_list<std::initializer_list<value_type>> init_list);
        
        Matrix(Matrix &&other_matrix) noexcept;
        Matrix(const Matrix &other_matrix);
        ~Matrix() = default;

        reference operator = (Matrix other) noexcept;

        // ===============================
        //          Итераторы
        // ===============================

        // TODO

        // ===============================
        //       Операторы доступа
        // ===============================

        MatrixRow operator [](size_type row);
        const MatrixRow operator [](size_type row) const;
        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        // ===============================
        //           Вместимость
        // ===============================

        size_type rows() const noexcept;
        size_type cols() const noexcept;
        size_type size() const noexcept;
        bool is_empty() const noexcept;

        // ===============================
        //          Модификаторы
        // ===============================

        void clear() noexcept;
        void swap(Matrix &other_matrix);
        void resize(size_type new_rows, size_type new_cols);

        // ===============================
        //    Математические операторы
        // ===============================

        Matrix &operator -= (const Matrix &other_matrix);
        Matrix &operator += (const Matrix &other_matrix);
        Matrix &operator *= (const Matrix &other_matrix);
        Matrix &operator *= (const_reference number); 

        // ===============================
        //       Операторы сравнения
        // ===============================

        bool operator == (const Matrix &other_matrix) const;
        bool operator != (const Matrix &other_matrix) const;
        bool operator < (const Matrix &other_matrix) const;
        bool operator <= (const Matrix &other_matrix) const;
        bool operator > (const Matrix &other_matrix) const;
        bool operator >= (const Matrix &other_matrix) const;
        bool equal(const Matrix &other_matrix) const;
        bool not_equal(const Matrix& other_matrix) const;
        bool less(const Matrix& other_matrix) const;
        bool less_equal(const Matrix& other_matrix) const;
        bool greater(const Matrix& other_matrix) const;
        bool greater_equal(const Matrix& other_matrix) const;

        // ===============================
        //          Методы матрицы
        // ===============================

        Matrix<T> inverse() const;
        Matrix<T> transpose() const;
        Matrix<T> pow(size_type exp) const;

        T trace() const;
        T determinant() const;

        bool is_square() const noexcept;
        bool is_symmetric() const noexcept;
        bool is_diagonal() const noexcept;
        bool is_identity() const noexcept;

        size_type rank() const;

        static Matrix<T> identity(size_type size) noexcept;
        static Matrix<T> random(size_type rows, size_type cols, T min_val, T max_val) noexcept;

    private:
        size_type m_rows = 0;
        size_type m_cols = 0;
        std::unique_ptr<value_type[]> m_data = nullptr;

        size_type find_pivot(size_type column) const;
        void eliminate_column(size_type pivot_idx, reference extra_matrix);

        static bool expect_char(std::istream& is, char expected);
        static bool read_matrix_row(std::istream& is, reference matrix, size_type row_idx);
};


template <typename T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& matrix);

template <typename T>
std::istream& operator >> (std::istream& is, Matrix<T>& matrix);

template <typename T>
Matrix<T> operator + (Matrix<T> lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator - (Matrix<T> lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator * (Matrix<T> lhs, const T& number);

template <typename T>
Matrix<T> operator * (const T& number, Matrix<T> rhs);

template <typename T>
Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs);


#include "matrix.cpp"

#endif 