/************************************************************
■コピーコンストラクタ、代入演算子、デストラクタ
	http://tercel-tech.hatenablog.com/entry/2012/11/03/003302
	
	contents
		・	値オブジェクトを作成するときは「ビッグスリー」原則に従うことが重要である.
			->デストラクタ、コピーコンストラクタ、代入演算子の3つのメンバ関数は常に共存する必要がある
			
		・	最低でも「中でnewする型はSTLコンテナにポインタを入れる」をルールとして採用しよう。未熟な人は「STLコンテナにはポインタを入れる」をルールにしてしまうのも良い。
		・	さらに、間違いが起こらないように、中でnewをするクラスはコピーを禁止することを義務づけよう。いっそ、作るクラス全てを全部コピー禁止にしてもいい。
************************************************************/
#include <vector>
using namespace std;

//*
class myClass {
public:
	myClass()	{ mX = new int(); }
	~myClass()	{ delete mX; }
	int* mX;
};

/*/
class myClass {
public:
	myClass() { mX = new int(); }
	
	// コピーコンストラクタ
	explicit myClass(const myClass &a) {
		mX = new int(*a.mX);
	}

	// デストラクタ
	virtual ~myClass() {
		delete mX;
	}
	
	// 代入演算子のオーバーロード
	myClass &operator=(const myClass &a) {
		if(this != &a) {
			*mX = *a.mX;
		}
		return *this;
	}
	
	int *mX;
};
//*/

vector< myClass > g_Array;

int main() {
	{
		myClass obj;
		g_Array.push_back( obj );
	}
	
	*( g_Array[ 0 ].mX ) = 6;
	
	printf("%d\n", *( g_Array[ 0 ].mX ) );
	return 0;
}



