import { Component, OnInit } from '@angular/core';

//se agregan modulos para Http

import {AuthService} from '../services/auth.service';
import {Casa,CasaService } from 'src/app/services/casa.service'

import { Observable } from 'rxjs';
@Component({
  selector: 'app-admin',
  templateUrl: './admin.page.html',
  styleUrls: ['./admin.page.scss'],
})
export class AdminPage implements OnInit {

  private casas: Observable<Casa[]>;
  
 //se agrega servicio al constructor
  constructor(public servicio:AuthService,private casaService: CasaService) { }

  ngOnInit() {
     this.casas = this.casaService.getCasas();
  }

  

}
