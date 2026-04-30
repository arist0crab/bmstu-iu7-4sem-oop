#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include <memory>

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

        MatrixIterator() : m_weak_data(), m_index(0) {}
        explicit MatrixIterator(std::shared_ptr<T[]> data, size_t index = 0) : m_weak_data(data), m_index(index) {}
        MatrixIterator(const MatrixIterator& other) = default;
        MatrixIterator& operator=(const MatrixIterator& other) = default;

        // ===============================
        //   Операторы разыменовывания
        // ===============================

        reference operator [] (difference_type n) const { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("expired");
            return shared[m_index + n];
        }
        reference operator * () const { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("expired");
            return shared[m_index];
        }
        pointer operator -> () const { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("expired");
            return &shared[m_index];
        }

        // ===============================
        //     Инкременты и декременты
        // ===============================

        MatrixIterator& operator++() { ++m_index; return *this; }
        MatrixIterator operator++(int) { MatrixIterator tmp = *this; ++m_index; return tmp; }
        MatrixIterator& operator--() { --m_index; return *this; }
        MatrixIterator operator--(int) { MatrixIterator tmp = *this; --m_index; return tmp; }

        // ===============================
        //     Арифметика итераторов
        // ===============================

        MatrixIterator& operator += (difference_type n) { m_index += n; return *this; }
        MatrixIterator& operator -= (difference_type n) { m_index -= n; return *this; }
        MatrixIterator operator + (difference_type n) const { MatrixIterator result = *this; result.m_index += n; return result; }
        MatrixIterator operator - (difference_type n) const { MatrixIterator result = *this; result.m_index -= n; return result; }
        difference_type operator - (const MatrixIterator& other) const { return static_cast<difference_type>(m_index) - static_cast<difference_type>(other.m_index); }

        // ===============================
        //       Операторы сравнения
        // ===============================

        bool operator == (const MatrixIterator& other) const { return m_index == other.m_index && !m_weak_data.owner_before(other.m_weak_data) && !other.m_weak_data.owner_before(m_weak_data); }
        bool operator != (const MatrixIterator& other) const { return !(*this == other); }
        bool operator < (const MatrixIterator& other) const { return m_index < other.m_index; }
        bool operator > (const MatrixIterator& other) const { return m_index > other.m_index; }
        bool operator <= (const MatrixIterator& other) const { return m_index <= other.m_index; }
        bool operator >= (const MatrixIterator& other) const { return m_index >= other.m_index; }

    private:
        std::weak_ptr<T[]> m_weak_data;
        size_t m_index;
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

        MatrixConstIterator() : m_weak_data(), m_index(0) {}
        explicit MatrixConstIterator(std::shared_ptr<T[]> data, size_t index = 0) : m_weak_data(data), m_index(index) {}
        MatrixConstIterator(const MatrixConstIterator& other) = default;
        MatrixConstIterator(const MatrixIterator<T>& other) : m_weak_data(other.m_weak_data), m_index(other.m_index) {}
        
        MatrixConstIterator& operator=(const MatrixConstIterator& other) = default;

        // ===============================
        //   Операторы разыменовывания
        // ===============================

        reference operator [] (difference_type n) const { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("expired");
            return shared[m_index + n];
        }
        reference operator * () const { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("expired");
            return shared[m_index];
        }
        pointer operator -> () const { 
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("expired");
            return &shared[m_index];
        }

        // ===============================
        //     Инкременты и декременты
        // ===============================

        MatrixConstIterator& operator++() { ++m_index; return *this; }
        MatrixConstIterator operator++(int) { MatrixConstIterator tmp = *this; ++m_index; return tmp; }
        MatrixConstIterator& operator--() { --m_index; return *this; }
        MatrixConstIterator operator--(int) { MatrixConstIterator tmp = *this; --m_index; return tmp; }

        // ===============================
        //     Арифметика итераторов
        // ===============================

        MatrixConstIterator& operator += (difference_type n) { m_index += n; return *this; }
        MatrixConstIterator& operator -= (difference_type n) { m_index -= n; return *this; }
        MatrixConstIterator operator + (difference_type n) const { MatrixConstIterator result = *this; result.m_index += n; return result; }
        MatrixConstIterator operator - (difference_type n) const { MatrixConstIterator result = *this; result.m_index -= n; return result; }
        difference_type operator - (const MatrixConstIterator& other) const { return static_cast<difference_type>(m_index) - static_cast<difference_type>(other.m_index); }

        // ===============================
        //       Операторы сравнения
        // ===============================

        bool operator == (const MatrixConstIterator& other) const { return m_index == other.m_index && !m_weak_data.owner_before(other.m_weak_data) && !other.m_weak_data.owner_before(m_weak_data); }
        bool operator != (const MatrixConstIterator& other) const { return !(*this == other); }
        bool operator < (const MatrixConstIterator& other) const { return m_index < other.m_index; }
        bool operator > (const MatrixConstIterator& other) const { return m_index > other.m_index; }
        bool operator <= (const MatrixConstIterator& other) const { return m_index <= other.m_index; }
        bool operator >= (const MatrixConstIterator& other) const { return m_index >= other.m_index; }

    private:
        std::weak_ptr<T[]> m_weak_data;
        size_t m_index;
};


template <typename T>
MatrixConstIterator<T> operator + (typename MatrixConstIterator<T>::difference_type n, const MatrixConstIterator<T>& it) 
{ 
    return it + n; 
}


#endif