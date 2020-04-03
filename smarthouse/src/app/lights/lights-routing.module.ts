import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { LightsPage } from './lights.page';

const routes: Routes = [
  {
    path: '',
    component: LightsPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class LightsPageRoutingModule {}
