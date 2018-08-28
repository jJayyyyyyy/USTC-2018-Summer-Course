###	2018.08.26晚18:30到21:30实验课内容 —— Socket编程

##	验收内容

*	设计一个TCP服务器/客户端，从客户端获得一个字符串，服务器把字符串全部转为大写字母之后返回给客户端

	*	本次实验可以用多种方式进行实现，如 Java, Python, C, 可以参考各个目录下的 demo

	*	workflow

		*	server 首先 listen(host, port)

		*	client 发出连接请求

		*	server 接受连接请求

		*	client 发送字符串

		*	server 收到字符串后，将每个字符都转为大写，然后发送给 client

		*	client 接收 server 发过来的大写字符串

		*	关闭连接

<br>

*	描述TCP建立连接三次握手和断开连接四次挥手过程

	![connect](https://github.com/jJayyyyyyy/USTC-2018-Summer-Course/blob/master/20180826/DailyTest/assets/connect.png)

	![disconnect](https://github.com/jJayyyyyyy/USTC-2018-Summer-Course/blob/master/20180826/DailyTest/assets/disconnect.png)

<br>

*	下列服务对应的端口号

	FTP: 20, 21

	HTTP: 80

	HTTPS: 443

	Telnet: 23

	SMTP: 25

<br>

##	相关阅读

*	[network, simple_server](https://github.com/jJayyyyyyy/network/tree/master/application_layer/http/simple_server)

*	[network, udp](https://github.com/jJayyyyyyy/network/tree/master/transport_layer/udp)

*	[Java Notes](https://github.com/jJayyyyyyy/JavaNotes)

*	[SimpleHttpServer](https://github.com/jJayyyyyyy/SimpleHttpServer)

<br>
