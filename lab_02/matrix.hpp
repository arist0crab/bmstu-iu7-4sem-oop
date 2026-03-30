#include <iostream>
#include <concepts>
#include <memory>

#define MATRIX_ELEMENT_TYPE_ERROR "Matrix element type must be copyable and destructible"

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

        Matrix() : m_rows(0), m_cols(0), m_data(nullptr);
        Matrix(size_type rows, size_type cols) : m_rows(rows), m_cols(cols), m_data(std::make_unique<T[]>(rows * cols)); 
        Matrix(size_type rows, size_type cols, const T& value) : m_rows(rows), m_cols(cols), m_data(std::make_unique<T[]>(rows * cols));
        Matrix(std::initializer_list<std::initializer_list<T>> init_list) : m_rows(init.size()), m_cols(0), m_data(nullptr);  // TODO
        // TODO template<typename OtherContainer>  
        // TODO explicit Matrix(const OtherContainer& container)
        Matrix(Matrix &&other_matrix) noexcept : m_rows(other_matrix.m_rows), m_cols(other_matrix.m_cols), m_data(std::move(other_matrix.m_data));  // TODO
        ~Matrix() = default;

        // TODO оператор присваивания
        Matrix &operator=(Matrix other) noexcept;

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
        //          Операторы
        // ===============================

        // TODO 

        // ===============================
        //      Математические методы
        // ===============================

        // TODO

    private:
        size_type m_rows = 0;
        size_type m_cols = 0;
        std::unique_ptr<T[]> m_data = nullptr;

        // TODO возможно придется переименовать метод или дописать какие-то спецификаторы
        void reset_matrix();

};