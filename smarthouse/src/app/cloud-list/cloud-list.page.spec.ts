import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { CloudListPage } from './cloud-list.page';

describe('CloudListPage', () => {
  let component: CloudListPage;
  let fixture: ComponentFixture<CloudListPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CloudListPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(CloudListPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
