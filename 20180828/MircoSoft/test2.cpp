#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

class Solution{
public:
	unsigned int str2int(string s){
		stringstream ss(s);
		unsigned int ans;
		ss>>ans;
		return ans;
	}
	
	unsigned int convertIPv4(string ip){
		unsigned int ans = 0;
		ip.push_back('.');
		
		string part = "";
		int weight = 24;
		for(int i = 0; i < ip.size(); i++ ){
			if( ip[i] != '.' ){
				part += ip[i];
			}else{
				ans += str2int(part) * pow(2, weight);
				weight -= 8;
				part = "";
			}
		}
		cout<<ans<<'\n';
		return ans;
	}
};

int main(){
	Solution s;
	
	s.convertIPv4("0.0.0.0");
	s.convertIPv4("0.0.0.1");
	s.convertIPv4("0.0.1.0");
	s.convertIPv4("0.1.0.0");
	s.convertIPv4("1.0.0.0");
	s.convertIPv4("255.255.255.255");
	return 0;
}

/*
TODO:
处理非法输入
*/