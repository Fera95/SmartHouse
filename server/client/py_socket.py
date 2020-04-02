import sys
import time
import simplejson as json
import socks

HOST = "localhost"
PORT = 1080

while (True):
    s = socks.socksocket()
    s.set_proxy(socks.HTTP, HOST, PORT)
    s.connect((HOST, PORT))

    # Send data
    msg = "POST / HTTP/1:1 \r\n"
    #msg += "Access-Control-Allow-Headers\r\n"
    #msg += "Access-Control-Allow-Origin: *\r\n"
    #msg += "Content-Type: text/plain\r\n\r\n"
    msg += input(">")
    s.send(msg.encode())

    # Recevie response
    data = s.recv(len(msg)+40000)
    s.close()

    # Process received data
    server_response = data.decode()

    if (server_response != ""):
        parsed_json = json.loads(server_response)
        print("Led 1: " + str(parsed_json['led_1']))
        print("Led 2: " + str(parsed_json['led_2']))
        print("Led 3: " + str(parsed_json['led_3']))
        print("Led 4: " + str(parsed_json['led_4']))
        print("Led 5: " + str(parsed_json['led_5']))
    else:
        print(server_response)

