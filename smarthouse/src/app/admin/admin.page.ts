import { Component, OnInit } from '@angular/core';

//se agregan modulos para Http

import {AuthService} from '../services/auth.service';
import {Casa,CasaService } from 'src/app/services/casa.service'

import { Observable } from 'rxjs';
import { ThemeService } from '../services/theme.service';
@Component({
  selector: 'app-admin',
  templateUrl: './admin.page.html',
  styleUrls: ['./admin.page.scss'],
})
export class AdminPage implements OnInit {

  public casas: Observable<Casa[]>;

  public estado: string;

  
 //se agrega servicio al constructor
  constructor(public servicio:AuthService,private casaService: CasaService,
    private theme: ThemeService) { }

  ngOnInit() {
     this.casas = this.casaService.getCasas();
  }

  print(dato1 :any,
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
        var dato =dato1+dato2+dato3+dato4+dato5+dato6+dato7+dato8+dato9+dato10;
        this.estado = dato.toString();
  }



  cambiarTema(){
    this.theme.cambiarTema(this.estado);
  }

  

}
