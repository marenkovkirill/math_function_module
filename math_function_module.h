
/*
* File: math_function_module.h
* Author: m79lol, iskinmike
*
*/

#ifndef MATH_FUNCTION_MODULE_H
#define MATH_FUNCTION_MODULE_H

class MathFunctionModule : public FunctionModule {
  FunctionData **math_functions;

#if MODULE_API_VERSION > 000
  ModuleInfo *mi;
#endif

 public:
  MathFunctionModule();

  // init
#if MODULE_API_VERSION > 000
  const struct ModuleInfo &getModuleInfo();
#else
  const char *getUID();
#endif
  void prepare(colorPrintfModule_t *colorPrintf_p,
               colorPrintfModuleVA_t *colorPrintfVA_p){};

  // compiler only
  FunctionData **getFunctions(unsigned int *count_functions);
  void *writePC(unsigned int *buffer_length);

  // intepreter - devices
#if MODULE_API_VERSION > 100
  int init();
  void final() {};
  
  // intepreter - program & lib
  int readPC(int pc_index, void *buffer, unsigned int buffer_length);
  // intepreter - program
  int startProgram(int run_index, int pc_index);
#else
  // intepreter - program & lib
  void readPC(void *buffer, unsigned int buffer_length) {};
  // intepreter - program
  int startProgram(int run_index);
#endif

  FunctionResult *executeFunction(system_value function_index, void **args);
  int endProgram(int run_index);

  // destructor
  void destroy();
  ~MathFunctionModule(){};
};

#endif /* MATH_FUNCTION_MODULE_H  */
