#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // GUI setup
    gui.setup("panel"); // most of the time you don't need a name
    gui.add(mXmulti.setup( "mXmulti", 0.01, 0, 2 ));
    gui.add(mYmulti.setup( "mYmulti", 0.1, 0, 2 ));
    gui.add(mZmulti.setup( "mZmulti", 0.2, 0, 2 ));
    gui.add(mZfreq.setup( "mZfreq", 3.0, 0, 5 ));
    gui.add(mZamt.setup( "mZamt", 0.3, 0, 2 ));
    gui.add(mLineWidth.setup( "mLineWidth", 0.5, 0, 3 ));
    gui.add(mAlpha.setup( "mAlpha", 0.2, 0, 1 ));
    
	ofSetVerticalSync(true);
//    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    for (uint i = 0; i<2; i++){
        perlinLine p;
        mPerlinLine.push_back(p);
    }

    for(std::vector<perlinLine>::iterator it = mPerlinLine.begin(); it != mPerlinLine.end(); ++it) {
        it->setup(mZfreq, mZamt);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for(std::vector<perlinLine>::iterator it = mPerlinLine.begin(); it != mPerlinLine.end(); ++it) {
        it->update(mXmulti, mYmulti, mZmulti, mZfreq, mZamt);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofEnableLighting();
    ofBackgroundGradient(ofColor(65,62,50),ofColor(25,22,10) );

    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest(); //make sure we test depth for 3d

    

    cam.begin();

    ofVboMesh mesh1 = mPerlinLine.at(0).getMesh();
    ofVboMesh mesh2 = mPerlinLine.at(1).getMesh();
    
    vector<ofVec3f>& verts = mesh1.getVertices();
    vector<ofVec3f>& verts2 = mesh2.getVertices();
    
    for(unsigned int i = 0; i < verts.size(); i++){
        glLineWidth(mLineWidth);
        glColor4f(1.0, 1.0, 1.0, mAlpha);
        glBegin(GL_LINES);
        glVertex3f(verts[i].x,verts[i].y,verts[i].z);
        glVertex3f(verts2[i].x,verts2[i].y,verts2[i].z);
        glEnd();
    }
    
//    for(std::vector<perlinLine>::iterator it = mPerlinLine.begin(); it != mPerlinLine.end(); ++it) {
//        it->draw();
//    }
    

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
