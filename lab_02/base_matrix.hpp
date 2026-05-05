#ifndef __BASE_MATRIX_HPP__
#define __BASE_MATRIX_HPP__

#include <any>


class BaseMatrix
{
    public:
        // ===============================
        //             Алиасы
        // ===============================
        
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
        virtual std::shared_ptr<BaseMatrix> transpose() const = 0;
        virtual std::shared_ptr<BaseMatrix> inverse() const = 0;
        virtual std::any determinant() const = 0;
        virtual std::any trace() const = 0;
        
        virtual bool is_square() const noexcept = 0;
        virtual bool is_symmetric() const noexcept = 0;
        virtual bool is_diagonal() const noexcept = 0;
        virtual bool is_identity() const noexcept = 0;
        
        virtual void clear() noexcept { }
        virtual void swap(BaseMatrix& other) noexcept { }
};

#endif