import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { FilesPage } from './files.page';

describe('FilesPage', () => {
  let component: FilesPage;
  let fixture: ComponentFixture<FilesPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FilesPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(FilesPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
