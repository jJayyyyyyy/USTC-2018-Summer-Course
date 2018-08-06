##	2018.08.05晚19:00到22:00实验课内容

1.	哈夫曼编码问题

	利用哈夫曼编码进行通信，可以大大提高信道利用率，缩短信息传输时间，降低成本。但是，这要求在发送端通过一个编码系统对数据进行编码，然后在接收端进行解码。对于双工信道（可以双向传输的信道），每个端口都要有一个完整的编解码系统。请编写一个哈夫曼编解码系统。

	要求：

	*	从终端读入字符集大小为n（即n个字符和n个权值），建立哈夫曼树，进行编码并输出，保存为文件 `hfmtree`

	*	利用刚才的 `hfmtree` 文件，对键盘输入的正文(已经过编码)进行译码。输出字符正文，再输出该文的二进制码。

	样例：根据下面的字符集和频度，建立哈夫曼树。
	
	```
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
	```
	
	然后实现以下报文的译码和输出
	
	```
	C PROGRAM IS MY FAVORITE
	```
	
2.	拓扑排序

	软件专业的学生要学习一系列课程，其中有些课程有先修课，具体关系如下

	```
	课程编号		先修课程编号
	
	1		None
	2		1
	3		1 2
	4		1
	5		3 4
	6		11
	7		3 5
	8		3 6
	9		None
	10		9
	11		9
	12		1 9 10
	```

	请制定教学计划，使学生能在最短时间内完成这些课程


	本题可套用拓扑排序模板以及BFS层序遍历模板，参考链接如下

	*	[topo, https://github.com/jJayyyyyyy/OJ/blob/19fec4ec6c03792b5391dad77dbe73bcb64a89e9/%E6%B5%99%E5%A4%A7%E6%9C%BA%E8%AF%95%E6%A8%A1%E6%8B%9F%E8%B5%9B/1011/readme.md](https://github.com/jJayyyyyyy/OJ/blob/19fec4ec6c03792b5391dad77dbe73bcb64a89e9/%E6%B5%99%E5%A4%A7%E6%9C%BA%E8%AF%95%E6%A8%A1%E6%8B%9F%E8%B5%9B/1011/readme.md)

	*	[topo, https://github.com/jJayyyyyyy/OJ/blob/19fec4ec6c03792b5391dad77dbe73bcb64a89e9/PAT/advanced_level/1146_Topological_Order/topological_order.cpp](https://github.com/jJayyyyyyy/OJ/blob/19fec4ec6c03792b5391dad77dbe73bcb64a89e9/PAT/advanced_level/1146_Topological_Order/topological_order.cpp)
	
	*	[BFS, https://github.com/jJayyyyyyy/cs/blob/master/data%20structure/tree/%E9%81%8D%E5%8E%86/%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.cpp](https://github.com/jJayyyyyyy/cs/blob/master/data%20structure/tree/%E9%81%8D%E5%8E%86/%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.cpp)
	