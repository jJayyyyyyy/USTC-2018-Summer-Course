#include <iostream>
#include <vector>
#include <iomanip>
#define LRU 1
#define FIFO 2
using namespace std;

vector<int> pageList;			// 页面块
vector<int> itemList;			// 作业序列

// 由用户输入页面块的大小
void resizePageList(){
	cout<<"请输入页面块大小: ";
	int size = 0;
	cin>>size;
	pageList.resize(size, -1);
}

// 输入作业序列
void getItemList(){
	cout<<"请输入作业个数: ";
	int n;
	cin>>n;
	cout<<"请输入作业序列:\n";

	for( int i = 0; i < n; i++ ){       //将作业页号依次输入数组中 
		int item;
		cin>>item;
		itemList.push_back(item);
	}
}

void init(){
	resizePageList();
	getItemList();
}

/* 以下函数判断第i个页面是否在内存*/ 
int getIxPage(int item){
	int i;
	for( i = 0; i < pageList.size(); i++ ){
		// 第i个页面是否在内存中
		if( pageList[i] == item ){
			break;
		}
	}
	return i;
}

int calcLRU(){
	int lenPage = pageList.size();
	pageList.assign(lenPage, -1);	// 重新初始化pageList
	int lenItem = itemList.size();

	int cntMiss = 0;

	cout<<"缺页序列:\n";
	// 下标越小，说明存在时间越久，应该被置换出去
	for( int i = 0; i < lenItem; i++ ){
		int item = itemList[i];
		int ixPage = getIxPage( item );
		// 如果不在当前的表中，说明发生了缺页, cntMiss++
		// 需要置换, 把 [0, lenPage-2] 循环前移，然后把 item 放到最后(最近使用)
		if( ixPage == lenPage ){
			cntMiss++;				// 发生了缺页
			cout<<item<<' ';
			int j = 0;
			for( ; j < ixPage - 1; j++ ){
				pageList[j] = pageList[j + 1];
			}
			pageList[j] = item;
		}
		// 如果在当前的表中, 则把 [ixPage, lenPage-2] 循环前移，然后把 item 放到最后(最近使用)
		// [0, ixPage-1] 不用动
		else{
			cout<<"_ ";
			int j = ixPage;
			for( ; j < lenPage - 1; j++ ){
				pageList[j] = pageList[j + 1];
			}
			pageList[j] = item;
		}
	}
	cout<<'\n';
	return cntMiss;
}

int calcFIFO(){
	int lenPage = pageList.size();
	pageList.assign(lenPage, -1);	// 重新初始化pageList
	int lenItem = itemList.size();

	int cntMiss = 0;

	cout<<"缺页序列:\n";
	// 下标越小，说明存在时间越久，应该被置换出去
	for( int i = 0; i < lenItem; i++ ){
		int item = itemList[i];
		int ixPage = getIxPage( item );
		// 如果不在当前的表中，说明发生了缺页, cntMiss++
		// 把 [0] 置换出去, 后面元素前移 [1, lenPage-1] -> [0, lenPage-2], 然后把 item 放到最后 [lenPage-1] (最近使用)
		if( ixPage == lenPage ){
			cntMiss++;				// 发生了缺页
			cout<<item<<' ';
			pageList.erase(pageList.begin());
			pageList.push_back(item);
		}
		// 如果在当前的表中, 不用作任何改动
		else{
			cout<<"_ ";
			int j = ixPage;
		}
	}
	cout<<'\n';
	return cntMiss;
}

int main(){
	init();

	int lenPage = pageList.size();
	int lenItem = itemList.size();
	int cntMiss = lenPage;

	cout<<"1. LRU\n2. FIFO\n请选择算法:\n";
	int choice = 0;
	cin>>choice;

	if( choice == LRU ){
		cntMiss = calcLRU();
	}else if( choice == FIFO ){
		cntMiss = calcFIFO();
	}

	double rateMiss = cntMiss * 100.0 / lenItem;
	cout<<"发生缺页的次数为: "<<cntMiss<<'\n';
	cout<<"缺页中断率为: "<<fixed<<setprecision(2)<<rateMiss<<"%\n";

	return 0;
} 


/*
####	LRU

input
3
12
4 3 2 1 4 3 5 4 3 2 1 5


output

缺页序列	4 3 2 1 4 3 5 _ _ 2 1 5
缺页次数	10
缺页率		83.33%


####	FIFO

input
3
12
1 2 3 4 1 2 5 1 2 3 4 5


output
缺页序列	1 2 3 4 1 2 5 _ _ 3 4 _
缺页次数	9
缺页率		75.00%

参考:
https://en.wikipedia.org/wiki/Cache_replacement_policies
http://www.cplusplus.com/reference/vector/vector
*/
