/* 实验说明请参考readme */
#include <unistd.h>			// pipe(), lockf(), 需要在编译参数中加上 -std=gnu99
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>		// 类型 (pid_t)

void readFromPipe1(int fd);
void readFromPipe2(int fd);
void readFromPipe3(int fd);
void readFromPipe4(int fd);

int main( ){
	int fd[2] = {0, 1};		// file descriptor

	/* 创建一个管道,  fd[0]读，fd[1]写, pipe() 是 Linux 的系统调用
	 * https://linux.die.net/man/2/pipe
	 * 若返回非0, 说明 pipe 创建失败
	 */
	if ( pipe (fd) != 0 ) {
		fprintf (stderr, "Pipe failed.\n");
		return EXIT_FAILURE;
	}


	// 尝试创建子进程1，若创建成功则 pid1 >= 0, fork() 是 Linux 的系统调用
	int pid1 = fork();
	
	// fork()成功后，可能会进入子进程1，也可能继续执行父进程
	// 所以需要判断当前处于 【子进程1】 or 【父进程】 or 【fork()失败】


	// fork() 成功且进入子进程1
	if( pid1 == (pid_t)0 ){
		lockf( fd[1], F_LOCK, 0 );		// 锁住 fd[1] 所指的管道, 0表示长度为无限
		char msg1[10] = "Child1";
		write( fd[1], msg1, 10 );
		lockf( fd[1], F_ULOCK, 0 );		// 解锁 fd[1] 所指的管道
		return EXIT_SUCCESS;
	}

	// fork() 成功且仍在父进程
	else if( pid1 > (pid_t)0 ){
		// Kernel 2.6.32 以上版本的preference --- 先父后子
		// http://chenzhenianqing.com/articles/350.html

		wait(EXIT_SUCCESS);				// 根据题目要求，先等待子进程1结束

		int pid2 = fork();
		if( pid2 == (pid_t)0 ){
			// fork() 成功且进入子进程2
			lockf( fd[1], F_LOCK, 0 );
			char msg2[10] = "Child2";
			write( fd[1], msg2, 10 );
			lockf( fd[1], F_ULOCK, 0 );
			return EXIT_SUCCESS;
		}

		// fork() 成功且仍在父进程
		else if( pid2 > (pid_t)0 ){
			wait(EXIT_SUCCESS);			// 等待子进程2结束

			// 分别去掉下面三行的注释进行测试，从管道中读取字符串
			readFromPipe1(fd[0]);
			// readFromPipe2(fd[0]);
			// readFromPipe3(fd[0]);

			return EXIT_SUCCESS;
		}

		// pid2 < 0, 子进程2 fork() 失败
		else{
			fprintf (stderr, "Fork2 failed.\n");
			return EXIT_FAILURE;
		}
	}

	// pid1 < 0, 子进程1 fork() 失败
	else{
		fprintf (stderr, "Fork1 failed.\n");
		return EXIT_FAILURE;
	}
}

/* 测试: 从管道中读取数据
 * 实验中，我们遇到一个问题，可以分两次从管道中读取 child1, child2 写入的数据，每次读10个字节，如 readFromPipe1()
 * 由此猜测管道是一个类似于 【队列】 的数据结构
 *
 *
 * 但是一次性从管道中读取20字节，却只能读取(显示) child1，如 readFromPipe2()，后面的child2 不见了
 *
 * 你能想到问题所在吗？
 *
 *
 *
 *
 * 实验的时候时间比较紧，没想通为什么会这样，以为这里面还有其他奥秘
 * 但是后来突然发现，这其实只是个 【C语言字符串】 的问题
 * 当我们声明 char msgbox[10]; 的时候，编译器帮我们把数组的所有元素都初始化成 0 了，也就是结束符 '\0'
 * 而 printf("%s", msgbox); 打印到 '\0' 就停止了
 * 如果我们把 [0, 19] 的字符分别单个打印出来，就可以发现 child2 其实是跟在 child1 后面的
 * 当时没有立刻发现问题2所在，想来还是C语言用得太少0.0
 * 其实学了汇编以后，发现C语言其实挺好用的T_T
*/
void readFromPipe1(int fd){
	char msgbox[10];

	int val = read( fd, msgbox, 10 );		// val是读取出来的字节数
	printf("%s\n", msgbox);

	val = read( fd, msgbox, 10 );
	printf("%s\n", msgbox);
}

void readFromPipe2(int fd){
	char msgbox[20];

	int val = read( fd, msgbox, 20 );
	printf("%s\n%d\n", msgbox, val);
}

void readFromPipe3(int fd){
	char msgbox[20];

	int val = read( fd, msgbox, 20 );
	printf("%s\n", msgbox);

	for(int i = 0; i < 20; i++ ){
		printf("%c_", msgbox[i]);
	}
	printf("\n");
}

// 无法停止
void readFromPipe4(int fd){
	char msgbox[20];

	int val = read( fd, msgbox, 20 );
	printf("%s\n", msgbox);

	val = read( fd, msgbox, 10 );
	printf("%s\n", msgbox);
}
