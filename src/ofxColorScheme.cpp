//
//  ofxColorScheme.cpp
//
//  Created by Ovis aries on 2014/05/23.
//
//

#include "ofxColorScheme.h"

void ofxColorScheme::drawUI(int x, int y){

	float mWidth = 360;

	window_rect.set(x, y, mWidth, 220);

	ofPushMatrix();
	ofTranslate(x, y);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(0, 0, 0, 170);
	ofRect(0,0,window_rect.width,window_rect.getHeight());

	drawPickUpPanel(20, 20, 280, 150);
	drawSchemeBar(20, 180, 320, 15);

	ofSetColor(currentColor);
	ofRect(210, 20, 140, 20);

	string info = "";
	info += "HSB :" + ofToString(int(currentHue*255),3,'0') + "," +
					  ofToString(int(currentSat*255),3,'0') + "," +
					  ofToString(int(currentBri*255),3,'0') + "\n";

	info += "RGB :" + ofToString(int(currentColor.r*255),3,'0') + "," +
					  ofToString(int(currentColor.g*255),3,'0') + "," +
					  ofToString(int(currentColor.b*255),3,'0') + "\n";

	ofSetColor(255);
	ofDrawBitmapString("CurrentColor", 210,15);
	ofDrawBitmapString("[" + currentFileName + "]", 20, 15);
	ofDrawBitmapString(info, 210, 60);

	//push,pull new save load
	ofSetColor(0, 0, 0, 100);
	ofRect(pArea_new);
	ofRect(pArea_load);
	ofRect(pArea_save);
	ofRect(pArea_push);
	ofRect(pArea_pull);
	ofRect(pArea_saveAs);

	ofSetColor(255);
	ofDrawBitmapString("New" , pArea_new .getPosition()+ofPoint(2,12));
	ofDrawBitmapString("Load", pArea_load.getPosition()+ofPoint(2,12));
	ofDrawBitmapString("Save", pArea_save.getPosition()+ofPoint(2,12));
	ofDrawBitmapString("SaveAs", pArea_saveAs.getPosition()+ofPoint(2,12));
	ofDrawBitmapString("Push", pArea_push.getPosition()+ofPoint(2,12));
	ofDrawBitmapString("Pull", pArea_pull.getPosition()+ofPoint(2,12));

	ofPopMatrix();
}



void ofxColorScheme::drawPickUpPanel(int x, int y,int w,int h){

	pickSB_rect.set(x, y, h, h);
	pickH_rect.set(x+h+10, y, 20, h);

	ofPushMatrix();
	ofTranslate(x, y);
	ofFloatColor cs[2];
	float hue = currentHue;
	cs[0].setHsb(hue, 1.0, 1.0);
	cs[1].setHsb(hue, 0.0, 1.0);

	glBegin(GL_TRIANGLE_STRIP);
	ofSetColor(cs[0]);
	glVertex2d(0, 0);

	ofSetColor(cs[1]);
	glVertex2d(h, 0);

	ofSetColor(cs[0]);
	glVertex2d(0, h);

	ofSetColor(cs[1]);
	glVertex2d(h, h);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	ofSetColor(0.0,0.0,0.0,0.0);
	glVertex2d(0, 0);

	ofSetColor(0.0,0.0,0.0,0.0);
	glVertex2d(h, 0);

	ofSetColor(0.0,0.0,0.0,255.0);
	glVertex2d(0, h);

	ofSetColor(0.0,0.0,0.0,255.0);
	glVertex2d(h, h);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0;i < h;i+=3){
		cs[0].setHsb(1.0*(float)i/h, 1.0, 1.0);
		ofSetColor(cs[0]);
		glVertex2d(h+10.0, i);
		glVertex2d(h+30.0, i);
	}
	glEnd();

	ofSetColor(255);
	ofNoFill();
	ofCircle(h*(1.0 - currentSat), h*(1.0 - currentBri), 5.0);
	ofCircle(h+20.0, h*currentHue, 5.0);
	ofFill();
	ofPopMatrix();
}

