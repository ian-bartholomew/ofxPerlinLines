#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofEasyCam cam;
        ofVboMesh mesh;
        ofLight light;
        
        float radius;
        int max;
        float zfreq;
        float zamt;
    
    	ofxPanel gui;
    
        ofxFloatSlider mXmulti;
        ofxFloatSlider mYmulti;
        ofxFloatSlider mZmulti;
    
};
