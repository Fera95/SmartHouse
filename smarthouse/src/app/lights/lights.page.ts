import { Component, OnInit } from '@angular/core';
import {Casa,CasaService } from 'src/app/services/casa.service'
import { ThemeService } from '../services/theme.service';
import { Observable } from 'rxjs';
import { analytics } from 'firebase';

import { ActivatedRoute, Router } from '@angular/router';
import { ToastController } from '@ionic/angular';
import { DomSanitizer } from '@angular/platform-browser';
 

@Component({
  selector: 'app-lights',
  templateUrl: './lights.page.html',
  styleUrls: ['./lights.page.scss'],
})
export class LightsPage implements OnInit {


 public casa: Casa = {
    id : '',
    Luz1: '',
    Luz2: '',
    Luz3: '',
    Luz4: '',
    Luz5: '',
    Puerta1: '',
    Puerta2: '',
    Puerta3: '',
    Puerta4: '',
    Puerta5: '',
    
  };
 

  

  public casas: Observable<Casa[]>;

  public id: string;
  public luz1: string;
  public luz2: string;
  public luz3: string;
  public luz4: string;
  public luz5: string;
  public puerta1: string;
  public puerta2: string;
  public puerta3: string;
  public puerta4: string;
  public puerta5: string;

  
  constructor(private theme: ThemeService,private casaService: CasaService,private activatedRoute: ActivatedRoute, 
    private toastCtrl: ToastController, private router: Router,private sanitizer : DomSanitizer) { }

  ngOnInit() {
    this.casas = this.casaService.getCasas();
    
    this.theme.cambiarTema("1");
  }

//Funcion para setear datos

setData(id:any
  ,dato1 :any,
  dato2 :any,
  dato3 :any,
  dato4 :any,
  dato5 :any,
  dato6 :any,
  dato7 :any,
  dato8 :any,
  dato9 :any,
  dato10 :any,
  ){
    this.id = id.toString();
    this.luz1 = dato1.toString();
    this.luz2 = dato2.toString();
    this.luz3 = dato3.toString();
    this.luz4 = dato4.toString();
    this.luz5 = dato5.toString();

    this.puerta1 = dato6.toString();
    this.puerta2 = dato7.toString();
    this.puerta3 = dato8.toString();
    this.puerta4 = dato9.toString();
    this.puerta5 = dato10.toString();
    this.casa.id = this.id;
    this.casa.Luz1 = this.luz1;
    this.casa.Luz2 = this.luz2;
    this.casa.Luz3 = this.luz3;
    this.casa.Luz4 = this.luz4;
    this.casa.Luz5 = this.luz5;

    this.casa.Puerta1 = this.puerta1;
    this.casa.Puerta2 = this.puerta2;
    this.casa.Puerta3 = this.puerta3;
   this.casa.Puerta4 = this.puerta4;
    this.casa.Puerta5 = this.puerta5;
 

}

 

  
  setLuz1() {
  
    var luz1 = this.casa.Luz1;
    let dato = luz1.toString();
   if(dato === "0"){
    this.casa.Luz1 = '1';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
   else{
    this.casa.Luz1 = '0';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
  }

  setLuz2() {
  
    var luz2 = this.casa.Luz2;
    let dato = luz2.toString();
   if(dato === "0"){
    this.casa.Luz2 = '1';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
   else{
    this.casa.Luz2 = '0';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
  }

  setLuz3() {
  
    var luz3 = this.casa.Luz3;
    let dato = luz3.toString();
   if(dato === "0"){
    this.casa.Luz3 = '1';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
   else{
    this.casa.Luz3 = '0';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
  }

  setLuz4() {
  
    var luz4 = this.casa.Luz4;
    let dato = luz4.toString();
   if(dato === "0"){
    this.casa.Luz4 = '1';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
   else{
    this.casa.Luz4 = '0';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
  }


  setLuz5() {
  
    var luz5 = this.casa.Luz5;
    let dato = luz5.toString();
   if(dato === "0"){
    this.casa.Luz5 = '1';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
   else{
    this.casa.Luz5 = '0';
    this.casaService.updateCasa(this.casa).then(() => {
      this.showToast('Casa updated');
    }, err => {
      this.showToast('There was a problem updating your casa :(');
    });
    ;
   }
  }

  getDynamicLuz1(){
    if(this.luz1 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle1:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle1:none');
    } 
  }

  getDynamicLuz2(){
    if(this.luz2 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle2:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle2:none');
    } 
  }

  getDynamicLuz3(){
    if(this.luz3 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle3:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle3:none');
    } 
  }

  getDynamicLuz4(){
    if(this.luz4 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle4:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle4:none');
    } 
  }

  getDynamicLuz5(){
    if(this.luz5 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle5:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Toggle5:none');
    } 
  }

  showToast(msg) {
    this.toastCtrl.create({
      message: msg,
      duration: 2000
    }).then(toast => toast.present());
  }

}
