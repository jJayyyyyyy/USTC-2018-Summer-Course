
###	2018.08.28晚18:30到21:30实验课内容 —— IP组网

##	实验目的

*	通过 `NetSim` 等软件进行仿真, 设计并验证 IP 组网过程

	`Cisco` 公司出产了很多类似的软件, 都可用于本次实验. 不过由于这些产品大多属于收费软件, 如果以后不去从事相关事业，仅为此次实验去买正版略贵

	(我可没说要去用盗版/破解版，就算用了，bug也是挺多的（逃

<br>

##	实验内容

*	具体内容可以参考 `assets` 中的课件，大致过程是这样

	*	拓扑结构

		![topo](https://github.com/jJayyyyyyy/USTC-2018-Summer-Course/blob/master/20180828/DailyTest/assets/topo.png)

	*	从控件中拖出几个 `Switch`, `Router`, `Win pc`, 把它们连接起来

	*	通过 `console` 配置每一个设备的 `ip`, `gateway`, `static route` 等内容

	*	如果配置正确, 则可以使局域网内机器可以互相 `ping` 通, 在 `Router` 上配置好路由表后, 也可以实现跨网机器间的互 `ping`

*	实验完成后还会有提问环节，题目和参考答案如下

	*	写出为一个 `Windows PC` 配置 `IP` 为 `192.168.1.2/24`, 网关为 `192.168.1.254` 的命令

		```
		:: 设置 IP 和 子网掩码
		C:> ipconfig /ip 192.168.1.2 255.255.255.0

		:: 设置网关
		C:> ipconfig /dg 192.168.1.254
		```

	*	为路由器配置一条静态转发表的命令, 目标网络为 `192.168.1.0/24`, 下一跳为 `192.168.1.254`

		```
		Router(config)# ip route 192.168.1.0 255.255.255.0 192.168.1.254
		```

	*	第 `23` 页图中只为其配置图中所示的静态路由，不配置一条相反的路径时，图最左边 `network` 框内的主机能否 `ping` 通 `172.16.1.5` ？为什么？

		```
		不能，因为 `ping` 是一个 `请求-响应` 的过程。如果配置了 `A->B` 的路径，则 `请求包` 可以顺利传递，但是当 `B` 中的机器返回 `响应包` 的时候，因为，没有配置 `B->A` 的路由表，所以 `Router B` 就不知道该把这个包往哪发了，结果 `A` 中的机器就无法收到 `响应包`，所以无法 `ping` 通
		```

	*	在实验拓扑中，如果不配置 `RouterA -> RouterC` 的静态路由，A1能否ping通A2，A1能否ping通C1？为什么？

		```
		A1 -> A2 可以 ping 通, 因为两者处于同一个局域网

		A1 -> C1 无法 ping 通, 因为两者不在同一个网络，而且路由器没有配置相关的路由表，RouterA 不知道该把这个请求包往哪发，于是就丢弃了 (host unreachable)
		```
<br>

##	相关阅读

*	[计算机网络, 韩立刚](https://www.bilibili.com/video/av9876107)

*	[Wikipedia, Ping](https://en.wikipedia.org/wiki/Ping_(networking_utility))

*	[路由器的工作原理](http://blog.51cto.com/13401027/1975059)

<br>

##	跋

*	Special Thanks to cc

<br>