import { Component, OnInit } from '@angular/core';

//se agregan modulos para Http

import {AuthService} from '../services/auth.service';
import {Casa,CasaService } from 'src/app/services/casa.service'

import { Observable } from 'rxjs';
import { ThemeService } from '../services/theme.service';
import { DomSanitizer } from '@angular/platform-browser';
import { stringify } from 'querystring';
@Component({
  selector: 'app-admin',
  templateUrl: './admin.page.html',
  styleUrls: ['./admin.page.scss'],
})
export class AdminPage implements OnInit {

  public casas: Observable<Casa[]>;
  public luz1: any;
  public luz2: any;
  public luz3: any;
  public luz4: any;
  public luz5: any;
  public puerta1: any;
  public puerta2: any;
  public puerta3: any;
  public puerta4: any;
  public puerta5: any;
 

 
  

  
 //se agrega servicio al constructor
  constructor(public servicio:AuthService,private casaService: CasaService,
    private theme: ThemeService , private sanitizer : DomSanitizer) { 
      this.theme.cambiarTema("0");
    }

  ngOnInit() {
     this.casas = this.casaService.getCasas();
     this.theme.cambiarTema("0");
  }


  //Funcion para setear datos

  setData(dato1 :any,
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

      this.luz1 = dato1;
      this.luz2 = dato2;
      this.luz3 = dato3;
      this.luz4 = dato4;
      this.luz5 = dato5;

      this.puerta1 = dato6;
      this.puerta2 = dato7;
      this.puerta3 = dato8;
      this.puerta4 = dato9;
      this.puerta5 = dato10;
          
  }

  temaSalida(){
   this.cambiarTema("1");
  }

  cambiarTema(estado: string){
    this.theme.cambiarTema(estado);
  }

  getDynamicLuz1(){
    if(this.luz1 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Luz1:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Luz1:none');
    } 
  }

  getDynamicLuz2(){
    if(this.luz2 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Luz2:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Luz2:none');
    } 
  }

  getDynamicLuz3(){
    if(this.luz3 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Luz3:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Luz3:none');
    } 
  }


  getDynamicLuz4(){
    if(this.luz4 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Luz4:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Luz4:none');
    } 
  }

  getDynamicLuz5(){
    if(this.luz5 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Luz5:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Luz5:none');
    } 
  }

  getDynamicPuerta1(){
    if(this.puerta1 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta1:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta1:none');
    } 
  }

  getDynamicPuerta2(){
    if(this.puerta2 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta2:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta2:none');
    } 
  }

  getDynamicPuerta3(){
    if(this.puerta3 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta3:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta3:none');
    } 
  }

  getDynamicPuerta4(){
    if(this.puerta4 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta4:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta4:none');
    } 
  }

  getDynamicPuerta5(){
    if(this.puerta5 == "1"){
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta5:block');
    }else{
      return this.sanitizer.bypassSecurityTrustStyle('--Puerta5:none');
    } 
  }

}
