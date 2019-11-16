#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // callback, outputs, inputs, sampleRate, bufferSize, nBuffers
    int inputs = 0;
    int outputs = 1;
    ofSoundStreamSettings settings;
    settings.numInputChannels = 1;
    settings.numOutputChannels = 2;
    settings.sampleRate = 44100;
    settings.setInListener(this);
    settings.setOutListener(this);
    soundStream.setup(settings);
    encoder1.setup("audible");
    encoder2.setup("audible");
    encoder1.addText("testing!!!");
    encoder2.addText("lol wut");
    
    decoder1.setup("audible");
    
    ofAddListener(decoder1.onMessage, this, &ofApp::onMessage1);
}

void ofApp::onMessage1(size_t & length) {
    cout << "has input: " << decoder1.consumeMessage() << endl;
}

void ofApp::audioOut(ofSoundBuffer & output) {
    encoder1.writeBufferChannel(output, 0);
    encoder2.writeBufferChannel(output, 1);
    // debug channel
}

void ofApp::audioIn(ofSoundBuffer & input) {
    decoder1.readBuffer(input);
    //decoder1.readBufferChannel(input, 1);
    //decoder2.readBufferChannel(input, 2);
}

int frameCount;
//--------------------------------------------------------------
void ofApp::update(){
    frameCount++;
    if (frameCount % 100 == 0) {
        encoder1.addText("testing!!!");
        encoder2.addText("lol wut");
    }
}

void ofApp::mousePressed(int mouseX, int mouseY, int button) {
    cout << "pressed " << endl;
    encoder1.addText("testing!!!");
    encoder2.addText("testing?!:");
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(200, 200, 0);
    ofDrawRectangle(0, 0, 20, 20);
}
