#ifndef __BASE_MATRIX_HPP__
#define __BASE_MATRIX_HPP__

#include <iostream>
#include <concepts>
#include <type_traits>

#include "concepts.hpp"

template <MatrixElement T>
class BaseMatrix
{
    public:
        // ===============================
        //        Алиасы типов
        // ===============================
        
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        
        // ===============================
        //          Деструктор
        // ===============================
        
        virtual ~BaseMatrix() = default;
        
        // ===============================
        //             Методы
        // ===============================
        
        virtual size_type rows() const noexcept = 0;
        virtual size_type cols() const noexcept = 0;
        virtual size_type size() const noexcept = 0;
        virtual bool is_empty() const noexcept = 0;
        
        virtual reference operator()(size_type row, size_type col) = 0;
        virtual const_reference operator()(size_type row, size_type col) const = 0;
        
        virtual Matrix<T> transpose() const = 0;
        virtual Matrix<T> inverse() const = 0;
        virtual value_type determinant() const = 0;
        virtual value_type trace() const = 0;
        
        virtual bool is_square() const noexcept = 0;
        virtual bool is_symmetric() const noexcept = 0;
        virtual bool is_diagonal() const noexcept = 0;
        virtual bool is_identity() const noexcept = 0;
        
        virtual void clear() noexcept { }
        virtual void swap(BaseMatrix& other) noexcept { }
};

#endif