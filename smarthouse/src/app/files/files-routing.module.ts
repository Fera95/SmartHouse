import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { FilesPage } from './files.page';

const routes: Routes = [
  {
    path: '',
    component: FilesPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class FilesPageRoutingModule {}
