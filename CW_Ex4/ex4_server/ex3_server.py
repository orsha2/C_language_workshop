#!/usr/bin/python2.7 -tt

import sys
from socket import *

END_OF_MSG = '\r\n\r\n'
MAX_SIZE_RECV = 1024
MSG = {
		'NOT_FOUND': 'HTTP/1.1 404 Not Found\r\n' \
					 'Content-type: text/html\r\n' \
					 'Content-length: 113\r\n\r\n' \
					 '<html><head><title>Not Found</title></head><body>\r\n' \
					 'Sorry, the object you requested was not found.\r\n' \
					 '</body></html>\r\n\r\n',
		'FOUND': 'HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: {}\r\n\r\n{}\r\n\r\n'
	}

class Server():

	def __init__(self):
		self._port = 1234 # self.get_port_number_from_cmd()
		self._socket = socket()
		self._socket.connect(('localhost', self._port))
		self._max_size_of_reqest = MAX_SIZE_RECV
		self._request_counter = 0
		self._recv_msg = ''

	def litsen_and_send(self):
		while True:
			self.read_msg_from_lb()
			is_counter_inside = self.is_counter_inside_msg()
			msg_to_send = self.get_msg(is_counter_inside)
			self._socket.send(msg_to_send.encode())
			self.clean_msg()

	def read_msg_from_lb(self):
		while END_OF_MSG not in self._recv_msg :
			current_msg = self._socket.recv(self._max_size_of_reqest).decode()
			self._recv_msg += str(current_msg)

	def get_msg(self,is_counter_inside ):
		msg_to_send = MSG['NOT_FOUND']
		if is_counter_inside:
			self._request_counter += 1
			msg_to_send = MSG['FOUND'].format(str(self._request_counter), str(self._request_counter))
		return msg_to_send

	def is_counter_inside_msg(self):
		if self._recv_msg.startswith('GET /counter'):
			return True
		return False

	def get_port_number_from_cmd(self):
		return int(sys.argv[1])

	def clean_msg(self):
		self._recv_msg = ''

server = Server()
server.litsen_and_send()



