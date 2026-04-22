#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <iterator>
#include <type_traits>

// TODO в классе матрицы делать static assert подходит ли этот итератор или нет
// TODO разнести константный и не константный итератор по разным классам

template <typename T, bool IsConst>
class MatrixIterator 
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    
    using pointer = std::conditional_t<IsConst, const T*, T*>;
    using reference = std::conditional_t<IsConst, const T&, T&>;

    // ===============================
    //          Конструкторы
    // ===============================

    explicit MatrixIterator(pointer ptr) : m_ptr(ptr) {}

    // ===============================
    //   Операторы разыменовывания
    // ===============================

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

    private:
        pointer m_ptr; 
};

#endif