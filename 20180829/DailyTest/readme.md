###	2018.08.29晚18:30到21:30实验课内容 —— 通过高级语言实现数据库的 `增删查改`

##	实验目的

*	通过 C++/Java/Python 以及相应的 connector, 练习数据库的 `增删查改` 操作

	本次实验，最简单的方法是通过 `Python` 进行 `CRUD`, 可以参考 [这篇文章](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/0014320107391860b39da6901ed41a296e574ed37104752000)

	欢迎发送 `Python`, `Java` 和 `C++` 以及其他语言实现的 `PR`~

*	`Java` 和 `Python` 实现数据库的 `增删查改` 的过程大致相同, `C++` 应该也是类似的

	*	首先是通过各语言的 `connector` 连接到 `MySQL`, 从而获取 `conn` 对象

	*	连接到数据库后，需要打开 `cursor` (游标), 

		`SQL` 语句是通过 `cursor` 执行的, 执行查找操作后返回的数据集 `rs` 也是通过 `cursor` 得到的

	*	接着是 `commit` (提交), 把结果更新到数据库

	*	最后是关闭 `cursor` 和 `conn`

*	推荐在 `cloud9` 等云平台上进行实验

<br>

##	相关阅读

*	[w3schools, SQL](https://www.w3schools.com/sql/)

*	[Liaoxuefeng, Python, MySQL](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/0014320107391860b39da6901ed41a296e574ed37104752000)

*	[cloud9](https://c9.io/)

*	[USTC-Summer-Course-20180825](https://github.com/jJayyyyyyy/USTC-2018-Summer-Course/tree/master/20180825/DailyTest)

<br>