/************************************************************
■コピー禁止を徹底させるNoncopyableクラス
	http://marupeke296.com/DXCLS_Noncopyable.html
************************************************************/
#include <stdio.h>

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class Noncopyable{
public:
	Noncopyable(){}
	~Noncopyable(){}
	
private:
	Noncopyable(const Noncopyable& org);
	void operator=(const Noncopyable& org);
};

/**************************************************
**************************************************/
class MyClass : private Noncopyable{
	int *val;

public:
	MyClass() : val(new int(999)) {
	}
	
	~MyClass() {
		delete val;
	}
};

/************************************************************
************************************************************/
int main(){
	MyClass myObj_0;
	MyClass myObj_1;
	// myObj_1 = myObj_0;
	
	return 0;
}

