import { Component, OnInit } from '@angular/core';
import {Router} from '@angular/router';
import {AuthService} from '../services/auth.service'; 
import {User} from '../shared/user.class'; 
import { ToastController } from '@ionic/angular';
@Component({
  selector: 'app-register',
  templateUrl: './register.page.html',
  styleUrls: ['./register.page.scss'],
})
export class RegisterPage implements OnInit {
  user: User = new User();

  constructor(private authSvc: AuthService,private router: Router,private toastCtrl: ToastController) { }

  ngOnInit() {
  }

  async onRegister(){
    const user = await this.authSvc.OnRegister(this.user);
    if(user){
      this.showToast('Usario creado con exito!');
      this.router.navigateByUrl('/');
    }
    else{
      this.showToast('Error creando usuario,recuerde utilizar formato válido de correo y que la contraseña debe ser de almenos 6 carácteres.');
    }
  }


  showToast(msg) {
    this.toastCtrl.create({
      message: msg,
      duration: 2000
    }).then(toast => toast.present());
  }

}
