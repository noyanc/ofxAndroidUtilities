#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogNotice("ofApp.cpp") << "Device Name:" << ofxandroidutilities.getDeviceName();
	ofLogNotice("ofApp.cpp") << "Android Api Level:" << ofxandroidutilities.getAndroidApiLevel();
	ofLogNotice("ofApp.cpp") << "Package Name:" << ofxandroidutilities.getPackageName();
	ofLogNotice("ofApp.cpp") << "Installer Package:" << ofxandroidutilities.getInstallerPackage();
	ofxandroidutilities.openURL("http://openframeworks.cc");
	ofLogNotice("ofApp.cpp") << "etc..";
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id){

}

//--------------------------------------------------------------
void ofApp::pause(){

}

//--------------------------------------------------------------
void ofApp::stop(){

}

//--------------------------------------------------------------
void ofApp::resume(){

}

//--------------------------------------------------------------
void ofApp::reloadTextures(){

}

//--------------------------------------------------------------
bool ofApp::backPressed(){
	return false;
}

//--------------------------------------------------------------
void ofApp::okPressed(){

}

//--------------------------------------------------------------
void ofApp::cancelPressed(){

}
