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

	#msg format: "Bedroom:Bathroom:Hallway:Kitchen:Studio"
	msg = input(">")

	if (len(msg) == 11):
		if ( (msg[0] == "\"" or msg[10] == "\"" ) and
             (msg[2] == ":" or msg[4] == ":" or msg[6] == ":" or msg[8] == ":" ) and
             (msg[1] == "1" or msg[1] == "0" ) and # LED
             (msg[3] == "1" or msg[3] == "0" ) and 
             (msg[5] == "1" or msg[5] == "0" ) and
             (msg[7] == "1" or msg[7] == "0" ) and 
             (msg[9] == "1" or msg[9] == "0" ) ):
			msg = msg.encode()
			s.send(msg)
			data = s.recv(len(msg)+40000)
			s.close()
			server_response = data.decode()
			
			if (server_response != ""):
				parsed_json = json.loads(server_response)
				print(" Door Bedroom: " + str(parsed_json['door_1']))
				print("Door Bathroom: " + str(parsed_json['door_2']))
				print(" Door Hallway: " + str(parsed_json['door_3']))
				print("  Door Kichen: " + str(parsed_json['door_4']))
				print("  Door Studio: " + str(parsed_json['door_5']))
			else:
				print(server_response)
		else:
			print("message has an incorrect format")
	else:
		print("Message is of incorrect length")

    





