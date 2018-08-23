##	2018.08.22晚18:30到21:30实验课内容 —— 网络的使用和配置

1.	基础命令

	*	查看本机缓存

		```
		arp -an [ip]
		arp -a
		```

	*	查看本机的ip和mac

		```
		ifconfig		# Linux
		ipconfig -all		# Windows
		```

	*	查看本机路由

		```
		route print
		```

	*	查看本机到某个IP需要经历几个路由器

		```
		traceroute -ip
		```

	*	查看tcp连接

		```
		netstat
		```

	*	查看域名服务器

		```
		nslookup
		```

	*	网络诊断

		```
		ping
		```

	<br>

2.	实验内容

	*	网络命令的使用

		```
		ifconfig, route print, tracert, netstatm nslookup
		```

	*	Wireshark的使用

		```
		分析ARP, DNS, ping, http
		```

	<br>

3.	回答问题

	*	写出用 ping 指令向 www.baidu.com 发送 8 个字节大小的 ICMP 包指令

		```
		ping -l 80 -n 8 www.baidu.com
		```

	*	使用 Wireshark 软件抓取数据包分析网络包，在过滤器里面过滤出 源ip 为 192.168.1.10，目的 ip 为 192.168.1.20 的数据包。写出过滤表达式

		```
		ip.src==192.168.1.10 and ip.dst==192.168.1.20
		```

	*	使用 Wireshark 抓取一个 ARP 数据包分析各个字段的含义

		含以太网首部的帧格式如下，其中以太网首部占14字节，ARP报文占28字节，在 Wireshark 中点击相应的帧/报文，就会给出各个字段具体的内容
		
		![ether-arp](https://img-blog.csdn.net/20130816090639218?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvc2hhbnpoaXpp/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
