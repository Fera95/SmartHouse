import sys
import time
import socks
import simplejson as json
import firebase_admin
import time
from firebase_admin import credentials, firestore
from time import sleep

HOST = "192.168.0.18"
PORT = 1080

cred = credentials.Certificate('key.json')
firebase_admin.initialize_app(cred)

db = firestore.client()

# Constantes
COLNAME = 'casas'
DOCNAME = '1hYGoarmfHZIuVuKrhPr'
TIME = 100000000

# Muestra toda la base de datos actual
def showAll():
	allDocs = db.collection(COLNAME).stream()
	for doc in allDocs:
		allDB='{} => {}'.format(doc.id, doc.to_dict())
	makeReadFile(allDB)	

# Hace un archivo con el estado de la base
def makeReadFile(allDB):
	fileDB = open('db','w+')
	fileDB.write(allDB)
	fileDB.close

def readFile():
	f = open('db','r')
	mensaje = f.read()
	f.close()
	  

def listenDocs(time):
	# Callback
	def on_snapshot(doc_snapshot, changes, read_time):
		for doc in doc_snapshot:
			#print(u'\n Received document snapshot: {}\n'.format(doc.id))

			showAll()
			#print('\n')
			readFile()

	doc_ref = db.collection(COLNAME).document(DOCNAME)
	doc_watch = doc_ref.on_snapshot(on_snapshot)

	# Tiempo antes de cerrar la conexión
	sleep(time)

	# Cerrar la conexión
	doc_watch.unsubscribe()

def recorrer(cadena):
	for contador in range(26,169):
		if cadena[contador]=='L':
			id=cadena[contador+3]
			status=cadena[contador+8]
			analizarLuz(id,status)
		elif cadena[contador]=='P':
			id=cadena[contador+6]
			status=cadena[contador+11]
			analizarPuerta(id,status)
	global msg
	msg='"'+led1+':'+led2+':'+led3+':'+led4+':'+led5+'"'
	#print(msg)

def analizarLuz(id,status):
	if(id=="1"):
		print("Luz1-> " + status)
		global led1
		led1=status
	elif(id=="2"):
		print("Luz2-> " + status)
		global led2
		led2=status
	elif(id=="3"):
		print("Luz3-> " + status)
		global led3
		led3=status
	elif(id=="4"):
		print("Luz4-> " + status)
		global led4
		led4=status
	else:
		print("Luz5-> " + status)
		global led5
		led5=status

def analizarPuerta(id,status):
	if(id=="1"):
		print("Puerta1-> " + status)
	elif(id=="2"):
		print("Puerta2-> " + status)
	elif(id=="3"):
		print("Puerta3-> " + status)
	elif(id=="4"):
		print("Puerta4-> " + status)
	else:
		print("Puerta5-> " + status)

while (True):
	#family=socket.AF_INET, type=socket.SOCK_STREAM, proto=0)
	s = socks.socksocket()
	s.connect((HOST, PORT))

	listenDocs(3)
	
	f = open('db','r')
	cadena = f.read()
	f.close()

	#print(cadena)

	for contador in range(26,169):
		if cadena[contador]=='L':
			id=cadena[contador+3]
			status=cadena[contador+8]
			analizarLuz(id,status)
		elif cadena[contador]=='P':
			id=cadena[contador+6]
			status=cadena[contador+11]
			analizarPuerta(id,status)
	global msg
	msg='"'+led1+':'+led2+':'+led3+':'+led4+':'+led5+'"'
	#print(msg)
	
	#msg format: "Bedroom:Bathroom:Hallway:Kitchen:Studio"
	#hola = input(">")

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
				#print(" Door Bedroom: " + str(parsed_json['door_1']))
				#print("Door Bathroom: " + str(parsed_json['door_2']))
				#print(" Door Hallway: " + str(parsed_json['door_3']))
				#print("  Door Kichen: " + str(parsed_json['door_4']))
				#print("  Door Studio: " + str(parsed_json['door_5']))
				val_upd = db.collection(COLNAME).document(DOCNAME)
				val_upd.update({'Puerta1': str(parsed_json['door_1'])})
				val_upd.update({'Puerta2': str(parsed_json['door_2'])})
				val_upd.update({'Puerta3': str(parsed_json['door_3'])})
				val_upd.update({'Puerta4': str(parsed_json['door_4'])})
				val_upd.update({'Puerta5': str(parsed_json['door_5'])})
			else:
				print(server_response)
		else:
			print("message has an incorrect format")
	else:
		print("Message is of incorrect length")
