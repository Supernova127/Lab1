# установка мин версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта
project(lab1)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")

# создание библиотеки prog1
add_library(prog1 MyFunctions.h MyFunctions.cpp)

# подключение библиотеки prog1 ко всем таргетам, создаваемым далее
link_libraries(prog1)

# создание исполняемого файла
add_executable(main main.cpp)


# для сборки из консоли:
#
# mkdir build   # создание директории для файлов сборки
# cd build      # переход в директорию сборки
# cmake ..      # генерация файлов сборки на основе CMakeLists.txt
# cmake --build .        # сборка проекта