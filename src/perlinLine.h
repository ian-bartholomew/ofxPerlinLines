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
    
        void setup();
        void update(float x, float y, float z);
        void draw();
    
    
    private:
        ofVboMesh mesh;
    
        float radius;
        int max;
        float zfreq;
        float zamt;
};