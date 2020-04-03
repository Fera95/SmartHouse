import { Injectable } from '@angular/core';
import { AngularFirestore, AngularFirestoreCollection, AngularFirestoreDocument, DocumentReference } from '@angular/fire/firestore';
import { map, take } from 'rxjs/operators';
import { Observable } from 'rxjs';
 
export interface Casa {
  id?: string,
  Luz1: string,
  Luz2: string,
  Luz3: string,
  Luz4: string,
  Luz5: string,
  Puerta1: string,
  Puerta2: string,
  Puerta3: string,
  Puerta4: string,
  Puerta5: string
}

 
@Injectable({
  providedIn: 'root'
})
export class CasaService {


  private casas: Observable<Casa[]>;
  private casaCollection: AngularFirestoreCollection<Casa>;
 
  constructor(private afs: AngularFirestore) {
    this.casaCollection = this.afs.collection<Casa>('casas');
    this.casas = this.casaCollection.snapshotChanges().pipe(
      map(actions => {
        return actions.map(a => {
          const data = a.payload.doc.data();
          const id = a.payload.doc.id;
          return { id, ...data };
        });
      })
    );
  }
 
  getCasas(): Observable<Casa[]> {
    return this.casas;
  }
 
  getCasa(id: string): Observable<Casa> {
    return this.casaCollection.doc<Casa>(id).valueChanges().pipe(
      take(1),
      map(casa => {
        casa.id = id;
        return casa
      })
    );
  }

 
  updateCasa(casa: Casa): Promise<void> {
    return this.casaCollection.doc(casa.id).update({
      
      Luz1: casa.Luz1,
      Luz2:  casa.Luz2,
      Luz3:  casa.Luz3,
      Luz4:  casa.Luz4,
      Luz5:  casa.Luz5,
      Puerta1:  casa.Puerta1,
      Puerta2: casa.Puerta2,
      Puerta3: casa.Puerta3,
      Puerta4: casa.Puerta4,
      Puerta5: casa.Puerta5



     });
  }
 
 
}