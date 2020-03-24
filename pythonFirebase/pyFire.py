import firebase_admin
from firebase_admin import credentials, firestore

cred = credentials.Certificate('key.json')
firebase_admin.initialize_app(cred)

db = firestore.client()

# Constantes
COLNAME = 'casas'
DOCNAME = '1hYGoarmfHZIuVuKrhPr'

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

def main():
    showAll()
    updateValue('Luz1','1')

main()


