/*
如果有bug，欢迎发出issue和pr ^_^
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <regex>
using namespace std;

class Solution1{
public:
	int cntPeach(int totalDay){
		int ans = 1;
		// 倒推
		for( int i = totalDay; i > 1; i-- ){
			ans = (ans + 1) * 2;
		}
		return ans;
	}
};

/*
第2题原来的题意一开始让人看不懂, 建议搜索相关的关键词, 并参考以下链接。
https://blog.csdn.net/pqleo/article/details/23625389
https://en.wikipedia.org/wiki/Georg_Cantor

重画了表格和图示之后就好理解一些了。从图中我们可以发现如下规律:
1. 第i行有i个数
2. 第i行, 每个数的分子分母之和, 都是 i + 1
3. 【奇数行分母】从1开始递增, 而【偶数行分子】从1开始递增

*/
class Solution2{
public:
	string enumRationalNumber(int n){
		if( n >= 1){
			int row = 0;
			int sum = 0;
			while( sum < n ){
				row++;
				sum += row;
			}

			// 此时的 row 是 n 所在的这一行
			sum -= row;	// 在第 row 行之前, 一共有sum个数
			int offset = n - sum;	// 因此 n - sum 就是第 n 个数在第 row 行的偏移量
			// 这样我们就可以根据规律2和3来得到分子和分母
			
			string numerator;	// 分子
			string denominator;	// 分母
			if( row % 2 == 0 ){
				numerator = to_string(offset);
				denominator = to_string(row + 1 - offset);
			}else{
				denominator = to_string(offset);
				numerator = to_string(row + 1 - offset);
			}

			return numerator + "/" + denominator;
		}else{
			return NULL;
		}
	}
};

class Solution3{
public:
	vector<int> getPerfectNumber(int upperbound){
		vector<int> ans;
		for( int num = 1; num < upperbound; num++ ){
			int sum = 1;
			for( int factor = 2; factor < num; factor++ ){
				if( num % factor == 0 ){
					sum += factor;
				}
				if( sum > num ){
					break;
				}
			}
			if( sum == num ){
				ans.push_back(num);
			}
		}
		return ans;
	}
};

class Solution4{
public:
	int calDay(){
		// 略
		return 0;
	}
};

/*
getline的用法
http://www.cplusplus.com/reference/string/string/getline/?kw=getline
*/
class Solution5{
public:
	int cntWord(string s){
		istringstream iss(s);
		string word;
		char delim = ' ';	// delimitation, 分界符
		int cnt = 0;
		while( getline(iss, word, delim) ){
			cnt++;
		}
		return cnt;
	}
};

/*
c++ regex
http://www.cplusplus.com/reference/regex/regex_match/
*/
class Solution6{
public:
	bool matchWord(string s, string word){
		string pattern = "(.*)" + word + "(.*)";
		return regex_match( s, regex(pattern) );
	}
	
	// http://www.cplusplus.com/reference/string/string/find/
	bool matchWord2(string s, string word){
		return s.find(word) != string::npos;
	}
};

//http://www.cplusplus.com/reference/vector/vector/insert/
class Solution7{
public:
	vector<int> sortAndInsert(int n){
		vector<int> ans;
		int val;
		for( int i = 0; i < n; i++ ){
			cin>>val;
			ans.push_back(val);
		}
		sort(ans.begin(), ans.end());

		cin>>val;
		auto it = ans.begin();
		for( ; it != ans.end(); it++ ){
			if( *it >= val ){
				break;
			}
		}
		ans.insert(it, val);
		return ans;
	}
};

class Solution8{
public:
	vector<int> largerThanAverage(int n){
		vector<int> v, ans;
		int val, sum=0;
		for( int i = 0; i < n; i++ ){
			cin>>val;
			sum += val;
			v.push_back(val);
		}
		int ave = (int)(sum * 1.0 / n);
		for( int num : v ){
			if( num > ave ){
				ans.push_back(num);
			}
		}
		return ans;
	}
};

int main(){
	// Solution1 s1;
	// cout<<s1.cntPeach(1)<<'\n';	// 1
	// cout<<s1.cntPeach(2)<<'\n';	// 4
	// cout<<s1.cntPeach(3)<<'\n';	// 10
	// cout<<s1.cntPeach(10)<<'\n';	// 1534, 话说这猴子好能吃
	
	
	// Solution2 s2;
	// cout<<s2.enumRationalNumber(1)<<'\n';
	// cout<<s2.enumRationalNumber(2)<<'\n';
	// cout<<s2.enumRationalNumber(3)<<'\n';
	// cout<<s2.enumRationalNumber(4)<<'\n';
	// cout<<s2.enumRationalNumber(5)<<'\n';
	// cout<<s2.enumRationalNumber(6)<<'\n';
	// cout<<s2.enumRationalNumber(7)<<'\n';
	// cout<<s2.enumRationalNumber(10)<<'\n';
	
	// Solution3 s3;
	// vector<int> ans = s3.getPerfectNumber(1000);
	// for( int num : ans ){
	// 	cout<<num<<' ';
	// }
	// cout<<'\n';
	
	
	// Solution5 s5;
	// cout<<s5.cntWord("hello")<<'\n';
	// cout<<s5.cntWord("hello world")<<'\n';
	// cout<<s5.cntWord("have a nice day.")<<'\n';
	
	// Solution6 s6;
	// cout<<s6.matchWord2("hello", "debug")<<'\n';
	// cout<<s6.matchWord("debug", "debug")<<'\n';
	// cout<<s6.matchWord("debugging", "debug")<<'\n';
	// cout<<s6.matchWord("to debug", "debug")<<'\n';
	// cout<<s6.matchWord("to debugy", "debug")<<'\n';
	// cout<<s6.matchWord("to debuff", "debug")<<'\n';

	// Solution7 s7;
	// vector<int> ans = s7.sortAndInsert(5);
	// for( auto num : ans ){
	// 	cout<<num<<' ';
	// }
	// cout<<'\n';

	// Solution8 s8;
	// vector<int> ans = s8.largerThanAverage(5);
	// for( auto num : ans ){
	// 	cout<<num<<' ';
	// }
	// cout<<'\n';

	return 0;
}