// 编译参数要加上 -std=gnu99 -pthread
#include <stdio.h>
#include <unistd.h>		// sleep
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;			// sem1 > 0 则可以执行 producer
sem_t sem2;			// sem2 > 0 则可以执行 consumer
int cnt = 0;		// 共享全局变量, producer 和 consumer 都可以对其进行操作

// T1
void * producer(){
	for( int i = 0; i < 5; i++ ){
		sem_wait(&sem1);		// 等待信号量 sem1, 等到后进行 sem1-- (P), 然后进入原子操作
		printf("producer: ");
		cnt++;
		printf("%d\n", cnt);
		sleep(1);
		
		sem_post(&sem2);		// 原子操作完成, 对 sem2 进行 V操作, 即 sem2++ (V), 若此前 sem2==-1, 则这一步就可以将 T2 从阻塞状态解放出来
	}
}  

// T2
void * consumer(){
	for( int i = 0; i < 5; i++ ){
		sem_wait(&sem2);		// 等待信号量 sem2, 等到后进行 sem2-- (P), 然后进入原子操作
		printf("consumer: ");
		cnt--;
		printf("%d\n", cnt);
		sleep(1);
		
		sem_post(&sem1);		// 原子操作完成, 对 sem1 进行 V操作, 即 sem1++ (V), 若此前 sem1==-1, 则这一步就可以将 T1 从阻塞状态解放出来
	}
}

int main(){  
	pthread_t id1;
	pthread_t id2;

	/* 若进行如下设置, 则相当于形成了互斥锁, 
	   而且执行时间肯定是10s, 否则可以并行 sleep()
	*/
	sem_init(&sem1, 0, 1);	// sem1 初值为 1, 可以确保执行顺序是 T1 - T2 - T1 - T2 - ...
	sem_init(&sem2, 0, 0);	// 将 sem2 初值设为 0, 这样 sem2 只能由 T1 进行++从而变成正数
	

	/* 
	sem_init(&sem1, 0, 4);	// sem1 初值为 4 > 1, 在T1首先执行完成后, T1, T2 的执行顺序不是确定的
	sem_init(&sem2, 0, 0);
	*/

	/*
	sem_init(&sem1, 0, 3);
	sem_init(&sem2, 0, 3);	// 此时可能出现 cnt < 0 的情况，因为 sem2 = 2 > 0, T2 可以在一开始就进入共享区
	*/

	int ret = 0;

	ret = pthread_create( &id1, NULL, (void *)producer, NULL );
	if( ret != 0 ){
		printf("Failed to create pthread1\n");
		return 1;
	}

	ret = pthread_create( &id2, NULL, (void *)consumer, NULL );
	if( ret != 0 ){
		printf("Failed to create pthread2\n");
		return 1;
	}

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);


	printf("\n%d\n", cnt);

	return 0;
}
