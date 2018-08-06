/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p
*/
#include <iostream>
#include <queue>
#include <set>
#define MAXSIZE 16
using namespace std;

struct Course{
	int id, term;
	Course(int i){
		id = i;
		term = 0;
	}
};

// 邻接表, next = G[now], 课程 now 的后续课程为 next
vector<int> G[MAXSIZE];
// 入度表, prev = inDegree[now], 课程 now 的前置课程是 prev 
int inDegree[MAXSIZE] = {0};
int cntTerm = 0;	// 一共需要多少个学期才能学完
// 每一学期的课程
vector<Course> courseList;


// 套用 BFS 模板即可
// L37~l42, 先找到所有入度为0的课程的id，即没有前置课程的id，放到队列里面
// L52, 然后分别将id的后续课程的入度-1
// L51~L59, 如果出现了新的入度为0的课程，则将其放入队列，同时学期数+1
bool isTopo(int n){
	int cnt = 0;
	queue<Course> q;	// q是待学习课程的队列

	// 把所有【没有前置课程的】课push到queue中
	for( int i = 1; i <= n; i++ ){
		if( inDegree[i] == 0 ){
			Course course(i);
			q.push(course);
		}
	}

	while( q.size() ){
		Course now = q.front();
		courseList.push_back(now);
		cnt++;
		q.pop();	// 前置课程now出队
		

		for( int id : G[now.id] ){
			inDegree[id]--;	// 编号为id的课，其前置课程now.id已经学完了，所以入度-1
			if( inDegree[id] == 0 ){
				Course next(id);		// 假设这门课为next，如果next的前置课程now都已经学完了, 也就是next的入度为0，那么next就可以进入待学习的队列q了
				next.term = now.term + 1;	// 课程next的学期 = 课程now的学期 + 1
				cntTerm++;
				q.push(next);
			}
		}
	}
	return cnt == n;
}

// 获取课程的前置关系
void getInput(int n){
	for( int v1 = 1; v1 <= n; v1++ ){
		int k;
		cin>>k;
		for( int i = 0; i < k; i++ ){
			int v2;
			cin>>v2;
			G[v2].push_back(v1);
			inDegree[v1]++;
		}
	}
}

// 输出每个学期要学习的课程
void printCourseOfEveryTerm(){
	vector< set<int> > termList;
	termList.resize(cntTerm);
	for( auto course : courseList ){
		int id = course.id;
		int term = course.term;
		termList[term].insert(id);
	}

	for( auto termid : termList ){
		for( auto courseid : termid ){
			cout<<courseid<<' ';
		}
		cout<<'\n';
	}
}

int main(){
	int n;
	cin>>n;

	getInput(n);

	cout<<'\n';
	
	if( isTopo(n) ){
		printCourseOfEveryTerm();
	}else{
		cout<<"Incomplete curriculum\n";
	}

	return 0;
}

/*
输入说明

总的课程数 n
接下来的n行中，每行第一个数是该课的前置课程数量k
然后是k个数，分别代表先修课程的id
id范围是 [1, n]

12
0
1 1
2 1 2
1 1
2 3 4
1 11
2 3 5
2 3 6
0
1 9
1 9
3 1 9 10




输出说明

每一行代表一个学期
每个学期的课号从小到大排列

1 9
2 4 10 11
3 6 12
5 8
7

*/