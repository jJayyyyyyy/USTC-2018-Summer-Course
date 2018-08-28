#!/usr/bin/python3
# -*- coding: utf-8 -*-
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_host = '127.0.0.1'
port = 8000
s.bind( (server_host, port) )

print('server_host: %s\tport: %d\n' % (server_host, port))

while True:
	msg, addr = s.recvfrom(1024)
	if not msg:
		print('Client offline!\n')
		break
	msg = msg.decode('utf-8')
	print('msg received: %s' % msg)
	
	msg = msg.upper();
	print('msg sent: %s\n' % msg)

	s.sendto(msg.encode('utf-8'), addr)

s.close()
