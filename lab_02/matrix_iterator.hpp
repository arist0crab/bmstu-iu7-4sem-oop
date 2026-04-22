#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <iterator>
#include <cstddef>

template <typename T>
class MatrixIterator 
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        // ===============================
        //          Конструкторы
        // ===============================

        MatrixIterator() : m_ptr(nullptr) {}
        explicit MatrixIterator(pointer ptr) : m_ptr(ptr) {}
        MatrixIterator(const MatrixIterator& other) = default;
        MatrixIterator& operator=(const MatrixIterator& other) = default;

        // ===============================
        //   Операторы разыменовывания
        // ===============================

        reference operator [] (difference_type n) const { return *(m_ptr + n); }
        reference operator * () const { return *m_ptr; }
        pointer operator -> () const { return m_ptr; }

        // ===============================
        //     Инкременты и декременты
        // ===============================

        MatrixIterator& operator++() { ++m_ptr; return *this; }
        MatrixIterator operator++(int) { MatrixIterator tmp = *this; ++m_ptr; return tmp; }
        MatrixIterator& operator--() { --m_ptr; return *this; }
        MatrixIterator operator--(int) { MatrixIterator tmp = *this; --m_ptr; return tmp; }

        // ===============================
        //     Арифметика итераторов
        // ===============================

        MatrixIterator& operator += (difference_type n) { m_ptr += n; return *this; }
        MatrixIterator& operator -= (difference_type n) { m_ptr -= n; return *this; }
        MatrixIterator operator + (difference_type n) const { return MatrixIterator(m_ptr + n); }
        MatrixIterator operator - (difference_type n) const { return MatrixIterator(m_ptr - n); }
        difference_type operator - (const MatrixIterator& other) const { return m_ptr - other.m_ptr; }

        // ===============================
        //       Операторы сравнения
        // ===============================

        bool operator == (const MatrixIterator& other) const { return m_ptr == other.m_ptr; }
        bool operator != (const MatrixIterator& other) const { return m_ptr != other.m_ptr; }
        bool operator < (const MatrixIterator& other) const { return m_ptr < other.m_ptr; }
        bool operator > (const MatrixIterator& other) const { return m_ptr > other.m_ptr; }
        bool operator <= (const MatrixIterator& other) const { return m_ptr <= other.m_ptr; }
        bool operator >= (const MatrixIterator& other) const { return m_ptr >= other.m_ptr; }

    private:
        pointer m_ptr;
};


template <typename T>
MatrixIterator<T> operator + (typename MatrixIterator<T>::difference_type n, const MatrixIterator<T>& it) 
{ 
    return it + n; 
}


template <typename T>
class MatrixConstIterator 
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        // ===============================
        //          Конструкторы
        // ===============================

        MatrixConstIterator() : m_ptr(nullptr) {}
        explicit MatrixConstIterator(pointer ptr) : m_ptr(ptr) {}
        MatrixConstIterator(const MatrixConstIterator& other) = default;
        MatrixConstIterator(const MatrixIterator<T>& other) : m_ptr(other.operator->()) {}
        
        MatrixConstIterator& operator=(const MatrixConstIterator& other) = default;

        // ===============================
        //   Операторы разыменовывания
        // ===============================

        reference operator [] (difference_type n) const { return *(m_ptr + n); }
        reference operator * () const { return *m_ptr; }
        pointer operator -> () const { return m_ptr; }

        // ===============================
        //     Инкременты и декременты
        // ===============================

        MatrixConstIterator& operator++() { ++m_ptr; return *this; }
        MatrixConstIterator operator++(int) { MatrixConstIterator tmp = *this; ++m_ptr; return tmp; }
        MatrixConstIterator& operator--() { --m_ptr; return *this; }
        MatrixConstIterator operator--(int) { MatrixConstIterator tmp = *this; --m_ptr; return tmp; }

        // ===============================
        //     Арифметика итераторов
        // ===============================

        MatrixConstIterator& operator += (difference_type n) { m_ptr += n; return *this; }
        MatrixConstIterator& operator -= (difference_type n) { m_ptr -= n; return *this; }
        MatrixConstIterator operator + (difference_type n) const { return MatrixConstIterator(m_ptr + n); }
        MatrixConstIterator operator - (difference_type n) const { return MatrixConstIterator(m_ptr - n); }
        difference_type operator - (const MatrixConstIterator& other) const { return m_ptr - other.m_ptr; }

        // ===============================
        //       Операторы сравнения
        // ===============================

        bool operator == (const MatrixConstIterator& other) const { return m_ptr == other.m_ptr; }
        bool operator != (const MatrixConstIterator& other) const { return m_ptr != other.m_ptr; }
        bool operator < (const MatrixConstIterator& other) const { return m_ptr < other.m_ptr; }
        bool operator > (const MatrixConstIterator& other) const { return m_ptr > other.m_ptr; }
        bool operator <= (const MatrixConstIterator& other) const { return m_ptr <= other.m_ptr; }
        bool operator >= (const MatrixConstIterator& other) const { return m_ptr >= other.m_ptr; }

    private:
        pointer m_ptr;
};


template <typename T>
MatrixConstIterator<T> operator + (typename MatrixConstIterator<T>::difference_type n, const MatrixConstIterator<T>& it) 
{ 
    return it + n; 
}


#endif