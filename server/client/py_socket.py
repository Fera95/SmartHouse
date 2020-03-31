import sys
import time
import json
import importlib.util
spec = importlib.util.spec_from_file_location('rp2socket', './socket.py')
foo = importlib.util.module_from_spec(spec)
spec.loader.exec_module(foo)
foo.MyClass()

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
    server_response = data.decode()
    
    parsed_json = json.loads(server_response)

    print("Led 1: " + str(parsed_json['led_1']))
    print("Led 2: " + str(parsed_json['led_2']))
    print("Led 3: " + str(parsed_json['led_3']))
    print("Led 4: " + str(parsed_json['led_4']))
    print("Led 5: " + str(parsed_json['led_5']))

