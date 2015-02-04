/*
* File: module.h
* Author: m79lol
*
*/
///////////// Это временная мера, так как выдает ошибку NULL не определен. Надо будет его определить или что? хз.
#include <stddef.h>
///////////// Это временная мера, так как выдает ошибку NULL не определен. Надо будет его определить или что? хз.

#ifndef MODULE_H
#define	MODULE_H
typedef unsigned int regnum;  // Переопределим тип, чтобы проще было его поменять при необходимости.
typedef int regval;           // Переопределим тип, чтобы проще было его поменять при необходимости.

/////////////////////////////////////////////////////////////////////////////////////
struct FunctionData {  //  

	regval command_index; // Индекс команды. Его проще передавать чем имя команды, пожэтому всем командам будет присвоен индекс
	regval count_params;  // Число параметров функции индекс которой передается в структуру. Это для отлова ошибок. чтобы компилатор знал сколько параметров ему ожидать
	bool give_exception;  // Возвращает ли исключение данная функция. Да или нет. Это для обработки ошибок через try|Catch.
	const char *name;     // Имя Функции к которой обращаемся.

	// Видимо это конструктор структуры(класса), так как разница между классами и структурами только в доступе и неследовании этого доступа.
	// Создает "пустой" объект
	FunctionData() :  // Создает "пустой" объект
		command_index(0), count_params(0), give_exception(false), name(NULL) {}
	// Позволяет создавать заданные объекты
	FunctionData(regval command_index, regval count_params, bool give_exception, const char *name) : // Позволяет создавать заданные объекты
		command_index(command_index), count_params(count_params), give_exception(give_exception), name(name) {}
};


struct AxisData {
	regval axis_index;
	regval upper_value;
	regval lower_value;
	const char *name;
	AxisData() :
		axis_index(0), upper_value(0), lower_value(0), name(NULL) {}
	AxisData(regval axis_index, regval upper_value, regval lower_value, const char *name) :
		axis_index(axis_index), upper_value(upper_value), lower_value(lower_value), name(name) {}
};


////////////////////////////////////////////////////////////////////////////////////////////
class FunctionResult {  // Данный класс будет выступать в качестве типа возвращаемого значения функцией executeFunction (описана в файле заголовка Function_module.h)
						// Естественно будет возвращать указатель на объект данного класса.. что-то вроде этого, надо бы еще почитать, чтобы быть точным.
	char type;      //
	regval result;  //


public:
	// Первый конструктор класса
	FunctionResult(char type1) : //не понятно пока что будем передавать в качестве параметра. Окей это конструктор со списком инициализации. Почти то же самое что присваивание
		type(type1) {}
	FunctionResult(char type, regval result) :
		type(type), result(result) {}
	virtual void destroy() {
		delete this;
	}
};
#endif	/* MODULE_H */
