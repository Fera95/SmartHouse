import { Component, OnInit } from '@angular/core';
import { InAppBrowser } from '@ionic-native/in-app-browser/ngx';
import * as firebase from 'firebase/app';


import 'firebase/storage'; 


import { ToastController } from '@ionic/angular';
import { ImagePicker } from '@ionic-native/image-picker/ngx';
import { ActionSheetController, Platform } from '@ionic/angular';
import {
  MediaCapture,
  MediaFile,
  CaptureError
} from '@ionic-native/media-capture/ngx';
<<<<<<< HEAD
import {  FileEntry } from '@ionic-native/File';
=======
>>>>>>> de17949937721424d1eea86fefbfa65a9c06b766
import { Media, MediaObject } from '@ionic-native/media/ngx';
import { StreamingMedia } from '@ionic-native/streaming-media/ngx';
import { PhotoViewer } from '@ionic-native/photo-viewer/ngx';
import { AngularFireStorage } from '@angular/fire/storage';
<<<<<<< HEAD
import { File } from '@ionic-native/file';
=======
import { File ,FileEntry} from '@ionic-native/file';
>>>>>>> de17949937721424d1eea86fefbfa65a9c06b766
import 'firebase/storage'; 
 
@Component({
  selector: 'app-cloud-list',
  templateUrl: './cloud-list.page.html',
  styleUrls: ['./cloud-list.page.scss']
})
export class CloudListPage implements OnInit {
  cloudFiles = [];
 
  constructor(private iab: InAppBrowser) {}
 
  ngOnInit() {
    this.loadFiles();
  }
 
  loadFiles() {
    this.cloudFiles = [];
 
    const storageRef = firebase.storage().ref('files');
    storageRef.listAll().then(result => {
      result.items.forEach(async ref => {
        this.cloudFiles.push({
          name: ref.name,
          full: ref.fullPath,
          url: await ref.getDownloadURL(),
          ref: ref
        });
      });
    });
  }
 
  openExternal(url) {
    this.iab.create(url);
  }
 
  deleteFile(ref: firebase.storage.Reference) {
    ref.delete().then(() => {
      this.loadFiles();
    });
  }
}