void ofxColorScheme::drawSchemeBar(int x,int y,int w,int h){
	float mWidth = w;

	ofPushMatrix();
	ofTranslate(x, y);

	if (schemeBarChanged){
		baseRects.clear();
		mainRects.clear();
		acntRects.clear();
	}

	float singleWidth = mWidth*0.6 / baseColors.size();
	int cnt = 0;
	for (float i = 0;i < mWidth*0.6;i+= singleWidth){
		ofSetColor(baseColors[cnt]);
		ofRect(i, 10, singleWidth, h);
		cnt++;
		if (schemeBarChanged)
			baseRects.push_back(ofRectangle(i+x, 10+y, singleWidth, h));
	}

	cnt = 0;
	singleWidth = mWidth*0.3 / mainColors.size();
	for (float i = 0;i < mWidth*0.3;i+= singleWidth){
		ofSetColor(mainColors[cnt]);
		ofRect(mWidth*0.6+i, 10, singleWidth, h);
		cnt++;
		if (schemeBarChanged)
			mainRects.push_back(ofRectangle(mWidth*0.6+i+x, 10+y, singleWidth, h));
	}

	cnt = 0;
	singleWidth = mWidth*0.1 / acntColors.size();
	for (float i = 0;i < mWidth*0.1;i+= singleWidth){
		ofSetColor(acntColors[cnt]);
		ofRect(mWidth*0.9+i, 10, singleWidth, h);
		cnt++;
		if (schemeBarChanged)
			acntRects.push_back(ofRectangle(mWidth*0.9+i+x, 10+y, singleWidth, h));
	}

	if (schemeBarChanged){
		activeRect  = &baseRects [0];
		activeColor = &baseColors[0];
		activeClass = OFX_COLORSCHEME_BASE;
	}

	schemeBarChanged = false;

	ofPopMatrix();

	ofSetColor(255);
	ofDisableAntiAliasing();
	float xx = activeRect->x + activeRect->width/2.0;
	ofTriangle(xx, activeRect->y,
			   xx-5, activeRect->y-8,
			   xx+5, activeRect->y-8);
	ofPushMatrix();
	ofTranslate(xx, activeRect->y-14);
	glLineWidth(2.0);
	ofLine(-5, 0, 5, 0);
	ofLine(0, -5, 0, 5);
	glLineWidth(1.0);

	ofEnableAntiAliasing();
	ofPopMatrix();
}

void ofxColorScheme::mouseMoved(ofMouseEventArgs &arg){

}

void ofxColorScheme::mousePressed(ofMouseEventArgs &arg){
	ofPoint pos;
	pos.set(arg.x - window_rect.x, arg.y - window_rect.y);

	mouseSelecting(arg);

	for (int i = 0;i < baseRects.size();i++){
		if (baseRects[i].inside(pos)){
			activeRect = &baseRects[i];
			activeColor = &baseColors[i];
			activeClass = OFX_COLORSCHEME_BASE;
		}
	}
	for (int i = 0;i < mainRects.size();i++){
		if (mainRects[i].inside(pos)){
			activeRect = &mainRects[i];
			activeColor = &mainColors[i];
			activeClass = OFX_COLORSCHEME_MAIN;
		}
	}
	for (int i = 0;i < acntRects.size();i++){
		if (acntRects[i].inside(pos)){
			activeRect = &acntRects[i];
			activeColor = &acntColors[i];
			activeClass = OFX_COLORSCHEME_ACCENT;
		}
	}

	if (pArea_push.inside(pos)){
		pushCurrentColor();
	}
	if (pArea_pull.inside(pos)){
		pullCurrentSchemeColor();
	}
	if (pArea_new.inside(pos)){
		resetScheme();
	}
	if (pArea_load.inside(pos)){
		loadNewScheme();
	}
	if (pArea_saveAs.inside(pos)){
		saveAsScheme();
	}
	if (pArea_save.inside(pos)){
		if (currentFileName == "NewScheme"){
			saveAsScheme();
		}else{
			saveScheme(currentFilePath);
		}
	}

	ofRectangle addButton;
	addButton.set(activeRect->x + activeRect->width/2.0 - 5,
				  activeRect->y - 19, 10, 10);
	if (addButton.inside(pos)){
		addScheme(activeClass);
	}
}

