import firebase_admin
import time
from firebase_admin import credentials, firestore
from time import sleep

cred = credentials.Certificate('key.json')
firebase_admin.initialize_app(cred)

db = firestore.client()

# Constantes
COLNAME = 'casas'
DOCNAME = '1hYGoarmfHZIuVuKrhPr'
TIME = 10000000

# Muestra toda la base de datos actual
def showAll():
    allDocs = db.collection(COLNAME).stream()
    for doc in allDocs:
        allDB='{} => {}'.format(doc.id, doc.to_dict())
    print(allDB)
    makeReadFile(allDB)

# Hace un archivo con el estado de la base
def makeReadFile(allDB):
    fileDB = open('db','w+')
    fileDB.write(allDB)
    fileDB.close    

# Actualiza el valor de un objeto (para poner 0 o 1 alguna luz o puerta)
def updateValue(obj, value):
    val_upd = db.collection(COLNAME).document(DOCNAME)
    val_upd.update({obj: value})
    showAll()

# Función que está buscando cambios hechos en la base de datos
def listenDocs(time):
    # Callback
    def on_snapshot(doc_snapshot, changes, read_time):
        for doc in doc_snapshot:
            print(u'\n Received document snapshot: {}\n'.format(doc.id))
            showAll()
            print('\n')

    doc_ref = db.collection(COLNAME).document(DOCNAME)
    doc_watch = doc_ref.on_snapshot(on_snapshot)

    # Tiempo antes de cerrar la conexión
    sleep(time)

    # Cerrar la conexión
    doc_watch.unsubscribe()

def main():
    showAll()
    listenDocs(TIME)

main()




