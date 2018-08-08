##	2018.08.08晚19:00到22:00实验课内容

1.	Linux简介与常用命令

	*	cd

	*	ls

	*	man

	*	mkdir

	*	cat

	*	cp

	*	mv

	*	rm

	*	find

	*	grep

	*	wc

	*	输出重定向

		*	`>` 覆盖重写

		*	`>>` 追加

	*	管道

	*	权限管理

		*	chmod

		*	chown

	*	pwd

	*	shutdown

	<br><br>

2.	代码编译

	*	安装 `gcc/g++`

	*	编辑文件 `test.c`

	*	编译

	*	```bash
		$ gcc test.c -o test
		```

	*	运行

		```bash
		$ ./test
		```

	<br><br>

3.	使用 gdb 进行代码调试

	*	首先生成可以调试的 `test.out` 文件

		```bash
		$ g++ -g test.cpp -o test.out
		```

	*	使用 `gdb` 进行调试

		```
		$ gdb test.out
		```

	*	进入 gdb 后设置断点

		```
		break 10	# 在第 10 行设置断点
		print i		# 打印变量 i
		next		# step over
		step		# step into
		run			# run
		```

	*	[参考链接, How to Debug C Program using gdb in 6 Simple Steps](https://www.thegeekstuff.com/2010/03/debug-c-program-using-gdb/)