void ofxColorScheme::mouseDragged(ofMouseEventArgs &arg){
	mouseSelecting(arg);

}

void ofxColorScheme::mouseReleased(ofMouseEventArgs &arg){

}

void ofxColorScheme::mouseSelecting(ofMouseEventArgs &arg){
	ofPoint pos;
	pos.set(arg.x - window_rect.x, arg.y - window_rect.y);

	if (pickSB_rect.inside(pos)){
		currentSat = 1.0 - float(pos.x - pickSB_rect.x) / pickSB_rect.width;
		currentBri = 1.0 - float(pos.y - pickSB_rect.y) / pickSB_rect.height;
		currentColor.setHsb(currentHue,currentSat,currentBri);
	}
	if (pickH_rect.inside(pos)){
		currentHue = float(pos.y - pickH_rect.y) / pickH_rect.height;
		currentColor.setHsb(currentHue,currentSat,currentBri);
	}
}

//User interface functions
ofFloatColor ofxColorScheme::getFloatColor(ofxColorSchemeClass Class, int index){
	vector<ofFloatColor> *cols;

	if (Class == OFX_COLORSCHEME_BASE) cols = &baseColors;
	if (Class == OFX_COLORSCHEME_MAIN) cols = &mainColors;
	if (Class == OFX_COLORSCHEME_ACCENT) cols = &acntColors;

	index = MIN(cols->size()-1,index);

	if (cols->size() == 0){
		return NULL;
	}else if (cols->size() > 0){
		return (*cols)[index];
	}
}

void ofxColorScheme::setColor(ofFloatColor Color, ofxColorSchemeClass Class, int index){
	vector<ofFloatColor> *cols;

	if (Class == OFX_COLORSCHEME_BASE) cols = &baseColors;
	if (Class == OFX_COLORSCHEME_MAIN) cols = &mainColors;
	if (Class == OFX_COLORSCHEME_ACCENT) cols = &acntColors;

	index = MIN(cols->size()-1,index);

	if (cols->size() > 0){
		(*cols)[index].set(Color);
	}
}

ofFloatColor& ofxColorScheme::getFloatColorRef(ofxColorSchemeClass Class, int index){
	vector<ofFloatColor> *cols;

	if (Class == OFX_COLORSCHEME_BASE) cols = &baseColors;
	if (Class == OFX_COLORSCHEME_MAIN) cols = &mainColors;
	if (Class == OFX_COLORSCHEME_ACCENT) cols = &acntColors;

	index = MIN(cols->size()-1,index);

	return (*cols)[index];
}

ofColor ofxColorScheme::getColor(ofxColorSchemeClass Class, int index){
	ofColor c;
	ofFloatColor cf = getFloatColor(Class, index);

	if (cf == NULL){
		return NULL;
	}else{
		c.set(cf);
		return c;
	}
}

void ofxColorScheme::pushCurrentColor(){
	activeColor->set(currentColor);
}

void ofxColorScheme::pullCurrentSchemeColor(){
	currentColor.set(*activeColor);
	currentHue = currentColor.getHue();
	currentSat = currentColor.getSaturation();
	currentBri = currentColor.getBrightness();
}

void ofxColorScheme::addScheme(ofxColorSchemeClass Class){
	vector<ofFloatColor> *cols;

	if (Class == OFX_COLORSCHEME_BASE)		cols = &baseColors;
	if (Class == OFX_COLORSCHEME_MAIN)		cols = &mainColors;
	if (Class == OFX_COLORSCHEME_ACCENT)	cols = &acntColors;

	ofFloatColor newC;
	newC.set(1.0,1.0,1.0,1.0);
	cols->push_back(ofFloatColor(newC));
	schemeBarChanged = true;
}

