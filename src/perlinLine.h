//
//  perlinLine.h
//  perlinLines
//
//  Created by HUGE | Ian Bartholomew on 7/11/14.
//
//

#pragma once

#include "ofMain.h"

class perlinLine {
    public:
        perlinLine();
        ~perlinLine();
    
        void setup(float zfreq, float zamt);
        void update(float x, float y, float z, float zfreq, float zamt);
        void draw();
        ofVboMesh getMesh();
    
    private:
        ofVboMesh mesh;
    
        float xSeed, ySeed, zSeed;
        float radius;
        int max;
};