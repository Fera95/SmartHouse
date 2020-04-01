import { Injectable, RendererFactory2, Inject, Renderer2} from '@angular/core';
import { DOCUMENT } from '@angular/common';

@Injectable({
  providedIn: 'root'
})
export class ThemeService {

  renderer: Renderer2; 
  tema : any;

  constructor(private rendererFactory: RendererFactory2,  @Inject(DOCUMENT) private document: Document) { 
    this.renderer = this.rendererFactory.createRenderer(null,null);
    this.tema = 'dark-theme';
  }

  cambiarTema(estado:string){
     if(estado=="0"){
      this.enableDark();
     } 
     if(estado=="1"){
      this.enableLight();
     }
     if(estado=="2"){
      this.enableExit();
     }
  }

  enableDark(){
      this.renderer.removeClass(this.document.body,this.tema);
      this.tema = 'dark-theme' ;
      this.renderer.addClass(this.document.body,this.tema);
  }

  enableLight(){  
    this.renderer.removeClass(this.document.body,this.tema);
    this.tema = 'light-theme' ;
    this.renderer.addClass(this.document.body,this.tema);

  }

  enableExit(){  
    this.renderer.removeClass(this.document.body,this.tema);
    this.tema = 'exit-theme' ;
    this.renderer.addClass(this.document.body,this.tema);
  }

}
