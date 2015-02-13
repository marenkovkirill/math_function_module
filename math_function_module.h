
/*
* File: math_function_module.h
* Author: m79lol, iskinmike
*
*/

#ifndef MATH_FUNCTION_MODULE_H
#define	MATH_FUNCTION_MODULE_H

// Опишем  производный класс от FunctionModule
class MathFunctionModule :public FunctionModule {
public:
	// Опишем сначала свойства класса, чтобы потом к ним обращаться
	FunctionData **math_functions; // Это будет указатель на массив из структур куда запишем данные о математических функциях 
	// Мы создадим заранее свойство чтобы записывать в него результат вычислений мат. функци, Это для executeFunctions
	FunctionResult* rez;

	// Метод UID 
	const char *getUID();

	// Получение функций
	FunctionData **getFunctions(int *count_functions);

	// Объявляем функцию возвращающую результат вычислений
	FunctionResult* executeFunction(regval functionId, regval *args);

	// Конструктор класса
	MathFunctionModule();

	// Деструктор напишем отдельным методом. Он удалит структуры с нашими функциями и потом сам оъект.
	void destroy();

	~MathFunctionModule() {};// не описываем деструктор но объявим его, так как он есть в базовом классе FunctionModule
};

typedef FunctionModule* (*getFunctionModuleObject_t)();
extern "C" {
	__declspec(dllexport) FunctionModule* getFunctionModuleObject(); // Объявим в заголовочном а в теле опишем.
}

#endif	/* MATH_FUNCTION_MODULE_H  */
