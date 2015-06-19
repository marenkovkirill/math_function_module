#include <stdlib.h>
#include <exception>
#include <time.h>
#include <math.h>

#include <stdarg.h>

#include "module.h"
#include "function_module.h"
#include "math_function_module.h"

const unsigned int COUNT_MATH_FUNCTIONS = 13;

#define ADD_MATH_FUNCTION1(FUNCTION_NAME) \
	math_functions[function_id] = new FunctionData; \
	math_functions[function_id]->command_index = function_id + 1; \
	math_functions[function_id]->count_params = 1; \
	math_functions[function_id]->params = new FunctionData::ParamTypes[1]; \
	math_functions[function_id]->params[0] = FunctionData::FLOAT; \
	math_functions[function_id]->name = FUNCTION_NAME; \
	function_id++;
#define ADD_MATH_FUNCTION2(FUNCTION_NAME) \
	math_functions[function_id] = new FunctionData;\
	math_functions[function_id]->command_index = function_id + 1;\
	math_functions[function_id]->count_params = 2;\
	math_functions[function_id]->params = new FunctionData::ParamTypes[2];\
	math_functions[function_id]->params[0] = FunctionData::FLOAT;\
	math_functions[function_id]->params[1] = FunctionData::FLOAT;\
	math_functions[function_id]->name = FUNCTION_NAME; \
	function_id++;

#define DEFINE_ALL_FUNCTIONS \
	ADD_MATH_FUNCTION2("pow") \
	ADD_MATH_FUNCTION1("abs") \
	ADD_MATH_FUNCTION1("sqrt") \
	ADD_MATH_FUNCTION2("rand") \
	ADD_MATH_FUNCTION1("sin") \
	ADD_MATH_FUNCTION1("cos") \
	ADD_MATH_FUNCTION1("tan") \
	ADD_MATH_FUNCTION1("asin") \
	ADD_MATH_FUNCTION1("acos") \
	ADD_MATH_FUNCTION1("atan") \
	ADD_MATH_FUNCTION1("exp") \
	ADD_MATH_FUNCTION1("log") \
	ADD_MATH_FUNCTION1("log10")

MathFunctionModule::MathFunctionModule() {
	srand(time(NULL));

	math_functions = new FunctionData*[COUNT_MATH_FUNCTIONS];
	system_value function_id = 0;

	DEFINE_ALL_FUNCTIONS
};

const char* MathFunctionModule::getUID() {
    return "Math_Functions_dll";
};

FunctionData** MathFunctionModule::getFunctions(unsigned int *count_functions) {
    *count_functions = COUNT_MATH_FUNCTIONS;
    return math_functions;
};

void *MathFunctionModule::writePC(unsigned int *buffer_length) {
	*buffer_length = 0;
	return NULL;
}

FunctionResult* MathFunctionModule::executeFunction(system_value function_index, void **args) {
	if ((function_index < 1) || (function_index > ((int) COUNT_MATH_FUNCTIONS))) {
		return NULL;
	}

	try {
		variable_value *input = (variable_value *)(*args);
		variable_value rez = 0;
		switch (function_index) {
		case 1: {
					variable_value *input2 = (variable_value *)(*(args + 1));
					rez = pow(*input, *input2);
					break;
		}
		case 2: {
					rez = abs(*input);
					break;
		}
		case 3: {
					if ((*input) < 0) {
						throw std::exception();
					}
					rez = sqrt(*input);
					break;
		}
		case 4: {
					if ((*input) <= 0) {
						throw std::exception();
					}
					variable_value *input2 = (variable_value *)(*(args + 1));
					rez = (variable_value)(rand() % ((int)(*input)) + ((int)(*input2)));
					break;
		}
		case 5: {
					rez = sin(*input);
					break;
		}
		case 6: {
					rez = cos(*input);
					break;
		}
		case 7: {
					rez = tan(*input);
					break;
		}
		case 8: {
					if (((*input) < -1) && ((*input) > 1)) {
						throw std::exception();
					}
					rez = asin(*input);
					break;
		}
		case 9: {
					if (((*input) < -1) && ((*input) > 1)) {
						throw std::exception();
					}
					rez = acos(*input);
					break;
		}
		case 10: {
					 rez = atan(*input);
					 break;
		}
		case 11: {
					 rez = exp(*input);
					 break;
		}
		case 12: {
					 if (*input <= 0) {
						 throw std::exception();
					 }
					 rez = log(*input);
					 break;
		}
		case 13: {
					 if (input <= 0) {
						 throw std::exception();
					 }
					 rez = log10(*input);
					 break;
		}
		}
		return new FunctionResult(1, rez);
	}
	catch (...) {
		return new FunctionResult(0);
	}
};

int MathFunctionModule::startProgram(int uniq_index) {
	return 0;
}

void MathFunctionModule::readPC(void *buffer, unsigned int buffer_length) {
}

int MathFunctionModule::endProgram(int uniq_index) {
	return 0;
}

void MathFunctionModule::destroy() {
	for (unsigned int j = 0; j < COUNT_MATH_FUNCTIONS; ++j) {
		if (math_functions[j]->count_params) {
			delete[] math_functions[j]->params;
		}
        delete math_functions[j];
    }
    delete[] math_functions;
    delete this;
};

PREFIX_FUNC_DLL FunctionModule* getFunctionModuleObject() {
    return new MathFunctionModule();
};
