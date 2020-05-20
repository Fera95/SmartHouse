import { NgModule } from '@angular/core';
import { PreloadAllModules, RouterModule, Routes } from '@angular/router';
import {AuthGuard} from './guards/auth.guard';
const routes: Routes = [
  { path: '', redirectTo: 'home', pathMatch: 'full' },
  { path: 'home', loadChildren: () => import('./home/home.module').then( m => m.HomePageModule)
},
  {
    path: 'register',
    loadChildren: () => import('./register/register.module').then( m => m.RegisterPageModule)
  },
  {
    path: 'login',
    loadChildren: () => import('./login/login.module').then( m => m.LoginPageModule)
  },
  {
    path: 'admin',
    loadChildren: () => import('./admin/admin.module').then( m => m.AdminPageModule)
  },
  {
    path: 'casa-details',
    loadChildren: () => import('./pages/casa-details/casa-details.module').then( m => m.CasaDetailsPageModule)
  },
  {
    path: 'casa-details/:id',
    loadChildren: () => import('./pages/casa-details/casa-details.module').then( m => m.CasaDetailsPageModule)
  },
  {
    path: 'files',
    loadChildren: () => import('./files/files.module').then( m => m.FilesPageModule)
  },
  {
    path: 'cloud-list',
    loadChildren: () => import('./cloud-list/cloud-list.module').then( m => m.CloudListPageModule)
  },
  {
    path: 'lights',
    loadChildren: () => import('./lights/lights.module').then( m => m.LightsPageModule)
  }



];

@NgModule({
  imports: [
    RouterModule.forRoot(routes, { preloadingStrategy: PreloadAllModules })
  ],
  exports: [RouterModule]
})
export class AppRoutingModule { }
