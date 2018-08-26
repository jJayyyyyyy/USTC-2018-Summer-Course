###	2018.08.25晚18:30到21:30实验课内容 —— SQL语句练习

##	开发环境

*	Ubuntu 14.04

*	mysql  Ver 14.14 Distrib 5.5.54, for debian-linux-gnu (x86_64) using readline 6.3

*	运行

	```
	$ mysql-ctl start
	$ mysql-ctl cli
	> create database if not exists cos;
	> connect cos;
	```

*	结束

	```
	> quit
	$ mysql-ctl stop
	```

*	utf-8 编码

	编辑 `/etc/mysql/my.cnf` 文件，在相应位置设置 `utf-8` 编码

	```
	[client]
	default-character-set = utf8

	[mysqld]
	character-set-server = utf8
	collation-server = utf8_general_ci
	```

	然后进入 mysql 进行验证

	```
	> show variables like '%char%';
	```

<br>

##	实验说明

本实验涉及的数据库表如下：

*	`patron` 包含的字段: `patron_id`, `name`, `address`, `email`

*	`menu` 表包含的字段: `menu_id`, `menu_name`, `menu_date`

*	`food_item` 包含的字段: `food_description`, `food_price`, `menu_id`

*	注意：这里的表可能是不完整的，当进行数据库设计时，要根据系统需求自行添加或改字段

	`menu` 和 `food_item` 表是级联的，有一对多的关系

<br>

##	习题

1.	创建 `patron` ，`menu`，`food_item`

	*	如果主键、外键在此处没有考虑清楚，可以在实验中逐步添加

	*	创建 `patron` 

		```sql
		create table patron ( patron_id int primary key, name varchar(20), address varchar(40), email varchar(20) );
		```

	*	创建 `menu`

		```sql
		create table menu ( menu_id int primary key, menu_name varchar(20), menu_date date );
		```

	*	创建 `food_item`

		```sql
		create table food_item ( food_id int primary key, menu_id int, food_price int, food_description varchar(80) );
		```

	*	显示刚才创建的表

		```sql
		show tables;
		describe patron;
		describe menu;
		describe food_item;
		```

	<br>

2.	修改 `patron` 表的结构，增加一个字段 `patron`的身份证号，然后再删除这个字段

	*	增加字段

		```sql
		alter table patron add column idno varchar(20);
		```

	*	删除字段

		```sql
		alter table patron drop column idno;
		```

	<br>

3.	任意新建一张表，然后删除此表

	*	新建表

		```sql
		create table if not exists hello (num int);
		```

	*	删除表

		```sql
		drop table if exists hello;
		```

	<br>

4.	查询 `patron` 表中 `name` 字段的长度小于等于3的所有的人的记录

	*	为了方便测试，我们首先插入一些数据

		```sql
		insert into patron values ( 1, 'Alice', 'CenterSt', 'Alice@ustc.edu' );
		insert into patron values ( 2, 'Bob', 'Fifth Ave', 'Bob@ustc.edu' );
		insert into patron values ( 3, 'Go', 'Alpha', 'Go@ustc.edu' );
		/* insert into patron values ( 4, 'Beta', 'Alpha', 'Beta@ustc.edu' ); */
		```

	*	筛选记录

		```sql
		select * from patron where length(name) <= 3;
		```

	<br>

5.	在 menu 增加一种菜类型（menu），并增加这种类型的菜2~3样（food_item）.

	*	在 menu 中增加家常菜

		```sql
		insert into patron values()
		insert into menu values ( 1, "Homemade", 20180825 );
		```

	*	在 food_item 中增加 炒饭和炸鸡

		```sql
		insert into food_item values ( 1, 1, 10, "Fried Rice" );
		insert into food_item values ( 2, 1, 12, "Fried Chicken" );
		```

	<br>

6.	新建一个视图，包含 `patron` 表中的 `name`, `email` 两个字段

	*	视图 `view` 和表 `table` 都可以由 `as select name, email from patron` 导出

		```sql
		create view vip as select name, email from patron;
		/* drop view vip; */
		/* create table vip1 as select name, email from patron; */
		/* drop table vip1; */
		```

		区别在于, `view` 相当于一个指针，不存放数据，如果原来表中的数据变了，view也会跟着变

		而 `table` 则是普通变量，里面存储的数据不会跟着原来的表一起变化

	<br>

7.	查询 `food_item` 表中的总记录数

	*	select 结合 count()

		```sql
		select count(*) from food_item;
		```

	<br>

8.	查询 `patron` 表中手机尾号为 `5728` 的记录

	*	先调整 `patron`, 增加 `手机号` 字段

		```sql
		alter table patron add column mobi varchar(16);

		```

	*	然后更新一些记录的手机号

		```sql
		update patron set mobi = '123456' where patron_id = 1;
		update patron set mobi = '1235728' where patron_id = 2;
		```

	*	最后查找记录. 使用通配符 `%` 来匹配 `0 ~ n` 个字符

		% - The percent sign represents zero, one, or multiple characters

		```sql
		select * from patron where mobi like '%5728';
		``` 

	<br>

9.	将 `menu` 表按时间排序（升序）

	*	目前 `menu` 表中只有一条记录，我们先增加几条记录

		```sql
		insert into menu values (2, 'chuan', '20180826');
		insert into menu values (3, 'yue', '20180823');
		insert into menu values (4, 'su', '20180822');
		```

	*	然后选出所有记录，并按时间 `menu_date` 升序排列

		```sql
		select * from menu order by menu_date asc;
		```

	<br>

10.	查询出 `food_item` 表中 `menu_id` 以及对应的 `menu_id` 的菜的个数

	*	首先增加 `food_item` 的记录

		```sql
		insert into food_item values (3, 2, 5, 'egg');
		insert into food_item values (4, 3, 15, 'eggy');
		insert into food_item values (5, 4, 3, 'potato');
		```

	*	然后从 `food_item` 选出所有记录，并根据 `menu_id` 进行分类统计

		```sql
		select menu_id, count(*) from food_item group by menu_id;
		```

	<br>

11.	查询出 `patron` 表中的前 3 条记录

	*	使用 `limit` 进行记录条数的限定。注意 `MySQL` 不支持 `top 3 *`

		```sql
		select * from patron limit 3;
		```

	<br>

12.	查询出菜名为 `potato` 的菜的价格，菜的描述以及它所属的菜的种类的名字

	*	```sql
		select food_description, food_price, menu_id from food_item where food_description = 'potato';
		```

	<br>

13.	查询出 `food_item` 表中和 `potato` 一样菜价的菜的名字和价格

	*	先找到 `potato` 的价格, 然后以此为判断条件, 对记录进行筛选

		```sql
		select food_description, food_price from food_item where food_price = (select food_price from food_item where food_description = 'potato');
		```

	<br>

##	相关阅读

*	[w3schools - SQL ](https://www.w3schools.com/sql)

*	[SQL 笔记](https://github.com/jJayyyyyyy/cs/tree/master/SQL)

<br>
