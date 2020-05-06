import { Injectable } from '@angular/core';
import {AngularFireAuth} from '@angular/fire/auth';
import {User} from '../shared/user.class';
import {HttpClient,HttpHeaders, HttpClientModule} from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  public isLogged: any = false; 


  constructor(public afAuth: AngularFireAuth) {
    afAuth.authState.subscribe(user => (this.isLogged = user));
   }   //login
    async onLogin (user:User){
      try {
        return await this.afAuth.auth.signInWithEmailAndPassword(user.email,user.password); 
      } catch (error) {
        console.log('Error on Login',error);
      }
    } //register 
   async OnRegister(user:User){
     try{ 
       return await this.afAuth.auth.createUserWithEmailAndPassword(
         user.email,
         user.password
         );
     }
     catch(error){
        console.log('Error on Register', error);
     }
   }
  /* //Se obtienen datos
   getData(){
     return this.http.get("https://reqres.in/api/users?page=0&per_page=12");
   }*/

  

}
