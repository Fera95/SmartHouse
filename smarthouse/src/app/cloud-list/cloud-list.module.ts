import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { CloudListPageRoutingModule } from './cloud-list-routing.module';

import { CloudListPage } from './cloud-list.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    CloudListPageRoutingModule
  ],
  declarations: [CloudListPage]
})
export class CloudListPageModule {}
