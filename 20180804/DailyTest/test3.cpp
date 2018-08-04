/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
http://www.cplusplus.com/reference/vector/vector/
*/
class Solution{
public:
	vector<int> insertSort(){
		vector<int> ans;
		int n, val;
		cin>>n;
		
		cin>>val;
		ans.push_back(val);
		
		for( int i = 1; i < n; i++ ){
			cin>>val;
			auto it = ans.begin();
			for( ; it != ans.end(); it++ ){
				if( *it > val ){
					break;
				}
			}
			ans.insert(it, val);
		}
		return ans;
	}

	vector<int> relocate(vector<int> & v){
		vector<int> odd, even, ans;
		for( int i = 0; i < v.size(); i++ ){
			if( v[i] % 2 == 1 ){
				odd.push_back(v[i]);
			}else{
				even.push_back(v[i]);
			}
		}
		ans = odd;
		for( int num : even ){
			ans.push_back(num);
		}
		return ans;
	}

	vector<int> fun(){
		vector<int> sortedVec = insertSort();
		return relocate(sortedVec);
	}
};


int main(){
	Solution s;
	
	vector<int> ans = s.fun();
	for( int num : ans ){
		cout<<num<<' ';
	}
	cout<<'\n';

	return 0;
}