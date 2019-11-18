#pragma once

#include "quiet.h"
#include "ofSoundBuffer.h"
#include "ofEvent.h"
#include "quiet/decoder.h"
#include <vector>
#include <string>

class ofxQuietDecoder {
public:
    void setup(const char *profileName);
    void setup(const char *profileName, const char *profilePath);
    size_t readBuffer(ofSoundBuffer & buf);
    size_t readBufferChannel(ofSoundBuffer &buf, size_t channel);
    ofEvent<size_t> onMessage;
    std::string consumeMessage();
    bool hasData();
private:
    void setupWithOptions(quiet_decoder_options *options);
    void pollForInput(void);
    quiet_decoder* decoder;
    std::vector<unsigned char> recvBuffer;
    ofSoundBuffer localBuf;
    ssize_t recvSize = 0;
};
