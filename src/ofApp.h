#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxSpout2Receiver.h"

# define PORT 110110
# define HOST "127.0.0.1"
# define MAX_UNITS 15
# define POS_X 10
# define POS_Y 10
# define U_X 5
# define U_Y 3

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void exit();

	void sendOSC(string address, int index, ofColor color);

	ofColor setRandom(int fe, int default);
	ofColor setFlash(int fe, int default);
		
	ofxOscSender sender;
	ofxOscReceiver ipad;

	ofColor set_unit_colors[MAX_UNITS];
	ofColor fixedRandomArray[MAX_UNITS];
	int randomPosX[MAX_UNITS];
	int randomPosY[MAX_UNITS];
	int method;
	int fe;
	int dc;

	ofxSpout2::Receiver spoutReceiver;
	ofPixels pix;
};