void ofxColorScheme::resetScheme(){
	baseColors.clear();
	mainColors.clear();
	acntColors.clear();

	ofFloatColor b,m,c;
	b.setHsb(0.0, 0.5, 0.3, 1.0);
	m.setHsb(0.0, 1.0, 0.7, 1.0);
	c.setHsb(0.1, 1.0, 1.0, 1.0);

	baseColors.assign(1, ofFloatColor(b));
	mainColors.assign(1, ofFloatColor(m));
	acntColors.assign(1, ofFloatColor(c));

	schemeBarChanged = true;
	activeColor = &baseColors[0];
	activeRect	= &baseRects[0];
	activeClass = OFX_COLORSCHEME_BASE;
	currentFileName = "NewScheme";
}

void ofxColorScheme::saveAsScheme(){
	ofFileDialogResult res = ofSystemSaveDialog("myScheme.xml", "");
	saveScheme(res.filePath);
	currentFileName = res.fileName;
	currentFilePath = res.filePath;
}

void ofxColorScheme::loadNewScheme(){
	ofFileDialogResult res = ofSystemLoadDialog();
	loadScheme(res.filePath);
	currentFileName = res.fileName;
	currentFilePath = res.filePath;
}

void ofxColorScheme::saveScheme(string path){
	ofXml xml_base;
	xml_base.addChild("Root");
	xml_base.addChild("BaseColors");
	xml_base.addChild("MainColors");
	xml_base.addChild("AcntColors");

	xml_base.setTo("//Root");
	xml_base.setTo("BaseColors");
	for (int i = 0;i < baseColors.size();i++){
		ofXml xml;
		xml.addChild("BaseColor");
		xml.setTo("BaseColor");
		xml.addValue("Hue",baseColors[i].getHue());
		xml.addValue("Sat",baseColors[i].getSaturation());
		xml.addValue("Bri",baseColors[i].getBrightness());
		xml_base.addXml(xml);
	}

	xml_base.setTo("//Root");
	xml_base.setTo("MainColors");
	for (int i = 0;i < mainColors.size();i++){
		ofXml xml;
		xml.addChild("MainColor");
		xml.setTo("MainColor");
		xml.addValue("Hue",mainColors[i].getHue());
		xml.addValue("Sat",mainColors[i].getSaturation());
		xml.addValue("Bri",mainColors[i].getBrightness());
		xml_base.addXml(xml);
	}

	xml_base.setTo("//Root");
	xml_base.setTo("AcntColors");
	for (int i = 0;i < acntColors.size();i++){
		ofXml xml;
		xml.addChild("AccentColor");
		xml.setTo("AccentColor");
		xml.addValue("Hue",acntColors[i].getHue());
		xml.addValue("Sat",acntColors[i].getSaturation());
		xml.addValue("Bri",acntColors[i].getBrightness());
		xml_base.addXml(xml);
	}

	xml_base.save(path);
}

void ofxColorScheme::loadScheme(string path){
	ofXml xml_base;
	if (!xml_base.load(path)) return;

	baseColors.clear();
	mainColors.clear();
	acntColors.clear();
	xml_base.setTo("//Root");

	string par[3] = {"BaseColors","MainColors","AcntColors"};
	string chl[3] = {"BaseColor" ,"MainColor" ,"AccentColor"};

	for (int i = 0;i < 3;i++){
		if (xml_base.exists(par[i])){
			xml_base.setTo(par[i]);

			do {

				if (xml_base.getName() == par[i] && xml_base.setTo(chl[i])){
					do{

						ofFloatColor c;
						c.setHsb(xml_base.getValue<float> ("Hue"),
								 xml_base.getValue<float> ("Sat"),
								 xml_base.getValue<float> ("Bri"));
						if (i == 0) baseColors.push_back(c);
						if (i == 1) mainColors.push_back(c);
						if (i == 2) acntColors.push_back(c);

					} while (xml_base.setToSibling());
				}
				xml_base.setToParent();

			}while (xml_base.setToSibling());
		}
	}

	schemeBarChanged = true;
}