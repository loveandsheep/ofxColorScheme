//
//  ofxColorScheme.h
//
//  Created by Ovis aries on 2014/05/23.
//
//

#ifndef __ofxColorPaletteStudy__ofxColorScheme__
#define __ofxColorPaletteStudy__ofxColorScheme__

#include "ofMain.h"

enum ofxColorSchemeClass{
	OFX_COLORSCHEME_BASE,
	OFX_COLORSCHEME_MAIN,
	OFX_COLORSCHEME_ACCENT
};

class ofxColorScheme{
public:

	ofFloatColor	getFloatColor(ofxColorSchemeClass Class,int index);
	ofFloatColor&	getFloatColorRef(ofxColorSchemeClass Class,int index);
	ofColor			getColor(ofxColorSchemeClass Class,int index);

	void			setColor(ofFloatColor Color,ofxColorSchemeClass Class,int index);

	void			drawUI(int x,int y);
	void			loadScheme(string path);
	void			saveScheme(string path);
	void			resetScheme();
	void			addScheme(ofxColorSchemeClass Class);
//	void			removeScheme(ofxColorSchemeClass Class,int index);
	void			pushCurrentColor();
	void			pullCurrentSchemeColor();

	ofxColorScheme(){
		ofFloatColor b,m,c;
		b.setHsb(0.0, 0.5, 0.3, 1.0);
		m.setHsb(0.0, 1.0, 0.7, 1.0);
		c.setHsb(0.1, 1.0, 1.0, 1.0);

		baseColors.assign(1, ofFloatColor(b));
		mainColors.assign(1, ofFloatColor(m));
		acntColors.assign(1, ofFloatColor(c));

		ofAddListener(ofEvents().mouseMoved, this, &ofxColorScheme::mouseMoved);
		ofAddListener(ofEvents().mousePressed, this, &ofxColorScheme::mousePressed);
		ofAddListener(ofEvents().mouseDragged, this, &ofxColorScheme::mouseDragged);
		ofAddListener(ofEvents().mouseReleased, this, &ofxColorScheme::mouseReleased);

		currentHue = 0.0;

		pArea_new	.set(275, 100, 60, 15);
		pArea_load	.set(275, 117, 60, 15);
		pArea_save	.set(275, 134, 60, 15);
		pArea_saveAs.set(275, 151, 60, 15);

		pArea_push	.set(210, 100, 60, 15);
		pArea_pull	.set(210, 117, 60, 15);

		currentHue = 0.0;
		currentSat = 1.0;
		currentBri = 1.0;
		currentColor.setHsb(0.0, 1.0, 1.0);

		schemeBarChanged = true;
		activeColor = &baseColors[0];
		activeRect	= &baseRects[0];
		activeClass = OFX_COLORSCHEME_BASE;

		currentFileName = "NewScheme";
		currentFilePath = "";
	}

	~ofxColorScheme(){

	}

	void drawPickUpPanel(int x,int y,int w,int h);
	void drawSchemeBar(int x,int y,int w,int h);
	void mouseSelecting(ofMouseEventArgs &arg);
	void saveAsScheme();
	void loadNewScheme();

	void mouseMoved		(ofMouseEventArgs &arg);
	void mousePressed	(ofMouseEventArgs &arg);
	void mouseDragged	(ofMouseEventArgs &arg);
	void mouseReleased	(ofMouseEventArgs &arg);

	vector<ofFloatColor>	baseColors;
	vector<ofFloatColor>	mainColors;
	vector<ofFloatColor>	acntColors;

	bool schemeBarChanged;
	vector<ofRectangle>		baseRects;
	vector<ofRectangle>		mainRects;
	vector<ofRectangle>		acntRects;

	ofFloatColor*			activeColor;
	ofRectangle*			activeRect;
	ofxColorSchemeClass		activeClass;

	string					currentFileName;
	string					currentFilePath;
	float					currentHue;
	float					currentSat;
	float					currentBri;
	ofFloatColor			currentColor;

	ofRectangle window_rect;
	ofRectangle pickSB_rect;
	ofRectangle pickH_rect;

	ofRectangle pArea_push;
	ofRectangle pArea_pull;
	ofRectangle pArea_new;
	ofRectangle pArea_save;
	ofRectangle pArea_saveAs;
	ofRectangle pArea_load;
};

#endif /* defined(__ofxColorPaletteStudy__ofxColorScheme__) */
