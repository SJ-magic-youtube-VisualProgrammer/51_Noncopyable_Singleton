/************************************************************
参考URL
	Singleton
		http://marupeke296.com/DP_Singleton.html

	wikipedia
		https://ja.wikipedia.org/wiki/Singleton_%E3%83%91%E3%82%BF%E3%83%BC%E3%83%B3#C.2B.2B.E3.81.A7.E3.81.AE.E5.AE.9F.E8.A3.85.E4.BE.8B
************************************************************/
#include <stdio.h>

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class SINGLETON{
private:
	SINGLETON()
	{
		printf("CONSTRUCTOR\tSINGLETON\n");
	}
	
	~SINGLETON()
	{
		printf("DESTRUCTOR\tSINGLETON\n");
	}
	
	SINGLETON(const SINGLETON&);				// Copy constructor. no define. 
	SINGLETON& operator=(const SINGLETON&);		// コピー代入演算子. no define.
	
public:
	static SINGLETON& getInstance(){
		static SINGLETON inst;
		return inst;
	}
	
	void func()
	{
		printf("singleton:func:%p\n", this);
	}
};

/**************************************************
**************************************************/
class USER{
private:
	SINGLETON& Singleton;
	int id;
	
public:
	USER(int _id)
	: Singleton(SINGLETON::getInstance())
	, id(_id)
	{
		printf("CONSTRUCTOR\tUSER_%d\n", id);
	}
	
	~USER()
	{
		printf("DESTRUCTOR\tUSER_%d\n", id);
	}
	
	void func(){
		Singleton.func();
	}
};

/************************************************************
************************************************************/
int main()
{
	printf("<Start>\n");	// <Start>
	
	USER user_0(0);			// CONSTRUCTOR	SINGLETON
							// CONSTRUCTOR	USER_0
	USER user_1(1);			// CONSTRUCTOR	USER_1
	user_0.func();			// singleton:func:0x10dcbb038
	user_1.func();			// singleton:func:0x10dcbb038
	
	printf("<Finish>\n");	// <Finish>
							// DESTRUCTOR	USER_1
							// DESTRUCTOR	USER_0
							// DESTRUCTOR	SINGLETON
	
	return 0;
}
