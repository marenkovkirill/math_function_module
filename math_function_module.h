
/*
* File: math_function_module.h
* Author: m79lol, iskinmike
*
*/

#ifndef MATH_FUNCTION_MODULE_H
#define	MATH_FUNCTION_MODULE_H

class MathFunctionModule : public FunctionModule {
	FunctionData **math_functions;
	
	public:
		MathFunctionModule();
		const char *getUID();
		void prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p) {};
		FunctionData **getFunctions(unsigned int *count_functions);
		FunctionResult* executeFunction(system_value function_index, void **args);
		void destroy();
		~MathFunctionModule() {};
};

#endif	/* MATH_FUNCTION_MODULE_H  */
