#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // GUI setup
    gui.setup("panel"); // most of the time you don't need a name
    gui.add(mXmulti.setup( "mXmulti", 0.01, 0, 2 ));
    gui.add(mYmulti.setup( "mYmulti", 0.1, 0, 2 ));
    gui.add(mZmulti.setup( "mZmulti", 0.2, 0, 2 ));
    

    
	ofSetVerticalSync(true);
//    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    mPerlinLine.setup();


}

//--------------------------------------------------------------
void ofApp::update(){
    
    mPerlinLine.update(mXmulti, mYmulti, mZmulti);

}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofEnableLighting();
    ofBackgroundGradient(ofColor(65,62,50),ofColor(25,22,10) );

    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest(); //make sure we test depth for 3d

    

    cam.begin();

    mPerlinLine.draw();

    //    ofSetColor(137,137,140);
    //    ofFill();
    
    
#ifndef TARGET_OPENGLES
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1,-1);
#endif    
    
    cam.end();

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
