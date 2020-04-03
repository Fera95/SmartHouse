import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { LightsPageRoutingModule } from './lights-routing.module';

import { LightsPage } from './lights.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    LightsPageRoutingModule
  ],
  declarations: [LightsPage]
})
export class LightsPageModule {}
