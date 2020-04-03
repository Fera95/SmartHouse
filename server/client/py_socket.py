import sys
import time
import socks
import simplejson as json

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
    
    if (server_response != ""):
        parsed_json = json.loads(server_response)
        print("Door 1: " + str(parsed_json['led_1']))
        print("Door 2: " + str(parsed_json['led_2']))
        print("Door 3: " + str(parsed_json['led_3']))
        print("Door 4: " + str(parsed_json['led_4']))
        print("Door 5: " + str(parsed_json['led_5']))
    else:
        print(server_response)

