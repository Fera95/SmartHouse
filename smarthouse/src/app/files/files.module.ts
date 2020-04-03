import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { FilesPageRoutingModule } from './files-routing.module';

import { FilesPage } from './files.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    FilesPageRoutingModule
  ],
  declarations: [FilesPage]
})
export class FilesPageModule {}
