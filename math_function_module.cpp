
#include <stddef.h> // Чтобы определить NULL

///////// Включения основного модуля module.h
#include "Module.h"
#include "Function_module.h"

#include <math.h>
#include <iostream>
#include <time.h> // для Рандомайзера 


using namespace std;


// Опишу функцию вне класса чтобы можно было применять cout
FunctionResult* MathFunctionModule::executeFunction(regval functionId, regval *args){
	cout << "Func executed" << endl;
	if (!functionId) {
		return NULL;
	}

	// эта конструкция чтобы создать заранее объект указатель на который будем возвращать
	char ch4 = '1'; // имя надо будет поменять  или просто что-то поменять. Но пока символ оставим в покое и буем работать с result.
	rez = new FunctionResult(ch4);

	// Уже не тестовое задание пробуем описать
	switch (functionId) {
		//первая функция pow - квадрат. 1-й аргумент возводимое, второй - степень.
		case 1:  // Тут вопрос про приведение типов
		{
			//C приведением типов
			double arg1,arg2,resOfPow;
			arg1=*args;
			arg2=*(args+1);
			resOfPow=pow(arg1,arg2);
			rez->result = (int) resOfPow;
			// Все сделали и выходим из свича
			break;
		}
		case 2: // ABS модуль числа
		{
		/*C приведением типов*/ 
			int resOfabs;
			resOfabs = abs(*args);
			rez->result = resOfabs;
			// Все сделали и выходим из свича
			break;
		}
		case 3: // FMOD Остаток от деления
		{
			int resOfmod;
			resOfmod = (int) fmod(*args,*(args +1));
			rez->result = resOfmod;
			// Все сделали и выходим из свича
			break;
		}
		case 4: // DIV Целочисленное деление
			int resOfdiv;
			resOfdiv = ( *args - (int)fmod(*args, *(args + 1)) ) / (*(args+1));
			rez->result = resOfdiv;
			// Все сделали и выходим из свича
			break;
	
		case 5: // Корень 2-й степени Результат будем выводить умноженным на 1000, потому что растет медленно(меняется медленно)
		{
			int resOfsqrt;
			resOfsqrt = (int) (1000 * sqrt(*args));
			rez->result = resOfsqrt;
			// Все сделали и выходим из свича
			break;
		}
		case 6: // Рандомное целое число
		{
			int resOfrand;
			resOfrand = rand()%(*args) + (*(args+1)) ;
			rez->result = resOfrand;
			// Все сделали и выходим из свича
			break;
		}
		case 7: // Синус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
		{
			int resOfsin;
			resOfsin = (int) (1000 * sin(*args/1000)) ;
			rez->result = resOfsin;
			// Все сделали и выходим из свича
			break;
		}
		case 8: // Косинус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
		{
			int resOfcos;
			resOfcos = (int)(1000 * cos(*args/1000));
			rez->result = resOfcos;
			// Все сделали и выходим из свича
			break;
		}
		case 9: // Тангенс Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
		{
			int resOftan;
			resOftan = (int)(1000 * tan(*args / 1000));
			rez->result = resOftan;
			// Все сделали и выходим из свича
			break;
		}
		case 10: // АркСинус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
		{
			int resOfasin;
			resOfasin = (int)(1000 * asin(*args / 1000));
			rez->result = resOfasin;
			// Все сделали и выходим из свича
			break;
		}
		case 11: // АркКосинус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
		{
			int resOfacos;
			resOfacos = (int)(1000 * acos(*args / 1000));
			rez->result = resOfacos;
			// Все сделали и выходим из свича
			break;
		}
		case 12: // АркТангенс Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
		{
			int resOfatan;
			resOfatan = (int)(1000 * atan(*args / 1000));
			rez->result = resOfatan;
			// Все сделали и выходим из свича
			break;
		}
		case 13: // Экспонента Растет быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000
		{
			int resOfexp;
			resOfexp = (int)exp(*args / 1000);
			rez->result = resOfexp;
			// Все сделали и выходим из свича
			break;
		}
		case 14: // Логарифм Натуральный Растет медленно поэтому вывод умножим на 1000
		{
			int resOflog;
			resOflog = (int)( 1000* log(*args));
			rez->result = resOflog;
			// Все сделали и выходим из свича
			break;
		}
		case 15: // Десятичный логарифм Растет медленно поэтому вывод умножим на 1000
		{
			int resOflog10;
			resOflog10 = (int) (1000 * log10(*args));
			rez->result = resOflog10;
			// Все сделали и выходим из свича
			break;
		}
        }; // Конец switch
	return rez;
};





int main(){
	int test;
	test = 1;
	cout << test << endl;


	regval *arg1;
	regval x;
	x = 1;
	arg1 = &x;

	regval TwoArgs[] = {2,3};
	regval absTestMas[] = { -14 };
	regval fmodTestMas[] = { 7, 4 };
	regval divTestMas[] = { 9, 4 };
	regval randTestMas[] = { 10, 1 };
	regval SiCoTanTestMas[] = {1};
	
	MathFunctionModule newObject;

	FunctionResult *FRobject;

	// проверка возведения в степень
	FRobject = newObject.executeFunction(1, TwoArgs); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject << endl;
	cout << FRobject->type << endl;
	cout << FRobject->result << endl;

   

	// Проверка получения абсолютной величины
	FRobject = newObject.executeFunction(2, absTestMas); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject << endl;
	cout << FRobject->type << endl;
	cout << FRobject->result << endl;

	// Проверка остатка от деления
	FRobject = newObject.executeFunction(3, fmodTestMas); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject << endl;
	cout << FRobject->type << endl;
	cout << FRobject->result << endl;

	// Проверка целочисленного деления на том же массиве
	FRobject = newObject.executeFunction(4, divTestMas); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject << endl;
	cout << FRobject->type << endl;
	cout << FRobject->result << endl;
	
	cout << "- - - " << newObject.executeFunction(4, divTestMas)->result + newObject.executeFunction(4, divTestMas)->result << endl;

	// Проверка Установка рандомайзера. не важно что передаем в аргументах
	FRobject = newObject.executeFunction(5, divTestMas); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject << endl;
	cout << FRobject->type << endl;
	cout << FRobject->result << endl;

	// Проверяем рандомайзер 
	FRobject = newObject.executeFunction(6, randTestMas); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject->result << endl;
	FRobject = newObject.executeFunction(6, randTestMas); // не забываем что этот объект ссылается на свойство newObject. 
	cout << FRobject->result << endl;
	

	return 0;
}
