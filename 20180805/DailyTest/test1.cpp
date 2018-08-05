/*
alpha版的代码
TODO: 对变量名函数名以及程序结构等等进行调整和精简
TODO: 加上文件读写
TODO: 实现insertSort()
TODO: delete回收内存


在alpha版的代码中，假设有如下字符及其频度
A 1
B 1
C 2
D 3

则可以建立一棵这样的哈夫曼树
  7
 / \
D   4
   / \
  2   C
 / \
A   B
   
四个字母的编码分别为
A 100
B 101
C 11
D 0

1. 在这个程序里，我们首先建立一个数组，读取全部输入。其中，数组的每一个元素可以存储一个HTreeNode类型结点指针。对了，为了方便起见，我们把'#'当成空格
2. 然后我们对数组按照字母频度进行从小到大的排序。
3. 接着就是构造哈弗曼树啦，从数组中选取最小的两个元素，生成一个新的结点，再把这个结点插到数组的相应位置。如此一直重复，直到完成哈夫曼树的构建。
4. 接下来，我们使用前序遍历找到每一个结点，并进行哈夫曼编码。
5. 最后就是哈夫曼解码了，我们在之前的步骤中，已经完成了两个hash表，huffmancode和huffmandecode。哈夫曼编码无前缀，所以对于解码时候输入的01串，我们利用substr进行截取和对比，然后查表寻找其对应的字母即可
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

struct CharItem{
	char ch;
	int weight;

	CharItem(){
		ch = 0;
		weight = 0;
	}
	CharItem(char c, int f){
		ch = c;
		weight = f;
	}
};

struct HTreeNode{
	HTreeNode *lchild, *rchild;
	CharItem charitem;

	HTreeNode(CharItem item){
		charitem = item;
		lchild = rchild = NULL;
	}
};

vector<HTreeNode *> v;
string huffmancode[128];
unordered_map<string, char> huffmandecode;

bool cmp(HTreeNode * a, HTreeNode * b){
	if( a->charitem.weight != b->charitem.weight ){
		return a->charitem.weight < b->charitem.weight;
	}else{
		return a->charitem.ch < b->charitem.ch;
	}
}

void getInput(int n){
	char ch;
	int weight;
	for( int i = 0; i < n; i++ ){
		cin>>ch>>weight;
		if( ch == '#' ){
			ch = ' ';
		}

		v.push_back( new HTreeNode( CharItem(ch, weight) ) );
	}
	sort(v.begin(), v.end(), cmp);
}

void preTrav(HTreeNode * root, string code){
	if( root != NULL ){
		if( root->lchild == NULL && root->rchild == NULL ){
			char ch = root->charitem.ch;
			huffmancode[ch] += code;
		}
		preTrav(root->lchild, code + "0");
		preTrav(root->rchild, code + "1");
	}
}

void encode(){
	for( int ch = 'A'; ch <= 'Z'; ch++ ){
		string code = huffmancode[ch];
		if( code != "" ){
			huffmandecode[code] = ch;
		}
	}
}

string encodeABCD(){
	string ans = "";
	string toBeEncoded = "ABCD";
	for(char ch : toBeEncoded){
		ans += huffmancode[ch];
	}
	return ans;
}

// s is a string consists of 0 & 1
string decodeABCD(string s){
	string ans = "";

	for( int i = 0; i < s.size(); ){
		int j;
		for( j = 1; j < s.size(); j++ ){
			string subcode = s.substr(i, j);
			if( huffmandecode.find(subcode) != huffmandecode.end() ){
				ans += huffmandecode[subcode];
				break;
			}
		}
		i += j;
	}
	return ans;
}

void insertSort(HTreeNode * parent){
	sort(v.begin(), v.end(), cmp);
}

int main(){

	getInput(4);

	int ix = 1;
	HTreeNode * parent;
	while(v.size() >= 2){
		HTreeNode * lchild = v[0];
		HTreeNode * rchild = v[1];

		int sumWeight = lchild->charitem.weight + rchild->charitem.weight;
		CharItem pItem(0, sumWeight);
		parent = new HTreeNode(pItem);
		parent->lchild = lchild;
		parent->rchild = rchild;

		v.erase(v.begin(), v.begin()+2);
		v.push_back(parent);
		insertSort(parent);
	}

	string code = "";

	preTrav(parent, code);
	
	cout<<encodeABCD()<<'\n';

	encode();
	cout<<decodeABCD("100101110")<<'\n';

	cout<<"#\n";

	return 0;
}


/*
A 1
B 1
C 2
D 3

100101110

A 64
B 13
C 22
D 32
E 103
F 21
G 15
H 47
I 57
J 1
K 5
L 32
M 20
N 57
O 63
P 15
Q 1
R 48
S 51
T 80
U 23
V 8
W 18
X 1
Y 16
Z 1
# 168


*/