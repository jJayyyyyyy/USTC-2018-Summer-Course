##	2018.08.16晚19:00到22:00实验课内容 —— 页面置换算法实验

1.	内容

	*	理解常用页面置换算法的原理

	*	实现LRU和FIFO内存页面置换算法

	*	根据实验比较二者的性能

	<br>

2.	LRU和FIFO回顾

	*	LRU页面置换算法

	![LRU](https://github.com/jJayyyyyyy/USTC-2018-Summer-Course/blob/master/20180816/DailyTest/assets/LRU.png)

	<br>

	*	FIFO页面置换算法

	![FIFO](https://github.com/jJayyyyyyy/USTC-2018-Summer-Course/blob/master/20180816/DailyTest/assets/FIFO.png)

	<br>

3.	要求

	*	利用先进先出FIFO和最近最久未使用LRU两种页面置换算法模拟页面访问过程

	*	模拟两种算法的页面置换过程，给出每个页面访问时的内存分配情况

	*	输入：根据实际情况考虑输入，比如最小物理块数m，页面个数n，页面访问序列P1, …,Pn等

	*	输出：每种算法的缺页次数和缺页率

	<br>

4.	程序设计(参考)

	*	利用先进先出FIFO和最近最久未使用LRU两种页面置换算法模拟页面访问过程

	*	模拟两种算法的页面置换过程，给出每个页面访问时的内存分配情况

	*	输入：根据实际情况考虑输入，比如最小物理块数m，页面个数n，页面访问序列P1, …,Pn等

	*	输出：每种算法的缺页次数和缺页率

	<br>

5.	主要数据结构（仅供参考）

	*	代码
	    
	    ```c
		struct one_frame{
			int page_no;
			char flag;
		};

		struct one_frame M_Frame[frame_num];
		// 这里frame_num是给一个进程分配的最大的内存页面数 
		```

	*	存放页面访问序列的数组 (Acess_Series[total_instruction]) 

	*	结构数组M_Frame[]记录了进程被分配的内存页面的使用情况。

		在M_Frame[]中还可记载各页面进入内存或被访问的先后顺序（如可使M_Frame[0]总是最先进入或最久未被访问的页面）

	<br>

6.	程序流程（仅供参考）

	*	父进程： 

		随机产生内存访问页面序列，存于数组Acess_Series[total_instruction]中

		数据结构M_Frame的初始化

		分别创建两个子进程

		等待子进程执行结束，退出

