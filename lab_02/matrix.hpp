#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <concepts>
#include <memory>
#include <type_traits>

#define MATRIX_ELEMENT_TYPE_ERROR "Matrix element type must be copyable and destructible"
#define MATRIX_INITIALIZER_LIST_CONSTRUCTOR_ERROR "Inconsistent row lengths in initializer_list"
#define MATRIX_UNARY_ADD_SUB_ERR "Matrix dimensions must match for addition"

// элементы матрицы - арифметические типы
template <typename T>
concept MatrixElement = std::is_arithmetic_v<T>;

template <typename T>
class Matrix
{
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

        // TODO оператор присваивания
        // Matrix &operator=(Matrix other) noexcept;

        // ===============================
        //          Итераторы
        // ===============================

        // TODO

        // ===============================
        //       Доступ к элементам
        // ===============================

        // TODO

        // ===============================
        //          Вместимость
        // ===============================

        // TODO

        // ===============================
        //          Модификаторы
        // ===============================

        // TODO

        // ===============================
        //       Операторы доступа
        // ===============================

        // TODO 

        // ===============================
        //    Математические операторы
        // ===============================

        Matrix &operator -= (const Matrix &other_matrix);
        Matrix &operator += (const Matrix &other_matrix);
        Matrix &operator *= (const Matrix &other_matrix);
        Matrix &operator *= (const_reference number); 
        // TODO 

        // ===============================
        //    Математические операторы
        // ===============================

        // TODO

        // ===============================
        //      Математические методы
        // ===============================

        // TODO

    private:
        size_type m_rows = 0;
        size_type m_cols = 0;
        std::unique_ptr<value_type[]> m_data = nullptr;

        // TODO возможно придется переименовать метод или дописать какие-то спецификаторы
        void reset_matrix();

};


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