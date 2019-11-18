#pragma once

#include "quiet.h"
#include "ofSoundBuffer.h"
#include "ofEvent.h"
#include "quiet/decoder.h"
#include <vector>
#include <string>

class ofxQuietDecoder {
public:
    void setup(const char *profile);
    size_t readBuffer(ofSoundBuffer & buf);
    size_t readBufferChannel(ofSoundBuffer &buf, size_t channel);
    ofEvent<size_t> onMessage;
    std::string consumeMessage();
    bool hasData();
private:
    void pollForInput(void);
    quiet_decoder* decoder;
    std::vector<unsigned char> recvBuffer;
    ofSoundBuffer localBuf;
    ssize_t recvSize = 0;
};
