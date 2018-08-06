/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p

哈希查找表的建立
程序说明：
1. 首先建立inputList读取输入
2. 然后建立 hashTable1，链地址法存储。hashTable1 建立完成后，对其进行输出
3. 接着建立 hashTable2，线性探测再散列, H[key] = (key + i) % P, 建立完成后对其进行输出。注意本题样例输入 n > P，因此有的结点将无法存储
hash


TODO: 增加注释
TODO: 重构代码
TODO: 增加样例
*/
/*
同类题目参考
PAT_A_1145
*/

#include <iostream>
#include <vector>
using namespace std;

struct Node{
	int val;
	Node *next;
	Node(){
		val = 0;
		next = NULL;
	}
	Node(int v){
		val = v;
		next = NULL;
	}
};

int MAXSIZE;

vector<bool> primeList;
vector<int> inputList;

void getInputList(int n){
	for( int i = 0; i < n; i++ ){
		int val;
		cin>>val;
		inputList.push_back(val);
	}
}

void getPrimeList(){
	primeList[2] = true;

	for( int i = 3; i < MAXSIZE - 2; i += 2 ){
		primeList[i] = true;
		primeList[i + 1] = false;
	}

	int upper = (int)sqrt(MAXSIZE);
	for( int i = 3; i < upper; i += 2 ){
		if( primeList[i] == true ){
			for( int j = i + i; j < MAXSIZE - 2; j += i ){
				primeList[j] = false;
			}
		}
	}
}

void printHashTable1(vector<Node *> & hashtable){
	cout<<"HashTable1\n";
	for( int i = 0; i < hashtable.size(); i++ ){
		Node * node = hashtable[i];
		cout<<i;
		while( node != NULL ){
			cout<<' '<<node->val;
			node = node->next;
		}
		cout<<'\n';
	}
}

void printHashTable2(vector<int> & hashtable){
	cout<<"HashTable2\n";
	for( int i = 0; i < hashtable.size(); i++ ){
		if( hashtable[i] != 0 ){
			cout<<i<<' '<<hashtable[i]<<'\n';
		}
	}
}

void getHashTable1(vector<Node *> & hashtable, int P){
	for( int val : inputList ){
		int pos = val % P;
		Node * node = new Node(val);
		if( hashtable[pos] == NULL ){
			hashtable[pos] = node;
		}else{
			Node * p = hashtable[pos];
			while( p->next != NULL ){
				p = p->next;
			}
			p->next = node;
		}
	}

	cout<<'\n';
}

void getHashTable2(vector<int> & hashtable, int P){
	for( int val : inputList ){
		int j;
		for( j = 0; j < P; j++ ){
			int pos = (val + j) % P;
			if( hashtable[pos] == 0 ){
				hashtable[pos] = val;
				break;
			}
		}
		if( j == P ){
			cout<<val<<" cannot be inserted\n";
		}
	}
}

int main(){
	int n, P;
	cin>>n>>P;

	getInputList(n);

	MAXSIZE = n + 300;
	primeList.resize(MAXSIZE);
	getPrimeList();

	// 防止输入的P不是素数
	for( ; P < MAXSIZE; P++ ){
		if( primeList[P] == true ){
			break;
		}
	}

	vector<Node *> hashtable1(P, 0);
	getHashTable1(hashtable1, P);
	printHashTable1(hashtable1);
	cout<<"\n\n";

	vector<int> hashtable2(P, 0);
	getHashTable2(hashtable2, P);
	printHashTable2(hashtable2);
	cout<<"\n\n";

	return 0;
}


/*
input1
12 11
19 14 23 1 68 20 84 27 56 11 10 79


input2
4 5 4
10 6 4 15 11
11 4 15 2
*/