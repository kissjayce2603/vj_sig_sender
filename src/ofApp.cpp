#include "ofApp.h"

void ofApp::setup() {
	sender.setup(HOST, PORT);
	ipad.setup(PORT);
	spoutReceiver.setup();
	ofColor initcolor(100, 100, 100);
	for (int i = 0; i < std::size(set_unit_colors); i++) {
		set_unit_colors[i] = initcolor;
		randomPosX[i] = ofRandom(0, pix.getWidth());
		randomPosY[i] = ofRandom(0, pix.getHeight());
	}
}

void ofApp::update() {
	while (ipad.hasWaitingMessages()) {
		ofxOscMessage m;
		ipad.getNextMessage(&m);
		if (m.getAddress() == "/ipad/method0") {
			method = 0;
			for (int i = 0; i < std::size(set_unit_colors); i++) {
				randomPosX[i] = ofRandom(pix.getWidth());
				randomPosY[i] = ofRandom(pix.getHeight());
			}
		}
		if (m.getAddress() == "/ipad/method1") {
			method = 1;
		}
		if (m.getAddress() == "/ipad/method2") {
			method = 2;
		}
		if (m.getAddress() == "/ipad/fe") {
			fe = m.getArgAsInt(0);
		}
		if (m.getAddress() == "/ipad/dc") {
			dc = m.getArgAsInt(0);
		}
	}
}

void ofApp::draw() {
	ofClear(0);
	int ux = U_X;
	int uy = U_Y;
	int unit_index = 0;
	
	ofDrawBitmapString("-----KontactLab-----SENDER-----", POS_X, POS_Y);

	for (int i = 0; i < uy; i++) {
		for (int j = 0; j < ux; j++) {
			ofSetColor(set_unit_colors[unit_index]);
			ofDrawRectangle(j * 60 + (POS_X + 1290), i * 60 + (POS_Y + 10), 50, 50);
			ofSetColor(255);
			ofDrawBitmapString(ofToString(unit_index), j * 60 + 1300 + POS_X, i * 60 + 25 + POS_Y);
			unit_index++;
		}
	}

	spoutReceiver.updateTexture();
	spoutReceiver.getTexture().draw(POS_X, POS_Y);
	spoutReceiver.getTexture().readToPixels(pix);

	for (int i = 0; i < std::size(set_unit_colors); i++) {
		
		switch (method) {
			case 0: set_unit_colors[i] = pix.getColor(randomPosX[i], randomPosY[i]); break;
			case 1: set_unit_colors[i] = setFlash(fe, dc); break;
			case 2: set_unit_colors[i] = setRandom(fe, dc); break;
			default: set_unit_colors[i] = pix.getColor(randomPosX[i], randomPosY[i]); break;
		}
		
		ofDrawBitmapString(ofToString(i), POS_X + 1290, POS_Y + 250 + (i + 1) * 12);
		ofDrawBitmapString(set_unit_colors[i], POS_X + 1290 + 50, POS_Y + 250 + (i + 1) * 12);
		sendOSC("/bg_color_zhongyi/", i, set_unit_colors[i]);
	}
}

void ofApp::keyPressed(int key) {
	if (key == '0') {
		method = 0;
		for (int i = 0; i < std::size(set_unit_colors); i++) {
			randomPosX[i] = ofRandom(pix.getWidth());
			randomPosY[i] = ofRandom(pix.getHeight());
			
		}
	}
	if (key == '1') {
		method = 1;
	}

	if (key == '2') {
		method = 2;
	}

}

void ofApp::exit() {
	spoutReceiver.exit();
}


//--------------------------------------------------------------------------------------------------

void ofApp::sendOSC(string address, int index, ofColor color) {
	ofxOscMessage m;
	m.setAddress(address + ofToString(index));
	m.addIntArg(color.r);
	m.addIntArg(color.g);
	m.addIntArg(color.b);
	sender.sendMessage(m);
}

ofColor ofApp::setRandom(int fe, int default) {
	ofColor c;

	if (ofGetFrameNum() % fe == 0) {
		c.r = ofRandom(255);
		c.g = ofRandom(255);
		c.b = ofRandom(255);
		return c;
	}
	else {
		return default;
	}
}
	

ofColor ofApp::setFlash(int fe, int default) {
	if (ofGetFrameNum() % fe == 0) {
		return ofRandom(255);
	}
	else {
		return default;
	}
	
}

//--------------------------------------------------------------------------------------------------