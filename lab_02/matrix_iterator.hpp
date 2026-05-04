#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <concepts>

template <typename T>
concept MatrixIteratorElement = MatrixElement<T>;

template <MatrixIteratorElement T>
class MatrixIteratorBase
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = T&;
        using pointer = T*;

        // ===============================
        //          Конструкторы
        // ===============================

        MatrixIteratorBase() noexcept : m_weak_data(), m_index(0) {}
        explicit MatrixIteratorBase(std::shared_ptr<T[]> data, size_t index = 0) noexcept : m_weak_data(data), m_index(index) {}
        MatrixIteratorBase(const MatrixIteratorBase& other) = default;
        MatrixIteratorBase& operator=(const MatrixIteratorBase& other) = default;

        // ===============================
        //   Операторы разыменовывания
        // ===============================

        reference operator [] (difference_type n) const
        { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return shared[m_index + n];
        }
        reference operator * () const
        { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return shared[m_index];
        }
        pointer operator -> () const
        { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return &shared[m_index];
        }

        // ===============================
        //     Инкременты и декременты
        // ===============================

        MatrixIteratorBase& operator++() noexcept { ++m_index; return *this; }
        MatrixIteratorBase operator++(int) noexcept { MatrixIteratorBase tmp = *this; ++m_index; return tmp; }
        MatrixIteratorBase& operator--() noexcept { --m_index; return *this; }
        MatrixIteratorBase operator--(int) noexcept { MatrixIteratorBase tmp = *this; --m_index; return tmp; }

        // ===============================
        //     Арифметика итераторов
        // ===============================

        MatrixIteratorBase& operator += (difference_type n) noexcept { m_index += n; return *this; }
        MatrixIteratorBase& operator -= (difference_type n) noexcept { m_index -= n; return *this; }
        MatrixIteratorBase operator + (difference_type n) const noexcept { MatrixIteratorBase result = *this; result += n; return result; }
        MatrixIteratorBase operator - (difference_type n) const noexcept { MatrixIteratorBase result = *this; result -= n; return result; }
        difference_type operator - (const MatrixIteratorBase& other) const noexcept { return static_cast<difference_type>(m_index) - static_cast<difference_type>(other.m_index); }

        // ===============================
        //       Операторы сравнения
        // ===============================

        bool operator == (const MatrixIteratorBase& other) const noexcept
        {
            auto s1 = m_weak_data.lock();
            auto s2 = other.m_weak_data.lock();
            return m_index == other.m_index && (!s1 || !s2 || s1 == s2);
        }
        auto operator <=> (const MatrixIteratorBase& other) const noexcept { return m_index <=> other.m_index; }

    protected:
        std::weak_ptr<T[]> m_weak_data;
        size_t m_index;
};


// ===============================
//          Итераторы
// ===============================

template <MatrixIteratorElement T>
class MatrixIterator : public MatrixIteratorBase<T>
{
    public:
        using MatrixIteratorBase<T>::MatrixIteratorBase;
};


template <MatrixIteratorElement T>
class MatrixConstIterator : public MatrixIteratorBase<const T>
{
    public:
        using MatrixIteratorBase<const T>::MatrixIteratorBase;
        MatrixConstIterator(const MatrixIterator<T>& other) noexcept : MatrixIteratorBase<const T>(other) {}
};


template <MatrixIteratorElement T>
class MatrixReverseIterator : public std::reverse_iterator<MatrixIterator<T>>
{
    public:
        using std::reverse_iterator<MatrixIterator<T>>::reverse_iterator;
};


template <MatrixIteratorElement T>
class MatrixConstReverseIterator : public std::reverse_iterator<MatrixConstIterator<T>>
{
    public:
        using std::reverse_iterator<MatrixConstIterator<T>>::reverse_iterator;
};


// ===============================
//      Внешние операторы
// ===============================

template <MatrixIteratorElement T>
MatrixIterator<T> operator + (typename MatrixIterator<T>::difference_type n, const MatrixIterator<T>& it) noexcept
{ 
    return it + n; 
}

template <MatrixIteratorElement T>
MatrixConstIterator<T> operator + (typename MatrixConstIterator<T>::difference_type n, const MatrixConstIterator<T>& it) noexcept
{ 
    return it + n; 
}


#endif