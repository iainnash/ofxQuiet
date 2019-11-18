#pragma once

#include "ofMain.h"
#include "ofxQuiet.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int mouseX, int mouseY, int button);
    ofSoundStream soundStream;
    void onMessage1(size_t & length);
    void onMessage2(size_t & length);
    void audioOut(ofSoundBuffer & output);
    void audioIn(ofSoundBuffer & input);
    
    ofxQuietEncoder encoder1;
    ofxQuietEncoder encoder2;
    ofxQuietDecoder decoder1;
    ofxQuietDecoder decoder2;
};
