#!/usr/bin/python3
# -*- coding: utf-8 -*-
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_host = '127.0.0.1'
port = 8000

while True:
	data = input('msg to be sent: ')
	s.sendto(data.encode('utf-8'), (server_host, port))
	if not data:
		print('Quit!\n')
		break
	print( 'msg from server: %s\n' % s.recv(1024).decode('utf-8') )

s.close()
