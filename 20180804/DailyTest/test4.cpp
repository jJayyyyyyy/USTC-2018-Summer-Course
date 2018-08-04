/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p
*/
#include <iostream>
#include <vector>
using namespace std;

/*
JosephList() 对应本题的逐个输出
如果要求最后的幸存者，对应的函数是 JosephSurvivor(), 参考 readme 链接
*/
class Solution{
public:

	// 这个解法的时间复杂度挺大的...
	vector<int> JosephList(int n, int m){
		vector<int> outList;
		if( n > 0 && m > 0 ){
			vector<bool> survivor(n, true);

			int cursor = 0, cntM = 1, cntSurvivor = n;
			while( cntSurvivor != 0 ){
				if( cntM == m ){
					cntM = 1;	// cntM 范围是 [1, m]
					while( cntSurvivor != 0 && survivor[cursor] == false ){
						cursor = ( cursor + 1 ) % n;	// 跳过已经出局的人
					}

					
					survivor[cursor] = false;	// 此时下标为 cursor 的人就要出局了 
					outList.push_back(cursor);
					cntSurvivor--;	// 剩余幸存者 -1
				}

				cntM++;

				while( cntSurvivor != 0 && survivor[cursor] == false ){
					cursor = ( cursor + 1 ) % n;
				}
				cursor = ( cursor + 1 ) % n;
			}
		}
		return outList;
	}

	int JosephSurvivor1(int n, int m){
		int ans = 0;
		for( int i = 2; i <= n; i++ ){
			ans = (ans + m) % i;
		}
		cout<<ans<<'\n';
		return ans;
	}

	int JosephSurvivor2(int n, int m){
		if( n == 1 ){
			return 0;
		}else{
			int ans = ( JosephSurvivor2(n-1, m) + m ) % n;
			return ans;
		}
	}
};


int main(){
	Solution s;
	vector<int> ans;

	ans = s.JosephList(7, 3);
	for( int num : ans ){
		cout<<num<<' ';
	}
	cout<<'\n';

	ans = s.JosephList(4, 2);
	for( int num : ans ){
		cout<<num<<' ';
	}
	cout<<'\n';

	return 0;
}
