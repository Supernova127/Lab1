#ifndef FUNCTION
#define FUNCTION

#include <limits>
#include <iomanip>
#include <iostream>

namespace Prog1 {
	struct Line
	{
        int n = 0; // количество элементов вектора Б 
		double* a = nullptr; // массив элементов
	};
	struct Matrix
	{
        int m = 0; // количество строк и столбцов матрицы и количество элементов вектора Б
		Line* lines = nullptr; // массив строк
	};

    template<class T>
    T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max() ) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Не удалось прочитать номер EOF");
            else if (std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Не удалось прочитать номер: ") );
            // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if (std::cin.fail() || a < min || a > max) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода. Повторите ввод " << std::endl;
            }
            else // успешный ввод
                return a;
        }
    }
    Matrix input(); // ввод и проверка корректности ввода и выделения памяти 
    Line GenerateVector_B(const Matrix &matrix);
    double calculateAverage(const Matrix& matrix,const int i);// Эта функция вычисляет среднее арифметическое значение строки матрицы
    double calculateMax(const Matrix& matrix,const int i);
    double findNonZeroElementInMatrix(const Matrix& matrix);
    double zero(const Matrix& matrix,const int i);
    void outputMatrix(const Matrix& matrix);
    void outputVectorB(const Line& vector);
	void freeMemoryMatrix(Matrix& matrix);
    void freeMemoryVector(Line& vector);

}

#endif