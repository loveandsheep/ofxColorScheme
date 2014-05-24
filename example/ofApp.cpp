#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	//Pick colors from ofxColorScheme instance.
	ofFloatColor baseCol = colorScheme.getColor(OFX_COLORSCHEME_BASE, 0);
	ofFloatColor mainCol = colorScheme.getColor(OFX_COLORSCHEME_MAIN, 0);
	ofFloatColor accentCol = colorScheme.getColor(OFX_COLORSCHEME_ACCENT, 0);

	//Use them.
	ofBackground(baseCol);

	for (int i = 0;i < ofGetWidth();i+= 20 ){

		if ((i/20) % 13 == 0)	ofSetColor(accentCol);
		else					ofSetColor(mainCol);

		ofRect(i, ofGetHeight(), 15, -ofNoise(ofGetElapsedTimef()/3.0,i/40.0)*100);

	}

	//draw UI for editting scheme.
	colorScheme.drawUI(10, 10);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
