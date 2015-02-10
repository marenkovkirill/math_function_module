
/*
* File: math_function_module.h
* Author: m79lol, iskinmike
*
*/

#ifndef FUNCTION_MODULE_H
#define	FUNCTION_MODULE_H
class FunctionModule {
protected:
	FunctionModule() {}
public:
	virtual const char *getUID() = 0;
	virtual FunctionData** getFunctions(int *count_functions) = 0;
	virtual FunctionResult* executeFunction(regval functionId, regval *args) = 0;
	virtual void destroy() = 0;
	virtual ~FunctionModule() {};
};

// Необходимо описать новый класс который будет наследовать свойства класса FunctionModule


///////////// Все что ниже мы включим в .срр  файл будущей dll библиотеки, а пока пишем здесь

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
	ADD_MATH_FUNCTION("pow",2,false) \
	ADD_MATH_FUNCTION("abs",1,false) \
	ADD_MATH_FUNCTION("mod",2,false) \
	ADD_MATH_FUNCTION("div",2,false);
// Конец макроса


////////////// Установка Глобальных переменных.
// GLOBAL VARIABLES
int COUNT_MATH_FUNCTIONS = 6;


////////////// Установка доп параметров заголовков и прочего
//////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\*****
/////////////////////////////////////////////////////////////////////\//////\\\/\\///\//\//*****
///////*****************************************************************************************


// Опишем сначала производный класс от FunctionModule
class MathFunctionModule:public FunctionModule {
public:
	// Опишем сначала свойства класса, чтобы потом к ним обращаться
	FunctionData **math_functions; // Это будет указатель на массив из структур куда запишем данные о математических функциях 
	
	// Мы создадим заранее свойство чтобы записывать в него результат вычислений мат. функции
	FunctionResult* rez;

	// Функция UID 
	const char *getUID() {
			return "Math_Functions_dll";
	};

	FunctionData **getFunctions(int *count_functions){ // Эта функция даст указатель на массив струкктур где описаны функции
		*count_functions = COUNT_MATH_FUNCTIONS; // Присваиваем в переменную(параметр функции) число наших функций
		return math_functions;
	};

	// Конструктор класса
	MathFunctionModule() {// В этом конструкторе сразу создадим массив структур
		math_functions = new FunctionData*[COUNT_MATH_FUNCTIONS];// Использует глобальную переменную. Это выделение памяти под массив указателей на структуры FunctionData из MSDN
		regval function_id = 0; // С этим идентефикатором работает DEFINE_ALL_FUNCTIONS
		DEFINE_ALL_FUNCTIONS
	};

	// Объявляем функцию возвращающую результат вычислений
	FunctionResult* executeFunction(regval functionId, regval *args);

	// Деструктор напишем отдельным методом. Он удалит структуры с нашими функциями и потом сам оъект.
	void destroy() {
		for (int j = 0; j < COUNT_MATH_FUNCTIONS; ++j) {
			delete math_functions[j];
		}
		delete[] math_functions;
		delete this;
	};

	~MathFunctionModule() {};// не описываем деструктор но объявим его, так как он есть в базовом классе FunctionModule
};

typedef FunctionModule* (*getFunctionModuleObject_t)();
extern "C" {
	__declspec(dllexport) FunctionModule* getFunctionModuleObject() {  // Нужная нам функция, вызвав ее в программе мы должны получить доступ к математическим функциям. Видимо определить их имена и т.д.
		return new MathFunctionModule();
	};                        
}
#endif	/* FUNCTION_MODULE_H  */
