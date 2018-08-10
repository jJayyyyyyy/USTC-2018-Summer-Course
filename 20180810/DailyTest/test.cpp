/*
整体思路
1. 根据用户输入建立一个链表数组waitingList，每个元素都是一个指针，指向一个等待队列中的PCB
2. 根据优先级，对 waitingList 进行排序
3. 这样，waitingList[0] 就是即将执行的进程
4. 取出 waitingList[0]，将其状态设为 RUN
5. 完成任务后，将状态设回 WAIT，优先级--，运行时间++
6. 将该任务插回等待队列中合适的位置
7. 重复 4-6

TODO
1. 重构代码
2. 模拟Blocked
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define FINISHED -1
#define WAIT 0
#define RUN 1
#define BLOCK 2
using namespace std;

struct Task{
	int day;
	int weekend;

	Task(){
		day = 0;
		weekend = 7;
	}
	
	// TODO 输入数字，进入blocked状态
	void work(){
		day++;
	}
	
	// TODO: 
	bool run(){
		if( day == weekend ){
			return false;
		}else{
			work();
			return true;
		}
	}
};

struct PCB{
	int pid;
	int state;
	int priority;
	int needtime, nowtime;
	Task * task;
	
	PCB(int _pid, int _priority, int _needtime){
		pid = _pid;
		priority = _priority;
		needtime = _needtime;
		state = WAIT;
		nowtime = 0;
		task = new Task();
	}
	
	void run(){
		// cout<<"Begin Running\n";
		state = 1;
		getInfo();
		task->run();
		// cout<<"End Running\n";
		// cout<<"pid: "<<pid<<", nowtime +1\n";
		nowtime++;
		priority--;
		if( nowtime == needtime ){
			state = FINISHED;
		}else{
			state = WAIT;
		}
		getInfo();
	}
	
	void getInfo(){
		cout<<"pid: "<<pid<<'\n';
		cout<<"priority: "<<priority<<'\n';
		cout<<"state: "<<state<<'\n';
		cout<<"needtime: "<<needtime<<'\n';
		cout<<"nowtime: "<<nowtime<<'\n';
	}
	
	bool finished(){
		return nowtime == needtime;
	}
	
	bool blocked(){
		return state == BLOCK;
	}
	
	bool waitForNextTime(){
		return state == WAIT && nowtime < needtime;
	}
};

bool cmp(PCB * & a, PCB * & b){
	if( a->priority != b->priority ){
		return a->priority > b->priority;
	}else{
		return a->pid < b->pid;
	}
}

// v[1] ~ v[n] 是已经排好序的
void insertSort(vector<PCB *> & v){
	// TODO【Done】: insertSort, 把v[0] 插到 v[1] ~ v[n]的某个位置，按照优先级排序
	// TODO【Done】: 先来先服务, 把v[0] 插到 相同优先级的最后位置 
	// sort(v.begin(), v.end(), cmp);
	for( int i = 1; i < v.size(); i++ ){
		if( v[0].priority <= v[i]->priority ){
			swap(v[0], v[i]);
		}else{
			break;
		}
	}
}

// 初始化等待(就绪)列表
void init(vector<PCB *> & v){
	int n;
	cin>>n;
	
	int pid, priority, needtime;
	
	for( int i = 0; i < n; i++ ){
		cin>>pid>>priority>>needtime;
		v.push_back(new PCB(pid, priority, needtime) );
	}

	sort(v.begin(), v.end(), cmp);
}

// input WaitingList or BlockedList
void printList(vector<PCB *> & v) {
	for( auto pcb : v ){
		pcb->getInfo();
	}
}

// 本质其实是维护几个指针数组
int main(){
	vector<PCB *> waitingList;
	vector<PCB *> blockedList;
	init(waitingList);
	
	while( waitingList.size() || blockedList.size() ){
		PCB * p = waitingList[0];
		p->run();

		if( p->finished() ){
			waitingList.erase(waitingList.begin());
		}else if( p->waitForNextTime() ){
			insertSort(waitingList);
		}

		// else if( p->blocked() ){
		// 	blockedList.push_back(p);
		// }

		printList( waitingList );
		// printList( blockedList );
		// TODO 输入数字，解除block，加入waitingList
	}

	return 0;
}

