#include <iostream>
#include <algorithm> 
#include "matrix.hpp"

int main() {
    try {
        std::cout << "--- 1. Создание и ввод матриц ---" << std::endl;

        Matrix<double> m1(3, 3, 0.0);
        
        m1(0, 0) = 4.0; m1(0, 1) = 7.0; m1(0, 2) = 2.0;
        m1(1, 0) = 3.0; m1(1, 1) = 6.0; m1(1, 2) = 1.0;
        m1(2, 0) = 2.0; m1(2, 1) = 5.0; m1(2, 2) = 8.0;

        std::cout << "Матрица M1:\n" << m1 << std::endl;

        std::cout << "--- 2. Демонстрация итераторов ---" << std::endl;

        std::cout << "Сортируем все элементы M1 по возрастанию..." << std::endl;
        std::sort(m1.begin(), m1.end());
        std::cout << "M1 после сортировки:\n" << m1 << std::endl;

        std::cout << "--- 3. Математические операции ---" << std::endl;
        Matrix<double> m2 = m1; 
        m2 *= 2.0;   
        std::cout << "M2 (это M1 * 2.0):\n" << m2 << std::endl;

        Matrix<double> res = m1 * m2; 
        std::cout << "Результат M1 * M2:\n" << res << std::endl;

        std::cout << "--- 4. Линейная алгебра ---" << std::endl;
        std::cout << "Ранг матрицы M1: " << m1.rank() << std::endl;
        
        if (m1.rank() == m1.cols())
            std::cout << "Обратная матрица для M1:\n" << m1.inverse() << std::endl;

        std::cout << "--- 5. Работа со строками ---" << std::endl;
        auto row = m1[0]; 
        std::cout << "Первый элемент первой строки: " << row[0] << std::endl;

    } 
    catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    }

    return 0;
}