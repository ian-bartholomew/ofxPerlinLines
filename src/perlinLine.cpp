//
//  perlinLine.cpp
//  perlinLines
//
//  Created by HUGE | Ian Bartholomew on 7/11/14.
//
//

#include "perlinLine.h"

perlinLine::perlinLine(){};

perlinLine::~perlinLine(){};

void perlinLine::setup(float zfreq, float zamt){
    radius = 400;
    max = 1000;
    
//    xSeed = ofRandomf(), ofRandomf(), zSeed = ofRandomf();
    xSeed = ofRandom(-2,2), ySeed = ofRandom(-2,2), zSeed = ofRandom(-2,2);
    
    //    mesh.addVertex(ofPoint(0,0,0)); // add center vertex
    mesh.addColor(ofColor(137,137,140,255)); // center is same as bg
    mesh.addNormal(ofVec3f(0,0,1)); // center normal points up
    
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
    //    for (int i=0, j = max-1; i < max; j=i++){
    //        mesh.addIndex(0);
    //        mesh.addIndex(i+1);
    //        mesh.addIndex(j+1);
    //    }
    
    
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
}

void perlinLine::update(float x, float y, float z, float zfreq, float zamt){

    for (int i = 0; i < max; i++){
        float step = 2*PI/max; // step size around circle
        float theta = ofMap(i, 0, max-1, 0, 2*PI - step); //map i as circle divisions to actual radian values around the circle (note we don't go quite all the way around by one step, because it will be the same as where we started, so we'll just index that starting vertex when we make faces)
        float t = ofGetElapsedTimef();
        ofVec3f tmpVec = mesh.getVertex(i);
        
//        tmpVec.x = radius*cos(theta) * ofSignedNoise(theta * t * x, xSeed);
//        tmpVec.y = radius*sin(theta) * ofSignedNoise(theta * t * y, ySeed);
//        tmpVec.z = radius*zamt*sin(zfreq*theta) * ofSignedNoise(theta * t * z, zSeed);
        
        tmpVec.x = radius*cos(theta) * ofSignedNoise(theta * x, xSeed, t * 0.05f);
        tmpVec.y = radius*sin(theta) * ofSignedNoise(theta * y, ySeed, t * 0.05f);
        tmpVec.z = radius*zamt*sin(zfreq*theta) * ofSignedNoise(theta * z, zSeed, t * 0.05f);

        
//        tmpVec.x += ofSignedNoise(tmpVec.x, tmpVec.y, tmpVec.z, t);
//        tmpVec.y += ofSignedNoise(tmpVec.y, tmpVec.x, tmpVec.y, t);
//        tmpVec.z += ofSignedNoise(tmpVec.z, tmpVec.z, tmpVec.x, t);
        
        mesh.setVertex(i, tmpVec);
    }
}

void perlinLine::draw(){
    // disable normals if a key is pressed
    if(ofGetKeyPressed() || ofGetMousePressed()){
        mesh.disableNormals();
    }else{
        mesh.enableNormals();
    }
    

    ofNoFill();
    mesh.enableColors();
    //    mesh.drawWireframe();
    mesh.draw();
//    mesh.drawVertices();
    mesh.disableColors();
}

ofVboMesh perlinLine::getMesh(){
    return mesh;
}