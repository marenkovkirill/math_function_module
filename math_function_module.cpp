
#include "Function_module.h"

using namespace std;

///////////////// Тестовые классы и структуры
struct FS {
	int first;
	int second;
};
    
class FuncModule {
protected:
	virtual FS** getFunc() = 0;
};

class FuncRealized : public FuncModule{

public:
	FS InnerClassFS; //Объявлена структура типа FS
	FS **robot_functions;
	FS** getFunc(){ //функция/метод должна вернуть указатель на указатель на структуру типа ФС
		cout << "getFunc WORKS!" << endl;

		InnerClassFS.first = 11;
		InnerClassFS.second = 20;

		FS *pTestFS;    // Указатель на структуру типа FS
		static FS **ppTestFS;  // Указатель на указатель на структуру типа FS
		pTestFS = &InnerClassFS; //присваиваем адрес структуры описанной в классе
		ppTestFS = &pTestFS;  //присваеваем адрес адреса структуры опис. в классе
		// Проверка значений указателей
		cout << pTestFS << " Указатель на структуру " << endl;
		cout << ppTestFS << " Указатель на указатель на структуру " << endl;
		robot_functions = new FS*[1];
		return robot_functions;
	};
	FuncRealized() {
		//robot_functions = new FS*[COUNT_MATH_FUNCTIONS];
		int function_id = 0;
	};
};
/////////////////// конец тестовых классов и структур





// Опишу функцию вне класса чтобы можно было применять cout
FunctionResult* MathFunctionModule::executeFunction(regval functionId, regval *args){
	cout << "Func executed" << endl;
	if (functionId == 1) {
		cout << "a+b = a+b" << endl;
	} //endIf
	//char ch1 = '1';
	char ch4 = '1';
	//FunctionResult  *rez2;
	//char ch4='1';
	rez = new FunctionResult(ch4);
	return rez;
};





int main(){

	FS **pointFStruct; // Объявили указатель на указатель на структуру типа FS
	FS *pFSStruct;
	regval *arg1;
	regval x;
	x = 1;
	arg1 = &x;

	FuncRealized FRealObject; // Объявили объект

	pointFStruct = FRealObject.getFunc();  // Сработала функция/метод
	pFSStruct = (*(pointFStruct));
	cout << pointFStruct << " _ _ _ " << pFSStruct << " _ _ _ " <<*(pointFStruct) << endl; // Выведем Указатель на указатель и Указатель
	cout << pointFStruct << " _ _ _ " << pFSStruct << " _ _ _ " << *(pointFStruct) << endl; // Выведем Указатель на указатель и Указатель
	cout << pointFStruct << " _ _ _ " << pFSStruct << " _ _ _ " << *(pointFStruct) << endl; // Выведем Указатель на указатель и Указатель
	cout << pointFStruct << " _ _ _ " << *(pointFStruct) << endl; // Выведем Указатель на указатель и Указатель
	cout << pointFStruct << " _ _ _ " << *(pointFStruct) << endl; // Выведем Указатель на указатель и Указатель

	cout << (*(pointFStruct)) << endl;
	cout << &(FRealObject.InnerClassFS.first) << endl;

	MathFunctionModule newObject;

	char ch3 = '1';
	FunctionResult *FRobject;

	cout << newObject.testInt << endl;
	newObject.testInt = 1;
	cout << newObject.testInt << endl;

	FRobject = newObject.executeFunction(1,arg1);
	cout << FRobject << endl;
	cout << FRobject << endl;
	cout << FRobject << endl;

	return 0;
}
