import sys
import time
import socks

HOST = "localhost"
PORT = 1080

while (True):
    #family=socket.AF_INET, type=socket.SOCK_STREAM, proto=0)
    s = socks.socksocket()
    s.connect((HOST, PORT))

    msg = input(">")
    msg = msg.encode()
    s.send(msg)
    data = s.recv(len(msg)+40000)
    s.close()
    server_response = data.decode()
    
    print(server_response)

