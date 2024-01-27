#include "MyFunctions.h"


namespace Prog1 {

    Matrix input() { // ввод и проверка корректности ввода и выделения памяти 
        Matrix matrix;

        std::cout << "введите число который отвечает за количество строк и столбцов " << std::endl;
         
        try
        {
            matrix.m = getNum<int>(1, 500); // matrix.m это количество строк и столбцов
            matrix.lines = new Line[matrix.m];            
            for (int i = 0; i < matrix.m; i++) {
                matrix.lines[i].a = new double[(matrix.m - i)];                
            }           
        }
        catch (const std::bad_alloc& ba) // в случае ошибки выделения памяти 
        {
            throw std::runtime_error("Ошибка выделения памяти для матрицы ");
        }
       
        for (int i = 0; i < matrix.m; i++) { // ввод матрицы ( ввод только главной диагонали и то что выше него )
            // так как это симметрическая матрица 
            for (int j = 0; j < (matrix.m - i); j++) {

                std::cout << "Введите элемент  матрицы A" << i << "." << (j + i) << ":" << std::endl;
                matrix.lines[i].a[j] = getNum<double>();
            }
        }

        return matrix;

    }

    Line GenerateVector_B(const Matrix& matrix) {
        Line vector;
        try
        {
            vector.a = new double[matrix.m]; // выдиления памяти вектору Б
            vector.n = matrix.m; // количество элементов вектора Б
            for (int i = 0; i < vector.n; i++) {
                double average, max;

                average = calculateAverage(matrix, i); // среднее арифметическое значение строки матрицы
                max = zero(matrix,i);
                if (max == 1) {
                    max = findNonZeroElementInMatrix(matrix);
                }
                else if(max == 0){
                    max = calculateMax(matrix, i);
                }
                if (max == 0) {
                    throw std::runtime_error("Деление на 0 ");
                }
                std::cout << "average " << average << std::endl;
                std::cout << "max " << max << std::endl;

                vector.a[i] = average / max;

            }

        }       
        catch (const std::bad_alloc& ba) // в случае любого исключения
        {
            throw std::runtime_error("Ошибка выделения памяти для матрицы ");
        }
        

        return vector;
    }
 
    double zero(const Matrix& matrix,const int i) {
        for (int j = 0; j < matrix.m; j++) {
            if (matrix.lines[0].a[j] == 0) {
                return 1;
            }
        }
        return 0;
    }

    double calculateAverage(const Matrix& matrix,const int i) { // Эта функция вычисляет среднее арифметическое значение строки матрицы
        double average = 0;
        int j = 0;
        while (j < matrix.m) {
            if(j < (matrix.m - i)) {
            average += matrix.lines[i].a[j];
            
            }
            if (j >= (matrix.m - i)) {
                if (i >= j) {
                    average += matrix.lines[(i - j)].a[j];
                }
                if (i < j) {
                    average += matrix.lines[(i - (matrix.m - j ))].a[(matrix.m -j)];

                }
            }
            j++;
        }
        average = average / matrix.m;

        return average;
    }

    double findNonZeroElementInMatrix(const Matrix& matrix) { // по заданию  если первый элемент в строке равен нулю то ( fun{ci} равен ) первый не нулевой элемент матрицы
        for (int i = 0; i < matrix.m; i++) {
            for (int j = i; j < (matrix.m-i); j++) {
                if (matrix.lines[i].a[j] != 0) {
                    return matrix.lines[i].a[j]; // нашол ненулевой элемент
                }
            }
        }        
        
        return 0; // если не нашол ненулевой элемент
    }

    double calculateMax(const Matrix& matrix,const int i) {
        // по заданию  если первый элемент в строке не равен нулю товычисление максимального элемента i-ой строки матрицы
        double max = matrix.lines[i].a[0];
        for (int j = 0; j < matrix.m; j++) {
            if (j < (matrix.m - i)) {
                if (max < matrix.lines[i].a[j]) {
                max = matrix.lines[i].a[j];
                }
            }

            if (j >= (matrix.m - i)) {
                if (i >= j) {
                    if (max < matrix.lines[(i - j)].a[j]) {
                        max = matrix.lines[(i - j)].a[j];
                    }                   
                }
                if (i < j) {
                    if (max < matrix.lines[(i - (matrix.m - j))].a[(matrix.m - j)]) {
                        max = matrix.lines[(i - (matrix.m - j))].a[(matrix.m - j)];
                    }                   
                }
            }
            
        }
        
        return max;

    }

    void outputMatrix(const Matrix& matrix) { // вывод матрицы и вектора 
        std::cout << "Исходная матрица" << std::endl;
        for (int i = 0; i < matrix.m; i++) {

            for (int j = 0; j < (matrix.m - (matrix.m - i)); j++) {
                std::cout << std::setw(6) << std::setprecision(8) << " A" << i << j << " = " << matrix.lines[j].a[(i - j)] << " ";

            }
            for (int j = 0; j < (matrix.m - i); j++) {

                std::cout << std::setw(6) << std::setprecision(8) << " A" << i << (j + i) << " = " << matrix.lines[i].a[j] << " ";
                //setw устанавливает ширину поля  для каждого элемента setprecision устанавливает точность вывода 
            }   // чтобы матрица была приятной для глаз 
            std::cout << std::endl;
        }
    }

    void outputVectorB(const Line& vector) {
        std::cout << "Вектор Б" << std::endl;
        for (int i = 0; i < vector.n; i++) {
            std::cout << std::setw(6) << std::setprecision(8) << " Б" << i << " = " << vector.a[i] << " ";
        }
        std::cout << std::endl;
    }

    void freeMemoryMatrix(Matrix& matrix) {
        if (matrix.lines != nullptr) {
            for (int i = 0; i < (matrix.m - i); i++)
                delete[] matrix.lines[i].a;
        }
        delete[] matrix.lines;
        matrix.lines = nullptr;
        matrix.m = 0;
    }

    void freeMemoryVector(Line& vector) {
        if (vector.a != nullptr) {
            delete[] vector.a;
        }
        vector.a = nullptr;
        vector.n = 0;
    }   
    
}