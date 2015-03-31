#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../module_headers/module.h"
#include "../module_headers/function_module.h"
#include "math_function_module.h"

int COUNT_MATH_FUNCTIONS = 13;

#define ADD_MATH_FUNCTION(FUNCTION_NAME, COUNT_PARAMS, GIVE_EXCEPTION) \
	math_functions[function_id] = new FunctionData; \
	math_functions[function_id]->command_index = function_id + 1; \
	math_functions[function_id]->count_params = COUNT_PARAMS; \
	math_functions[function_id]->give_exception = GIVE_EXCEPTION; \
	math_functions[function_id]->name = FUNCTION_NAME; \
	function_id++;

#define DEFINE_ALL_FUNCTIONS \
	ADD_MATH_FUNCTION("pow",  2, false) \
	ADD_MATH_FUNCTION("abs",  1, false) \
	ADD_MATH_FUNCTION("sqrt", 1, true) \
	ADD_MATH_FUNCTION("rand", 2, true) \
	ADD_MATH_FUNCTION("sin",  1, false) \
	ADD_MATH_FUNCTION("cos",  1, false) \
	ADD_MATH_FUNCTION("tan",  1, false) \
	ADD_MATH_FUNCTION("asin", 1, true) \
	ADD_MATH_FUNCTION("acos", 1, true) \
	ADD_MATH_FUNCTION("atan", 1, false) \
	ADD_MATH_FUNCTION("exp",  1, false) \
	ADD_MATH_FUNCTION("log",  1, true) \
	ADD_MATH_FUNCTION("log10",1, true)

const char* MathFunctionModule::getUID() {
    return "Math_Functions_dll";
};

FunctionData**  MathFunctionModule::getFunctions(unsigned int *count_functions) {
    *count_functions = COUNT_MATH_FUNCTIONS;
    return math_functions;
};

MathFunctionModule::MathFunctionModule() {
    srand(time(NULL));
	
	math_functions = new FunctionData*[COUNT_MATH_FUNCTIONS];
	system_value function_id = 0;
    DEFINE_ALL_FUNCTIONS
};

void MathFunctionModule::destroy() {
    for (int j = 0; j < COUNT_MATH_FUNCTIONS; ++j) {
        delete math_functions[j];
    }
    delete[] math_functions;
    delete this;
};

FunctionResult* MathFunctionModule::executeFunction(system_value functionId, variable_value *args) {
	if ((functionId < 1) || (functionId > COUNT_MATH_FUNCTIONS)) {
        return NULL;
    }

    FunctionResult *rez = new FunctionResult(1);
	bool throw_exception = false;

    switch (functionId) {
		case 1: {
			rez->result = pow(*args, *(args + 1));
			break;
		}
		case 2: {
			rez->result = abs(*args);
			break;
		}
		case 3: {
			if (*args < 0) {
				throw_exception = true;
			}
			rez->result = sqrt(*args);
			break;
		}
		case 4: {
			if (*args <= 0) {
				throw_exception = true;
			}
			rez->result = (variable_value) (rand() % ((int) (*args)) + ((int) (*(args + 1))));
			break;
		}
		case 5: {
			rez->result = sin(*args);
			break;
		}
		case 6: {
			rez->result = cos(*args);
			break;
		}
		case 7: {
			rez->result = tan(*args);
			break;
		}
		case 8: {
			if ((*args < -1) && (*args > 1)) {
				throw_exception = true;
			}
			rez->result = asin(*args);
			break;
		}
		case 9: {
			if ((*args < -1) && (*args > 1)) {
				throw_exception = true;
			}
			rez->result = acos(*args);
			break;
		}
		case 10: {
			rez->result = atan(*args);
			break;
		}
		case 11: {
			rez->result = exp(*args);
			break;
		}
		case 12: {
			if (*args <= 0) {
				throw_exception = true;
			}
			rez->result = log(*args);
			break;
		}
		case 13: {
			if (*args <= 0) {
				throw_exception = true;
			}
			rez->result = log10(*args);
			break;
		}
    }

    if (throw_exception) {
        rez->type = 0;
    }
    return rez;
};

__declspec(dllexport) FunctionModule* getFunctionModuleObject() {
    return new MathFunctionModule();
};
