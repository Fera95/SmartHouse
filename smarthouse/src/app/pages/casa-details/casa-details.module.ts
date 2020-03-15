import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { CasaDetailsPageRoutingModule } from './casa-details-routing.module';

import { CasaDetailsPage } from './casa-details.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    CasaDetailsPageRoutingModule
  ],
  declarations: [CasaDetailsPage]
})
export class CasaDetailsPageModule {}
