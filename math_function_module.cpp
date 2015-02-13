#include <stddef.h> // Чтобы определить NULL
#include <time.h> // для Рандомайзера 

///////// Включения основного модуля module.h
#include "Module.h"
#include "Function_Module.h"
#include "Math_Function_Module.h"

#include <math.h>
#include <iostream>

//using namespace std;

////////////// Установка Глобальных переменных.
// GLOBAL VARIABLES
int COUNT_MATH_FUNCTIONS = 15;

// Опишем макросс который будет заполнять наш массив структур с информацией о функциях. Ия функции, Присваивает уникальный индекс, число параметров и дает ли исключение.
#define ADD_MATH_FUNCTION(FUNCTION_NAME, COUNT_PARAMS, GIVE_EXCEPTION) \
math_functions[function_id] = new FunctionData; \
math_functions[function_id]->command_index = function_id + 1; \
math_functions[function_id]->count_params = COUNT_PARAMS; \
math_functions[function_id]->give_exception = GIVE_EXCEPTION; \
math_functions[function_id]->name = FUNCTION_NAME; \
function_id++;
// важная часть чтобы был уникальный параметр 
// начинается от нуля поэтому такой вид. В конструкторе перед использованием function_id будет присвоен ноль.
/////////////////////////////////////////////////////////////////////////////////

// Опишем макросс который все наши функции заполнит/ Добавил Функцию - Увеличивай их число COUNT_MATH_FUNCTIONS. А то удалишь нафиг какой-нить процесс в памяти.
#define DEFINE_ALL_FUNCTIONS \
	ADD_MATH_FUNCTION("pow",  2,false) \
	ADD_MATH_FUNCTION("abs",  1,false) \
	ADD_MATH_FUNCTION("mod",  2,false) \
	ADD_MATH_FUNCTION("div",  2,false) \
	ADD_MATH_FUNCTION("sqrt", 1,false) \
	ADD_MATH_FUNCTION("rand", 1,false) \
	ADD_MATH_FUNCTION("sin",  1,false) \
	ADD_MATH_FUNCTION("cos",  1,false) \
	ADD_MATH_FUNCTION("tan",  1,false) \
	ADD_MATH_FUNCTION("asin", 1,false) \
	ADD_MATH_FUNCTION("acos", 1,false) \
	ADD_MATH_FUNCTION("atan", 1,false) \
	ADD_MATH_FUNCTION("exp",  1,false) \
	ADD_MATH_FUNCTION("log",  1,false) \
	ADD_MATH_FUNCTION("log10",1,false) 
// Конец макроса

// Далее описание методов класса МathFunctionModule
// Метод UID 
const char* MathFunctionModule::getUID() {
	return "Math_Functions_dll";
};

// метод получения данных о наших функциях
FunctionData**  MathFunctionModule::getFunctions(int *count_functions){ // Эта функция даст указатель на массив струкктур где описаны функции
	*count_functions = COUNT_MATH_FUNCTIONS; // Присваиваем в переменную(параметр функции) число наших функций
	return math_functions;
};

// Конструктор класса
MathFunctionModule::MathFunctionModule() {// В этом конструкторе сразу создадим массив структур
	math_functions = new FunctionData*[COUNT_MATH_FUNCTIONS];// Использует глобальную переменную. Это выделение памяти под массив указателей на структуры FunctionData из MSDN
	regval function_id = 0; // С этим идентефикатором работает DEFINE_ALL_FUNCTIONS
	srand(time(NULL)); // зададим сразу рандомайзхер - вдруг пригодится
	DEFINE_ALL_FUNCTIONS
};

// Деструктор напишем отдельным методом. Он удалит структуры с нашими функциями и потом сам оъект.
void MathFunctionModule::destroy() {
	for (int j = 0; j < COUNT_MATH_FUNCTIONS; ++j) {
		delete math_functions[j];
	}
	delete[] math_functions;
	delete this;
};

// Метод - выполнить математическую функцию
FunctionResult* MathFunctionModule::executeFunction(regval functionId, regval *args){
	if ( (functionId<1) || (functionId >15) ) {
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
		rez->result = (int) pow((double) *args, (double) (*(args+1)) );
		// Все сделали и выходим из свича
		break;
	}
	case 2: // ABS модуль числа
	{
		rez->result = abs(*args);
		// Все сделали и выходим из свича
		break;
	}
	case 3: // FMOD Остаток от деления
	{
		rez->result = (int)fmod(*args, *(args + 1));
		// Все сделали и выходим из свича
		break;
	}
	case 4: // DIV Целочисленное деление
		rez->result = (*args - (int)fmod(*args, *(args + 1))) / (*(args + 1));
		// Все сделали и выходим из свича
		break;

	case 5: // Корень 2-й степени Результат будем выводить умноженным на 1000, потому что растет медленно(меняется медленно)
	{
		rez->result = (int)(1000 * sqrt(*args));
		// Все сделали и выходим из свича
		break;
	}
	case 6: // Рандомное целое число
	{
		rez->result = rand() % (*args) + (*(args + 1));
		// Все сделали и выходим из свича
		break;
	}
	case 7: // Синус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
	{
		rez->result = (int)(1000 * sin(((double)*args) / 1000));
		// Все сделали и выходим из свича
		break;
	}
	case 8: // Косинус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
	{
		rez->result = (int)(1000 * cos(((double)*args) / 1000));
		// Все сделали и выходим из свича
		break;
	}
	case 9: // Тангенс Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
	{
		rez->result = (int)(1000 * tan(((double)*args) / 1000));
		// Все сделали и выходим из свича
		break;
	}
	case 10: // АркСинус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
	{
		rez->result = (int)(1000 * asin(((double)*args) / 1000));
		// Все сделали и выходим из свича
		break;
	}
	case 11: // АркКосинус Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
	{
		rez->result = (int)(1000 * acos(((double)*args) / 1000));
		// Все сделали и выходим из свича
		break;
	}
	case 12: // АркТангенс Изменяется быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000 и выводить будем умножив на 1000, потому что быстро меняется в малых пределах
	{
		rez->result = (int)(1000 * atan(((double)*args) / 1000));
		// Все сделали и выходим из свича
		break;
	}
	case 13: // Экспонента Растет быстро поэтому ввод просим умножить на 1000 а в вычислениях введенное будем делить на 1000
	{
		rez->result = (int)exp(((double)*args) / 1000);
		// Все сделали и выходим из свича
		break;
	}
	case 14: // Логарифм Натуральный Растет медленно поэтому вывод умножим на 1000
	{
		rez->result == (int)(1000 * log((double)*args));
		// Все сделали и выходим из свича
		break;
	}
	case 15: // Десятичный логарифм Растет медленно поэтому вывод умножим на 1000
	{
		rez->result = (int)(1000 * log10((double)*args));
		// Все сделали и выходим из свича
		break;
	}
	}; // Конец switch
	return rez;
};

__declspec(dllexport) FunctionModule* getFunctionModuleObject() {  // Нужная нам функция, вызвав ее в программе мы должны получить доступ к математическим функциям. Видимо определить их имена и т.д.
		return new MathFunctionModule();
};
