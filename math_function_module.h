
/*
* File: math_function_module.h
* Author: m79lol, iskinmike
*
*/

#ifndef MATH_FUNCTION_MODULE_H
#define	MATH_FUNCTION_MODULE_H

class MathFunctionModule : public FunctionModule {
	public:
		FunctionData **math_functions;
		const char *getUID();
		FunctionData **getFunctions(int *count_functions);
		FunctionResult* executeFunction(regval functionId, regval *args);
		MathFunctionModule();
		void destroy();
		~MathFunctionModule() {};
};

#endif	/* MATH_FUNCTION_MODULE_H  */
