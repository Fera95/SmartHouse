import { Component, OnInit } from '@angular/core';
import {Router} from '@angular/router';
import {AuthService} from '../services/auth.service';
import {User} from '../shared/user.class';
import { ToastController } from '@ionic/angular';

@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {
  user: User = new User();
  
  constructor(private toastCtrl: ToastController, private router: Router, private authSvc: AuthService) { }

  ngOnInit() {
  }

  async onLogin(){
    const user = await this.authSvc.onLogin(this.user);
    
  
  if(user){
    this.router.navigateByUrl('/');
    this.showToast('Loggeado');
    console.log('Loggeo exitoso');
    
  }
  else{
    
    this.showToast('Email y/o contraseña invalidos');
  }
}
showToast(msg) {
  this.toastCtrl.create({
    message: msg,
    duration: 2000
  }).then(toast => toast.present());
}

}
