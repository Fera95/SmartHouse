import { Component, OnInit } from '@angular/core';

//se agregan modulos para Http

import {AuthService} from '../services/auth.service';
@Component({
  selector: 'app-admin',
  templateUrl: './admin.page.html',
  styleUrls: ['./admin.page.scss'],
})
export class AdminPage implements OnInit {

  //se crea variable de resultados
  result: any=[];
  
 //se agrega servicio al constructor
  constructor(public servicio:AuthService) { }

  ngOnInit() {
  
  }

  

}
