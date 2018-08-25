##	2018.08.23晚18:30到21:30实验课内容 —— 环境搭建与MySQL基本操作

1.	实验目的

	搭建MySQL服务环境，使用MySQL Workbench进行基本数据库操作练习

	<br>

2.	实验内容

	*	下载并安装MySQL(略)

	*	MySQL服务启动、停止

		```sql
		# 启动
		$ mysql-ctl start

		# 停止
		$ mysql-ctl stop
		```

	*	新建cos数据库

		并为该数据库新建用户cos_admin，分配权限为DBA (略)

		```sql
		# 先启动
		# 进入 root 用户的数据库
		$ mysql -u root

		# 删除 cos 数据库(如果存在)
		> drop database if exists cos;
		# 创建 cos 数据库(如果不存在)
		> create database if not exists cos;
		# 显示数据库
		> show databases;
		```

	*	新建Patron表，用户名（varchar）,密码，住址。修改Patron表，加入电话号码字段

		```sql
		# 连接到 cos 数据库
		> connect cos;

		# 建立 patron 表, 四列, (id, username, passwd, addr)
		> create table patron (id int primary key, username varchar(20), passwd varchar(20), addr varchar(100) );
		# 显示 cos 中的所有表
		> show tables;
		# 显示所有的列的title
		> describe patron;

		# 增加列(属性，字段)
		> alter table patron add tel varchar(11);
		> describe patron;

		# 增加一条记录
		> insert into patron values (1, 'Alpha', 'passwd1', 'Wen', '12345678');
		# 显示 patron 中的数据
		> select * from  patron;

		```

	<br>

3.	相关阅读

	*	[w3schools - SQL ](https://www.w3schools.com/sql)

	*	[SQL 笔记](https://github.com/jJayyyyyyy/cs/tree/master/SQL)

	<br>
