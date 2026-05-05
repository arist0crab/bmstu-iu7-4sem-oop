#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <concepts>
#include <memory>
#include <type_traits>
#include <random>
#include <span>

#include "exception.hpp"
#include "concepts.hpp"
#include "matrix_iterator.hpp"
#include "base_matrix.hpp"

template <MatrixElement T>
class Matrix : public BaseMatrix
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
        Matrix(size_type rows, size_type cols, T** c_matrix);

        Matrix(Matrix &&other_matrix) noexcept;
        explicit Matrix(const Matrix &other_matrix);

        template <ConvertibleTo<T> U>
        explicit Matrix(Matrix<U> &&other_matrix) noexcept;

        template <ConvertibleTo<T> U>
        explicit Matrix(const Matrix<U> &other_matrix);

        template <ConvertibleInputIterator<T> It, Sentinel<It> Sent>
        Matrix(size_type rows, size_type cols, It begin, Sent end);

        template <CommonContainer<T> Container>
        Matrix(size_type rows, size_type cols, const Container& container);
        
        ~Matrix() override = default;

        Matrix& operator = (const Matrix &other_matrix);
        Matrix& operator = (Matrix &&other_matrix);

        template <MatrixElement U>
        requires ConvertibleTo<U, T>
        Matrix& operator = (const Matrix<U>& other_matrix);

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

        size_type rows() const noexcept override;
        size_type cols() const noexcept override;
        size_type size() const noexcept override;
        bool is_empty() const noexcept override;

        // ===============================
        //          Модификаторы
        // ===============================

        void clear() noexcept override;

        void resize(size_type new_rows, size_type new_cols);
        
        void swap(Matrix &other_matrix);

        // ===============================
        //    Математические операторы
        // ===============================

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& operator += (const Matrix<U>& other_matrix);

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& operator -= (const Matrix<U>& other_matrix);

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& operator *= (const Matrix<U>& other_matrix);

        Matrix& operator *= (const_reference number);

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& operator &= (const Matrix<U>& other_matrix);

        // ===============================
        //       Операторы сравнения
        // ===============================

        template <MatrixElement U>
        requires EqualityComparable<T, U>
        bool equal(const Matrix<U>& other_matrix) const;

        template <MatrixElement U>
        requires EqualityComparable<T, U>
        auto operator<=>(const Matrix<U>& other) const;

        template <MatrixElement U>
        requires EqualityComparable<T, U>
        bool operator==(const Matrix<U>& other) const;

        template <MatrixElement U>
        requires EqualityComparable<T, U>
        bool operator!=(const Matrix<U>& other) const;

        bool equal(const Matrix &other_matrix) const;

        auto operator<=>(const Matrix &other) const;

        // ===============================
        //          Методы матрицы
        // ===============================

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& add(const Matrix<U>& other_matrix);

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& sub(const Matrix<U>& other_matrix);

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& mult(const Matrix<U>& other_matrix);

        Matrix& mult_scalar(const_reference number);

        template <MatrixElement U>
        requires HasCommon<T, U>
        Matrix& mult_hadamard(const Matrix<U>& other_matrix);

        std::shared_ptr<BaseMatrix> inverse() const;
        std::shared_ptr<BaseMatrix> transpose() const;
        Matrix pow(size_type exp) const;

        std::any trace() const override;
        std::any determinant() const override;

        bool is_square() const noexcept override;
        bool is_symmetric() const noexcept override;
        bool is_diagonal() const noexcept override;
        bool is_identity() const noexcept override;

        size_type rank() const;

        static Matrix identity(size_type size) noexcept;
        static Matrix random(size_type rows, size_type cols, value_type min_val, value_type max_val) noexcept;

    private:
        size_type m_rows = 0;
        size_type m_cols = 0;
        std::shared_ptr<value_type[]> m_data = nullptr;

        size_type find_pivot(size_type column) const;
        void eliminate_column(size_type pivot_idx, Matrix& extra_matrix);

        void swap_rows(size_type row1, size_type row2);
        void scale_row(size_type row, value_type factor);
        void transform_rows(size_type target, size_type source, value_type factor, Matrix<T>& extra);

        static bool expect_char(std::istream& is, char expected);
        static bool read_matrix_row(std::istream& is, reference matrix, size_type row_idx);
};


// ===============================
//    Внешние операторы
// ===============================

template <MatrixElement T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& matrix);

template <MatrixElement T>
std::istream& operator >> (std::istream& is, Matrix<T>& matrix);

template <MatrixElement T, MatrixElement U>
requires HasCommon<T, U> && SameSizeMatrices<Matrix<T>, Matrix<U>>
auto operator + (const Matrix<T>& lhs, const Matrix<U>& rhs);

template <MatrixElement T, MatrixElement U>
requires HasCommon<T, U> && SameSizeMatrices<Matrix<T>, Matrix<U>>
auto operator - (const Matrix<T>& lhs, const Matrix<U>& rhs);

template <MatrixElement T, ArithmeticScalar U>
requires HasCommon<T, U>
auto operator * (const Matrix<T>& lhs, const U& number);

template <ArithmeticScalar T, MatrixElement U>
requires HasCommon<T, U>
auto operator * (const T& number, const Matrix<U>& rhs);

template <MatrixElement T, MatrixElement U>
requires HasCommon<T, U> && MultipliableMatrices<Matrix<T>, Matrix<U>>
auto operator * (const Matrix<T>& lhs, const Matrix<U>& rhs);

#include "matrix.cpp"


#endif