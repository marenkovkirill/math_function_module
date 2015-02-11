
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
		case 1:
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
	
		case 5: // Корень 2-й степени
		{
			int resOfsqrt;
			resOfsqrt = (int) sqrt(*args);
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
		case 7: // Синус
		{
			int resOfsin;
			resOfsin = (int) (1000 * sin(*args)) ;
			rez->result = resOfsin;
			// Все сделали и выходим из свича
			break;
		}
		case 8: // Косинус
		{
			int resOfcos;
			resOfcos = (int)(1000 * cos(*args));
			rez->result = resOfcos;
			// Все сделали и выходим из свича
			break;
		}
		case 9: // Тангенс
		{
			int resOftan;
			resOftan = (int)(1000 * tan(*args));
			rez->result = resOftan;
			// Все сделали и выходим из свича
			break;
		}
		case 10: // АркСинус
		{
			int resOfasin;
			resOfasin = (int)(1000 * asin(*args));
			rez->result = resOfasin;
			// Все сделали и выходим из свича
			break;
		}
		case 11: // АркКосинус
		{
			int resOfacos;
			resOfacos = (int)(1000 * acos(*args));
			rez->result = resOfacos;
			// Все сделали и выходим из свича
			break;
		}
		case 12: // АркТангенс
		{
			int resOfatan;
			resOfatan = (int)(1000 * atan(*args));
			rez->result = resOfatan;
			// Все сделали и выходим из свича
			break;
		}
		case 13: // Экспонента
		{
			int resOfexp;
			resOfexp = (int) exp(*args);
			rez->result = resOfexp;
			// Все сделали и выходим из свича
			break;
		}
		case 14: // Логарифм Натуральный
		{
			int resOflog;
			resOflog = (int)log(*args);
			rez->result = resOflog;
			// Все сделали и выходим из свича
			break;
		}
		case 15: // Десятичный логарифм
		{
			int resOflog10;
			resOflog10 = (int)log10(*args);
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
