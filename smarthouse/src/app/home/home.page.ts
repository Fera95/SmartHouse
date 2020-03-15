import { Component } from '@angular/core';
import {Router} from '@angular/router';
import {AngularFireAuth} from '@angular/fire/auth';
import {AuthService} from '../services/auth.service';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  constructor(private authSvc: AuthService , private router: Router, 
    private afAuth: AngularFireAuth) {}

    onLogout(){
      console.log('Logout!');
        this.afAuth.auth.signOut();
        this.router.navigateByUrl('/login');
    }

}
