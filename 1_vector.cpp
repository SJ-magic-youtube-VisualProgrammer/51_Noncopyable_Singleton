/************************************************************
参考URL
	http://blpr.net/?p=263
	
description
	vectorで、
	"ポインタではなく"、
	オブジェクト自体を取り扱う場合、push_backしたときに次のことが行われています。
		*	push_backの対象となるオブジェクトをコピーコンストラクタでコピー
		*	既にpush_back済みのものがあれば、再びコピーコンストラクタでそのコピーを作り、元々コピーしてあったものをデストラクタで始末する。
	
Consideration
	vectorでオブジェクト自体を持つのは避けるのが良いかもしれない。
	vectorが廃棄される時に、自動でobjectのdestructorが呼ばれる、と言うメリットはあるものの、
	vectorの「気遣い」であるコピーコンストラクタ、デストラクタに、反って戸惑わされる恐れがあるからです。
	それよりも「後始末をしっかりする」ことさえ注意していればよい「ポインタを持つ」方が楽なのでは、と考えています。
************************************************************/
#include <stdio.h>
#include <vector>

using std::vector;

/************************************************************
************************************************************/
class HOGE{
private:
	int id;
	
public:
	HOGE(int _id) : id(_id)
	{
		printf("constructor:id_%d\n", id);
	}
	
	HOGE(const HOGE& org) : id(org.id)
	{
		printf("copy constructor:id_%d\n", id);
	}
	
	~HOGE()
	{
		printf("destructor:id_%d\n", id);
	}
	
	HOGE& operator=(const HOGE& org)
	{
		id = org.id;
		printf("ope= : id_%d\n", id);
		
		return *this;
	}
};

/************************************************************
************************************************************/
int main()
{
	int point = 0;
	
	printf("%d----------\n", point++);				// ----------
	HOGE Hoge0(0);									// constructor:id_0
	printf("%d----------\n", point++);				// ----------
	HOGE Hoge1(1);									// constructor:id_1
	printf("%d----------\n", point++);				// ----------
	HOGE Hoge2(2);									// constructor:id_2
	printf("%d----------\n", point++);				// ----------
	vector<HOGE> Array;
	printf("%d----------\n", point++);				// ----------
	
	Array.push_back(Hoge0);							// copy constructor:id_0
	for(int i = 0; i < Array.size(); i++){			// Array[0] : 0x7fbdd1c05c90
		printf("Array[%d] : %p\n", i, &Array[i]);
	}
	printf("%d----------\n", point++);				// ----------
	Array.push_back(Hoge1);							// copy constructor:id_1
													// copy constructor:id_0
													// destructor:id_0
	for(int i = 0; i < Array.size(); i++){			// Array[0] : 0x7fbdd1c05a90
		printf("Array[%d] : %p\n", i, &Array[i]);	// Array[1] : 0x7fbdd1c05a94
	}
	printf("%d----------\n", point++);				// ----------
	Array.push_back(Hoge2);							// copy constructor:id_2
													// copy constructor:id_1
													// copy constructor:id_0
													// destructor:id_1
													// destructor:id_0
	for(int i = 0; i < Array.size(); i++){			// Array[0] : 0x7fbdd1c05c90
		printf("Array[%d] : %p\n", i, &Array[i]);	// Array[1] : 0x7fbdd1c05c94
	}												// Array[2] : 0x7fbdd1c05c98
	printf("%d----------\n", point++);				// ----------
													// destructor:id_2		// vectorの掃除
													// destructor:id_1
													// destructor:id_0
													// destructor:id_2		// Hoge0 - Hoge2 の掃除
													// destructor:id_1
													// destructor:id_0
	return 0;
}

