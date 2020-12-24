#!/usr/bin/python2.7 -tt

import socket
from time import sleep

class LB():

    def __init__(self):
        self._soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        self._soc.bind(('localhost', 1234))
        self._soc.listen(10)
        print("LB is wating....")
        (self._new_socket, address) = self._soc.accept()


    def run(self):
        for i in range(0,10):
            self._new_socket.send(b"GET /counter message\0\0 from server\r\n\r\n")
            sleep(3)
            print (self._new_socket.recv(1024))

        for i in range(0,3):
            self._new_socket.send(b"GET counter message from server\r\n\r\n")
            sleep(3)
            print (self._new_socket.recv(1024))

lb = LB()
lb.run()
