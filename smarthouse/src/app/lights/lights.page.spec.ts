import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { LightsPage } from './lights.page';

describe('LightsPage', () => {
  let component: LightsPage;
  let fixture: ComponentFixture<LightsPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ LightsPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(LightsPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
