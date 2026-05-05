#ifndef MATRIX_ITERATOR_HPP
#define MATRIX_ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <concepts>

// ===============================
//      Базовый итератор (нешаблонный)
// ===============================

class MatrixIteratorBase
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = void;
        using difference_type = std::ptrdiff_t;
        using reference = void;
        using pointer = void;

        MatrixIteratorBase() noexcept : m_index(0) {}
        explicit MatrixIteratorBase(size_t index) noexcept : m_index(index) {}
        MatrixIteratorBase(const MatrixIteratorBase& other) = default;
        MatrixIteratorBase& operator=(const MatrixIteratorBase& other) = default;
        virtual ~MatrixIteratorBase() = default;

        MatrixIteratorBase& operator++() noexcept { ++m_index; return *this; }
        MatrixIteratorBase operator++(int) noexcept { MatrixIteratorBase tmp(*this); ++m_index; return tmp; }
        MatrixIteratorBase& operator--() noexcept { --m_index; return *this; }
        MatrixIteratorBase operator--(int) noexcept { MatrixIteratorBase tmp(*this); --m_index; return tmp; }

        MatrixIteratorBase& operator+=(difference_type n) noexcept { m_index += n; return *this; }
        MatrixIteratorBase& operator-=(difference_type n) noexcept { m_index -= n; return *this; }
        MatrixIteratorBase operator+(difference_type n) const noexcept { MatrixIteratorBase result(*this); result += n; return result; }
        MatrixIteratorBase operator-(difference_type n) const noexcept { MatrixIteratorBase result(*this); result -= n; return result; }
        difference_type operator-(const MatrixIteratorBase& other) const noexcept { return static_cast<difference_type>(m_index) - static_cast<difference_type>(other.m_index); }

        bool operator==(const MatrixIteratorBase& other) const noexcept { return m_index == other.m_index; }
        auto operator<=>(const MatrixIteratorBase& other) const noexcept { return m_index <=> other.m_index; }

    protected:
        size_t m_index;
        
        size_t get_index() const noexcept { return m_index; }
};

// ===============================
//      Концепт для T
// ===============================

template <typename T>
concept MatrixIteratorElement = std::is_scalar_v<T> || std::is_class_v<T>;

// ===============================
//      Шаблонный итератор
// ===============================

template <MatrixIteratorElement T>
class MatrixIterator : public MatrixIteratorBase
{
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = T&;
        using pointer = T*;

        MatrixIterator() noexcept : MatrixIteratorBase(), m_weak_data() {}
        
        explicit MatrixIterator(std::shared_ptr<T[]> data, size_t index = 0) noexcept 
            : MatrixIteratorBase(index), m_weak_data(data) {}
        
        MatrixIterator(const MatrixIterator& other) = default;
        MatrixIterator& operator=(const MatrixIterator& other) = default;

        reference operator[](difference_type n) const
        {
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return shared[m_index + n];
        }

        reference operator*() const
        {
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return shared[m_index];
        }

        pointer operator->() const
        {
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return &shared[m_index];
        }

        MatrixIterator& operator++() noexcept { MatrixIteratorBase::operator++(); return *this; }
        MatrixIterator operator++(int) noexcept { MatrixIterator tmp(*this); MatrixIteratorBase::operator++(); return tmp; }
        MatrixIterator& operator--() noexcept { MatrixIteratorBase::operator--(); return *this; }
        MatrixIterator operator--(int) noexcept { MatrixIterator tmp(*this); MatrixIteratorBase::operator--(); return tmp; }

        MatrixIterator& operator+=(difference_type n) noexcept { MatrixIteratorBase::operator+=(n); return *this; }
        MatrixIterator& operator-=(difference_type n) noexcept { MatrixIteratorBase::operator-=(n); return *this; }
        MatrixIterator operator+(difference_type n) const noexcept { MatrixIterator tmp(*this); tmp += n; return tmp; }
        MatrixIterator operator-(difference_type n) const noexcept { MatrixIterator tmp(*this); tmp -= n; return tmp; }
        
        difference_type operator-(const MatrixIterator& other) const noexcept 
        { 
            return MatrixIteratorBase::operator-(other); 
        }
        
        std::weak_ptr<T[]> get_weak_data() const noexcept { return m_weak_data; }

    protected:
        std::weak_ptr<T[]> m_weak_data;
};

// ===============================
//      Константный итератор
// ===============================

template <MatrixIteratorElement T>
class MatrixConstIterator : public MatrixIteratorBase
{
    public:
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using reference = const T&;
        using pointer = const T*;

        MatrixConstIterator() noexcept : MatrixIteratorBase(), m_weak_data() {}
        
        explicit MatrixConstIterator(std::shared_ptr<T[]> data, size_t index = 0) noexcept 
            : MatrixIteratorBase(index), m_weak_data(data) {}
        
        MatrixConstIterator(const MatrixConstIterator& other) = default;
        MatrixConstIterator& operator=(const MatrixConstIterator& other) = default;
        
        MatrixConstIterator(const MatrixIterator<T>& other) noexcept 
            : MatrixIteratorBase(other.get_index()), m_weak_data(other.get_weak_data()) {}

        reference operator[](difference_type n) const
        {
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return shared[m_index + n];
        }

        reference operator*() const
        {
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return shared[m_index];
        }

        pointer operator->() const
        {
            auto shared = m_weak_data.lock();
            if (!shared) throw std::runtime_error("Iterator expired: data has been deallocated");
            return &shared[m_index];
        }

        MatrixConstIterator& operator++() noexcept { MatrixIteratorBase::operator++(); return *this; }
        MatrixConstIterator operator++(int) noexcept { MatrixConstIterator tmp(*this); MatrixIteratorBase::operator++(); return tmp; }
        MatrixConstIterator& operator--() noexcept { MatrixIteratorBase::operator--(); return *this; }
        MatrixConstIterator operator--(int) noexcept { MatrixConstIterator tmp(*this); MatrixIteratorBase::operator--(); return tmp; }

        MatrixConstIterator& operator+=(difference_type n) noexcept { MatrixIteratorBase::operator+=(n); return *this; }
        MatrixConstIterator& operator-=(difference_type n) noexcept { MatrixIteratorBase::operator-=(n); return *this; }
        MatrixConstIterator operator+(difference_type n) const noexcept { MatrixConstIterator tmp(*this); tmp += n; return tmp; }
        MatrixConstIterator operator-(difference_type n) const noexcept { MatrixConstIterator tmp(*this); tmp -= n; return tmp; }
        
        difference_type operator-(const MatrixConstIterator& other) const noexcept 
        { 
            return MatrixIteratorBase::operator-(other); 
        }

    protected:
        std::weak_ptr<T[]> m_weak_data;
};

// ===============================
//      Реверсивные итераторы
// ===============================

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
MatrixIterator<T> operator+(typename MatrixIterator<T>::difference_type n, const MatrixIterator<T>& it) noexcept
{
    return it + n;
}

template <MatrixIteratorElement T>
MatrixConstIterator<T> operator+(typename MatrixConstIterator<T>::difference_type n, const MatrixConstIterator<T>& it) noexcept
{
    return it + n;
}

#endif