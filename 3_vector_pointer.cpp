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

class myClass {
public:
	myClass() { mX = new int(); }
	~myClass() { delete mX; printf("destructor:myClass\n"); }
	int* mX;
	
private:
	myClass(const myClass &);
	void operator=( const myClass &);
};

vector< myClass* > gArray;
int vec_size = 0;

// vector< myClass > gArray2;

int main() {
	vec_size++;
	gArray.resize(vec_size);
	gArray[vec_size - 1] = new myClass();
	
	/*
	{
		myClass obj;
		gArray2.push_back(obj);
	}
	*/

	*( gArray[ 0 ]->mX ) = 6;
	printf("%d\n", *( gArray[ 0 ]->mX ));
	
	printf("gArray.size() = %d\n", gArray.size());
	for(int i = 0; i < gArray.size(); i++){
		delete gArray[i];
	}
	
	return 0;
}

