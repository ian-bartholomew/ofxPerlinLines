#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // GUI setup
    gui.setup("panel"); // most of the time you don't need a name
    gui.add(mXmulti.setup( "mXmulti", 0.01, 0, 2 ));
    gui.add(mYmulti.setup( "mYmulti", 0.1, 0, 2 ));
    gui.add(mZmulti.setup( "mZmulti", 0.2, 0, 2 ));
    
    radius = 800;
    max = 2000;
    
	ofSetVerticalSync(true);
//    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
//    mesh.addVertex(ofPoint(0,0,0)); // add center vertex
    mesh.addColor(ofColor(137,137,140,255)); // center is same as bg
    mesh.addNormal(ofVec3f(0,0,1)); // center normal points up
    
    zfreq = 3.;
    zamt = .3;
    
    //loop around and make verts in a circle, with a bit of a z-wave
    for (int i = 0; i < max; i++){
        float step = 2*PI/max; // step size around circle
        float theta = ofMap(i, 0, max-1, 0, 2*PI - step); //map i as circle divisions to actual radian values around the circle (note we don't go quite all the way around by one step, because it will be the same as where we started, so we'll just index that starting vertex when we make faces)
        
        float prevTheta = theta - step; //one step back
        float nextTheta = theta + step; // one step forward
        
        // create vertices in polar coordinates, plus a sine wave for z
        ofVec3f p(radius*cos(theta),radius*sin(theta), radius*zamt*sin(zfreq*theta) );
        // add this vertex
        mesh.addVertex(p);
        
        // we need these for calculating normals
        ofVec3f prev(radius*cos(prevTheta),radius*sin(prevTheta),radius*zamt*sin(zfreq*prevTheta) );
        ofVec3f next(radius*cos(nextTheta),radius*sin(nextTheta),radius*zamt*sin(zfreq*nextTheta) );
        
        // our normals for each triangle face is the cross product of the two vectors making up that sliver
        ofVec3f previousFaceNormal = prev.crossed(p);
        ofVec3f nextFaceNormal = p.crossed(next);
        
        /* notice here we go in the same direction: previous->current,current->next;
         we could similarly go next->current,current-prev, which would flip all of our normals;
         this might not be the best idea, but its certainly better than going previous->current,next->current, which would end up being quite awful.
         This is the concept of an "orientable mesh" or "face winding order", to be googled for more information.
         */
        
        // since we want smooth normals, we'll sum the two adjacent face normals, then normalize (since usually, only the direction and not the magnitude of the normal is what matters)
        mesh.addNormal((previousFaceNormal + nextFaceNormal).normalize());
        
        //add a color too
        ofColor c(255,255,255,50);
//        c.setHsb(40 + 30*sin(2*theta+PI),255,255,255);
        mesh.addColor(c);
    }
    
    //index our verts/normals/colors as a triangle fan
    for (int i=0, j = max-1; i < max; j=i++){
        mesh.addIndex(0);
        mesh.addIndex(i+1);
        mesh.addIndex(j+1);
    }
    
    
//        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < max; i++){
        float step = 2*PI/max; // step size around circle
        float theta = ofMap(i, 0, max-1, 0, 2*PI - step); //map i as circle divisions to actual radian values around the circle (note we don't go quite all the way around by one step, because it will be the same as where we started, so we'll just index that starting vertex when we make faces)
        float t = ofGetElapsedTimef();
        ofVec3f tmpVec = mesh.getVertex(i);
        tmpVec.x = radius*cos(theta) * ofSignedNoise(theta * t * mXmulti);
        tmpVec.y = radius*sin(theta) * ofSignedNoise(theta * t * mYmulti);
        tmpVec.z = radius*zamt*sin(zfreq*theta) * ofSignedNoise(theta * t * mZmulti);
        
        
        mesh.setVertex(i, tmpVec);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofEnableLighting();
    ofBackgroundGradient(ofColor(65,62,50),ofColor(25,22,10) );

    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest(); //make sure we test depth for 3d

    
    // disable normals if a key is pressed
    if(ofGetKeyPressed() || ofGetMousePressed()){
        mesh.disableNormals();
    }else{
        mesh.enableNormals();
    }
    
    cam.begin();
    ofNoFill();
    mesh.enableColors();
    mesh.drawWireframe();
//    mesh.draw();
    mesh.disableColors();
    


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
