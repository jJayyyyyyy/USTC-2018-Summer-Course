##	2018.08.14晚19:00到22:00实验课内容 —— 进程的管道通信

##	实验要求

1.	使用系统调用 `pipe()` 建立一条管道线

	*	两个子进程分别向管道写一句话（写的内容自己定，但要有该进程的一些信息）

	*	父进程从管道中读出来自两个子进程的消息，显示在屏幕上

	*	**要求**

		**父进程首先接收子进程 p1 发来的消息，然后再接收子进程 p2 发来的消息**

	<br>

2.	分析

	*	并发具有一定程度的不确定性，进行 `fork()` 后，有可能先运行父进程，也有可能先运行子进程

	*	题目要求并发，又要求首先执行第一个子进程。所以，万一父进程先被执行，就在这里等待

		等到子进程1执行完了，再执行父进程的剩余操作

		也就是说，并行被手动安排成了串行顺序执行

	<br>

	*	实验的时候，没有加 `wait()` 或者把 `wait()` 放错了地方，我的电脑出现了随机的结果，而朋友的电脑却一直是先 `child2` 后 `child1`，`child1 < child2 < parent `

		在 `c9` 上运行也是这样的顺序，比如编译运行 `pipe_example.c` ，可以发现每次都能打印出 `hello world!` 和 `goodbye, world!`，也就是有了一种固定的 `先父后子` 的执行顺序（否则若先子后父，那么子进程读管道的时候管道还是空的，读不出来）

		在寻找原因的时候，发现了参考链接中的这篇文章 [ fork() 父子进程运行先后顺序](http://chenzhenianqing.com/articles/350.html)，作者根据 maillist 分析了父子进程执行顺序的历史演变。对于 `kernel-2.6.32 `以上的版本，截至2012年，父进程优先运行。对于这里的 `优先preference `，Linus是这么说的

		> ..., we've never made any guarantees, because the timeslice for the parent might be just about to end, so child-first vs parent-first is never a guarantee, it's always just a preference. ...

	*	另外我找到了一份 `Ubuntu内核` 的历史列表(实验用的发行版系统是 Ubuntu )，[List of Ubuntu Versions with Corresponding Linux Kernel Version](https://askubuntu.com/questions/517136/list-of-ubuntu-versions-with-corresponding-linux-kernel-version)，根据这份列表，`Ubuntu 14.04` 以上都已经采用了 `kernel-2.6.32 ` 以上版本的内核。

		不过根据实验结果，某些机器上的 `preference` 似乎变成了 `guarantee`

	*	扯远了。其实为了达到实验要求的执行顺序，**最关键的就是在合适的地方加上 `wait()`**

<br><br>

##	疑问 & TODO (已解决，C语言白学了T_T)

*	pipe 的数据结构

	是否为队列？因为 p1 写完后，就算父进程等到 p2 结束了才从管道读取消息，p2 写的消息也不会把 p1 的覆盖掉，而是排在了p1的后面

	然而，分两次读取，每次读10字节，可以读出p1和p2的消息，但是一次读取20字节，就只能输出p1的消息，为啥呢

	<br>

<br><br>

##	参考链接

*	[lockf(3) - Linux man page](https://linux.die.net/man/3/lockf)

	int lockf(int fd, int cmd, off_t len);

	fd: file descriptor

	cmd: F_LOCK, F_ULOCK, ...

	len: if len is zero, the section extends from the current file position to infinity, encompassing the present and future end-of-file positions. In all cases, the section may extend past current end-of-file.

	[lockf, opengroup](http://pubs.opengroup.org/onlinepubs/009695399/functions/lockf.html)

	[File locking in Linux](https://gavv.github.io/blog/file-locks/#lockf-function)

*	[read(2) - Linux man page](https://linux.die.net/man/2/read)

*	[write(2) - Linux man page](https://linux.die.net/man/2/write)

*	[F_LOCK, F_ULOCK undeclared, 编译参数 -std=gnu99](https://stackoverflow.com/questions/1423185/fileno-f-lock-and-f-ulock-become-undeclared-and-unavailable-when-i-add-std-c99)

*	[unknown type name 'pid_t', 需要包含头文件 <sys/types.h>](https://stackoverflow.com/questions/32282270/c99-error-unknown-type-name-pid-t)

*	[return value of read](https://stackoverflow.com/questions/3180126/how-to-use-read-to-read-data-until-the-end-of-the-file)

	这里还可以进行测试，比如 `readFromPipe4()` 运行后不会停止，估计就是因为找不到 EOF 所以停不下来了

*	[ fork() 父子进程运行先后顺序](http://chenzhenianqing.com/articles/350.html)

*	Linux 获取系统信息 `$ uname -a`

*	[List of Ubuntu Versions with Corresponding Linux Kernel Version](https://askubuntu.com/questions/517136/list-of-ubuntu-versions-with-corresponding-linux-kernel-version)

<br><br>

##	附录(PPT文字版)

1.	概述

	*	加深对进程概念的理解，明确进程和程序的区别
	*	学习进程创建的过程，进一步认识并发执行的实质
	*	分析进程争用资源的现象，学习解决进程互斥的方法
	*	学习解决进程同步的方法
	*	掌握 `Linux` 系统进程间通过管道通信的具体实现方法(本实验代码不适用于 `Windows` 环境 )

	<br>

2.	基础回顾

	*	基本概念

		*	进程的概念
		*	进程与程序的区别
		*	并发执行的概念
		*	进程互斥的概念
		*	进程通信的基本原理

	*	系统调用

		*	设置系统调用号：设置多条系统调用命令，并赋予每条系统调用命令一个唯一的系统调用号

	<br>

3.	系统调用

	*	处理系统调用：OS中有一张系统调用入口表，表中每个表目对应一条系统调用命令，包含该系统调用自带参数的数目、系统调用命令处理程序的入口地址等。OS内核便是根据所输入的系统调用号在该表中查找到相应的系统调用，进而转入它的入口地址去执行系统调用程序。

	*	Linux的系统调用机制：通过中断机制实现。

	<br>

4.	`fork()`, 创建一个新进程

	*	调用格式

		```c
		int pid = fork();
		// 若 pid < 0 则创建失败
		// 若 pid = 0 则创建成功, 且进入子进程
		// 若 pid > 0 则创建成功，且进入父进程
		```

		由于父进程和子进程分别独立地进入就绪队列等待调度，所以谁首先得到调度是不确定的。

		也就是说，谁首先从 fork() 返回, 继续执行后面的语句也是不确定的。

	<br>

5.	`wait()`, 控制父进程与子进程的同步

	*	如果父进程调用该函数，则父进程被阻塞，进入等待队列，等待子进程结束。

		子进程结束时，产生一个终止状态字，系统向父进程发出 `SIGCHILD` 信号。

		当接到信号后，父进程提取子进程的终止状态字，从 `wait()` 函数返回继续执行后续程序。

	*	调用格式

		```c
		#include <sys/type.h>
		#include <sys/wait.h>
		(pid_t) pt =  wait (int *statloc);
		// 若 pt >= 0 , 正确返回
		// 若 pt < 0, 则说明调用失败
		```

	<br>

6.	`exit()`, 结束进程

	*	正常终止时，该函数返回进程结束状态。

	*	调用格式：

		```c
		#include <stdio.h>
		void exit (int status);
		// status为进程结束状态
		// 
		```

	<br>

7.	`kill()`, 终止执行中的进程

	*	调用格式

		```c
		kill (int PID, int IID);
		// PID 是要被终止的进程号，IID为向被杀死的进程发送的中断号
		```

	<br>

8.	`pipe()`, 创建一个管道

	*	调用格式

		```c
		#include <unistd.h>
		pipe (int fp[2]);
		// fp[2] 是供进程使用的文件描述符数组, fp[1] 用于写, fp[0] 用于读
		// 调用成功返回 0
		// 调用失败返回 -1
		```

	<br>
