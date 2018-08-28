#include <iostream>
#include <cmath>
#include <sstream>
#include <cctype>
using namespace std;

class Solution{
public:
	unsigned int str2int(string s){
		stringstream ss(s);
		unsigned int ans;
		ss>>ans;
		return ans;
	}
	
	unsigned int convertIPv4toInt(string ip){
		unsigned int ans = 0;

		if( ip.size() == 0 ){
			cout<<"Empty IPv4 address\n";
			return 1;
		}

		ip.push_back('.');
		
		string part = "";
		// string seq = "";
		int weight = 24;
		int cntDot = 0;
		for(int i = 0; i < ip.size(); i++ ){
			char ch = ip[i];
			if( ch != '.' ){
				if( isdigit(ch) == false ){
					cout<<"IPv4 address consist of only digit and dot\n";
					return 2;
				}
				part += ch;
			}else{
				cntDot++;
				if( cntDot > 4 ){
					cout<<"Invalid IPv4 address, too many dots\n";
					return 3;
				}

				if( i > 0 && ip[i-1] == '.' ){
					cout<<"Invalid IPv4 address, consecutive dots\n";
					return 4;
				}

				unsigned int partAns = str2int(part);
				if( partAns > 255 ){
					// 不用考虑 partAns < 0 的情况, 因为负号已经归类于非法字符
					cout<<"Invalid IPv4 address, out of range\n";
					return 5;
				}

				ans += partAns * pow(2, weight);
				weight -= 8;
				part = "";
			}
		}
		if( cntDot < 4 ){
			cout<<"Invalid IPv4 address, too few dots\n";
			return 6;
		}
		cout<<ans<<'\n';
		return ans;
	}
};

int main(){
	Solution s;
	
	s.convertIPv4toInt("0.0.0.0");
	s.convertIPv4toInt("0.0.0.1");
	s.convertIPv4toInt("0.0.1.0");
	s.convertIPv4toInt("0.1.0.0");
	s.convertIPv4toInt("1.0.0.0");
	s.convertIPv4toInt("255.255.255.255");


	cout<<"\n\n\n";
	s.convertIPv4toInt("");			// 空串
	s.convertIPv4toInt("0.0");		// 太短了
	s.convertIPv4toInt("0.0.0.0.");	// 多了一个 dot
	s.convertIPv4toInt("0...0");		// 连续的 dot
	s.convertIPv4toInt("0.0.0.0.0");	// 太长了
	s.convertIPv4toInt("-1.0.0.0");	// 将负号归类于非法字符
	s.convertIPv4toInt("-1,0.0,0");	// 逗号, 非法字符
	s.convertIPv4toInt("1024.0.0,0");	// 超出范围

	return 0;
}
