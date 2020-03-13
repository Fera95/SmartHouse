import { Injectable } from '@angular/core';
import { AngularFirestore, AngularFirestoreCollection, AngularFirestoreDocument, DocumentReference } from '@angular/fire/firestore';
import { map, take } from 'rxjs/operators';
import { Observable } from 'rxjs';
 
export interface Casa {
  id?: string,
  name: string,
  notes: string
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
 
  addCasa(casa: Casa): Promise<DocumentReference> {
    return this.casaCollection.add(casa);
  }
 
  updateCasa(casa: Casa): Promise<void> {
    return this.casaCollection.doc(casa.id).update({ name: casa.name, notes: casa.notes });
  }
 
  deleteIdea(id: string): Promise<void> {
    return this.casaCollection.doc(id).delete();
  }
}