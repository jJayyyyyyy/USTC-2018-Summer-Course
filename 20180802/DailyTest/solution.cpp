/*

*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution2{
public:
	char encrypt(char input){
		if( input >= 'a' && input <= 'z' ){
			return (char)('z' - input + 'a');
		}else{
			return input;
		}
	}
};

class Solution4{
public:
	string encrypt(string strnum){
		if( strnum.size() == 4 ){
			for( int i = 0; i < 4; i++ ){
				strnum[i] = ( (strnum[i] - '0' + 7) % 10 ) + '0';
			}
			swap(strnum[0], strnum[2]);
			swap(strnum[1], strnum[3]);
		}
		return strnum;
	}

	string decrypt(string strnum){
		if( strnum.size() == 4 ){
			swap(strnum[0], strnum[2]);
			swap(strnum[1], strnum[3]);
			for( int i = 0; i < 4; i++ ){
				strnum[i] = ( (strnum[i] - '0' + 3) % 10) + '0';
			}
		}
		return strnum;
	}
};

int main(){
	Solution2 s2;
	cout<<s2.encrypt('a')<<'\n';	// z
	cout<<s2.encrypt('b')<<'\n';	// y
	cout<<s2.encrypt('c')<<'\n';	// x
	cout<<s2.encrypt('d')<<'\n';	// w
	cout<<s2.encrypt('e')<<'\n';	// v

	Solution4 s4;
	cout<<s4.encrypt("1234")<<'\n';	// 1234 -> 8901 -> 0189
	cout<<s4.decrypt("0189")<<'\n';	
	return 0;
}