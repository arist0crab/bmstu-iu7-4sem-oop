#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <concepts>
#include <memory>
#include <type_traits>
#include <random>
#include <span>
#include "exception.hpp"


template <typename T>
concept MatrixElement = std::is_arithmetic_v<T>;

#include "matrix_iterator.hpp"

template <typename T>
class Matrix
{
    class MatrixRow
    {
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using iterator = T*;
            using const_iterator = const T*;
            using difference_type = std::ptrdiff_t;
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
        using pointer = T*;
        using const_pointer = const T*;

        using iterator = MatrixIterator<T>;
        using const_iterator = MatrixConstIterator<T>;
        
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;

        // ===============================
        //      Проверка итераторов
        // ===============================
        
        static_assert(std::random_access_iterator<iterator>, MATRIX_ITERATOR_RANDOM_ACCESS_CORRESPONDENCE_ERROR);   
        static_assert(std::random_access_iterator<const_iterator>, MATRIX_CONST_ITERATOR_RANDOM_ACCESS_CORRESPONDENCE_ERROR);
        static_assert(std::is_same_v<typename std::iterator_traits<iterator>::value_type, T>, MATRIX_ITERATOR_VALUE_TYPE_ERROR);

        // ===============================
        //          Конструкторы
        // ===============================

        Matrix();
        Matrix(size_type rows, size_type cols); 
        Matrix(size_type rows, size_type cols, const_reference value);
        Matrix(std::initializer_list<std::initializer_list<value_type>> init_list);
        
        Matrix(Matrix &&other_matrix) noexcept;
        Matrix(const Matrix &other_matrix);
        // TODO получить матрицу из сишной матрицы
        // TODO матрицу из другого контейнера
        // TODO через итераторы другого контейнера
        // TODO через матрицу другого типа если это возможно
        ~Matrix() = default;

        Matrix& operator = (const Matrix &other_matrix);
        Matrix& operator = (Matrix &&other_matrix);

        // ===============================
        //          Итераторы
        // ===============================

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept;

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
        Matrix &operator &= (const Matrix &other_matrix);

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

        Matrix& add(const Matrix &other_matrix);
        Matrix& sub(const Matrix &other_matrix);
        Matrix& mult(const Matrix &other_matrix);
        Matrix& mult_scalar(const_reference number);
        Matrix& mult_hadamard(const Matrix &other_matrix);

        Matrix inverse() const;
        Matrix transpose() const;
        Matrix pow(size_type exp) const;

        value_type trace() const;
        value_type determinant() const;

        bool is_square() const noexcept;
        bool is_symmetric() const noexcept;
        bool is_diagonal() const noexcept;
        bool is_identity() const noexcept;

        size_type rank() const;

        static Matrix identity(size_type size) noexcept;
        static Matrix random(size_type rows, size_type cols, value_type min_val, value_type max_val) noexcept;

    private:
        size_type m_rows = 0;
        size_type m_cols = 0;
        std::unique_ptr<value_type[]> m_data = nullptr;

        size_type find_pivot(size_type column) const;
        void eliminate_column(size_type pivot_idx, Matrix& extra_matrix);

        void swap_rows(size_type row1, size_type row2);
        void scale_row(size_type row, value_type factor);
        void transform_rows(size_type target, size_type source, value_type factor, Matrix<T>& extra);

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