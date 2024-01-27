#include "MyFunctions.h"

using namespace Prog1;

int main() {
	setlocale( LC_ALL , "Russian");
	while(true){ // мое интерактивное диалоговое окно  можно и через кейс 
		int m;
		std::cout << " Если хотите создать матрицу нажмите 1 \n Если хотите выйти нажмите 0"<<std::endl ;
		try
		{
			m = getNum<int>(0,1);
		}
		catch (const std::runtime_error& re)
		{
			std::cerr << re.what() << std::endl;
			
			return 1;
		}
		
		if(m==1){
			Matrix matrix ; // исходная матрица  
			Line vector; // вектор Б
			try
			{
				matrix = input() ; // ввод и проверка корректности ввода и выделения памяти
				vector = GenerateVector_B(matrix);
				outputMatrix(matrix);
				outputVectorB(vector);				
				freeMemoryVector(vector);			
				freeMemoryMatrix(matrix);
			}
			catch (const std::bad_alloc& ba)
			{
				std::cerr << ba.what()<< std::endl;
				freeMemoryMatrix(matrix);
				freeMemoryVector(vector);
				return 1;
			}
			
			catch (const std::exception& e) { // в случае прочих исключений
				std::cerr << e.what() << std::endl;
				freeMemoryMatrix(matrix);
				freeMemoryVector(vector);
				return 1;
			}
			
		}
		else if (m==0) {
			break; // выход
		}
		else{
			std::cout << " Ошибка. Введите еще раз " << std::endl;
		
		}
		
	}
    return 0;
}