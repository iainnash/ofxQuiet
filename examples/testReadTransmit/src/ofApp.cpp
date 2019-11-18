#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSoundStreamSettings settings;
    settings.numInputChannels = 2;
    settings.numOutputChannels = 2;
    settings.sampleRate = 44100;
    settings.bufferSize = 512;
    settings.setInListener(this);
    settings.setOutListener(this);
    for (auto device : soundStream.getDeviceList()) {
        cout << "devices: " << endl;
        cout << device << endl;
    }
    auto deviceToUse = soundStream.getMatchingDevices("Scarlett 2i2");
    settings.setInDevice(deviceToUse.at(0));
    settings.setOutDevice(deviceToUse.at(0));
    soundStream.setup(settings);
    
    encoder1.setup("audible");
    encoder2.setup("audible");
    encoder1.addText("testing!!!");
    encoder2.addText("lol wut");
    
    decoder1.setup("audible");
    decoder2.setup("audible");
    
    ofAddListener(decoder1.onMessage, this, &ofApp::onMessage1);
    ofAddListener(decoder2.onMessage, this, &ofApp::onMessage2);
}

void ofApp::onMessage1(size_t &length) {
    auto decoder1Data = decoder1.consumeMessage();
    cout << "[decoder 1] has data: " << decoder1Data << endl;
}

void ofApp::onMessage2(size_t &length) {
    auto decoder2Data = decoder2.consumeMessage();
    cout << "[decoder 2] has data: " << decoder2Data << endl;
}

void ofApp::audioOut(ofSoundBuffer & output) {
    encoder1.writeBufferChannel(output, 0);
    encoder2.writeBufferChannel(output, 1);
}

void ofApp::audioIn(ofSoundBuffer & input) {
    decoder1.readBufferChannel(input, 0);
    decoder2.readBufferChannel(input, 1);
}

int frameCount;
//--------------------------------------------------------------
void ofApp::update(){
    frameCount++;
    if (frameCount % 100 == 0) {
        encoder1.addText("testing!!!");
        //encoder2.addText("lol wut");
    }
    if (frameCount % 45 == 0) {
        encoder2.addText("lol wut");
    }
}

void ofApp::mousePressed(int mouseX, int mouseY, int button) {
    cout << "pressed " << endl;
    encoder1.addText("testing!!!");
    encoder2.addText("foobar?!:");
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(200, 200, 0);
    ofDrawRectangle(0, 0, 20, 20);
}
