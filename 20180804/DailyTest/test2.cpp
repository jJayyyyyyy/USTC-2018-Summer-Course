/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
参考: https://blog.csdn.net/tigerisland45/article/details/71305826
采用递归的做法
如 n = a * b
那么当a≠b的时候, 【n 的可分解方案】 = 【a 的可分解方案】 + 【b 的可分解方案】
*/
class Solution{
public:
	int cntFactorPlan(int n, int start){
		if( n == 1 ){
			return 1;
		}else{
			int cnt = 0;
			for( int i = start; i <= n; i++ ){
				if( n % i == 0 ){
					int partialCnt = cntFactorPlan(n/i, i);
					cnt += partialCnt;
				}
			}
			return cnt;
		}
	}
};


int main(){
	Solution s;
	
	cout<<s.cntFactorPlan(2, 2)<<'\n';
	cout<<s.cntFactorPlan(4, 2)<<'\n';
	cout<<s.cntFactorPlan(8, 2)<<'\n';
	cout<<'\n';
	cout<<s.cntFactorPlan(4, 2)<<'\n';
	cout<<s.cntFactorPlan(5, 2)<<'\n';
	cout<<s.cntFactorPlan(20, 2)<<'\n';

	return 0;
}