import socket
import sys
import time

HOST = "localhost"
PORT = 8080

while (True):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    msg = input()
    msg = msg.encode()
    s.send(msg)
    data = s.recv(len(msg)+40000)
    s.close()
    print ("Received: ", data.decode())
