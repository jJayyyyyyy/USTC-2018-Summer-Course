/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct PrimePair{
	int a, b;
	PrimePair(int _a, int _b){
		a = _a;
		b = _b;
	}
};

/*
先构造素数表 https://github.com/jJayyyyyyy/OJ/blob/master/tools/Question1.md
然后遍历该表，寻找素数对
*/
class Solution{
public:
	vector<bool> primeList;

	void initPrimeList(int n){
		primeList[0] = false;
		primeList[1] = false;
		primeList[2] = true;
		
		for( int i = 3; i < n; i += 2 ){
			primeList[i] = true;
			primeList[i + 1] = false;
		}

		int upperBound = (int)sqrt(n);
		for( int i = 3; i < upperBound; i += 2 ){
			if( primeList[i] == true ){
				for( int j = i + i; j < n; j += i ){
					primeList[j] = false;
				}
			}
		}
	}

	vector<PrimePair> getPrimePair(int n){
		vector<PrimePair> ans;
		if( n > 3 ){
			primeList.resize(n + 5);
			initPrimeList(n);

			for( int i = 5; i < n; i++ ){
				if( primeList[i-2] == true && primeList[i] == true ){
					ans.push_back( PrimePair(i-2, i) );
				}
			}
		}

		return ans;
	}
};


int main(){
	Solution s;
	
	vector<PrimePair> ans = s.getPrimePair(20);
	for( auto pair : ans ){
		cout<<pair.a<<' '<<pair.b<<'\n';
	}

	return 0;
}