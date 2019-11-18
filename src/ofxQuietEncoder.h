#pragma once

#include "quiet.h"
#include "ofSoundBuffer.h"
#include "quiet/encoder.h"
#include <string>

class ofxQuietEncoder {
public:
    void setup(const char *profile);
    void setup(const char *profileName, const char *profilePath);
    size_t addText(char *text, size_t size);
    size_t addText(std::string text);
    size_t writeBuffer(ofSoundBuffer & buf);
    size_t writeBufferChannel(ofSoundBuffer &buf, size_t channel);
private:
    void setupWithOptions(quiet_encoder_options *options);
    quiet_encoder* encoder;
    ofSoundBuffer localBuf;
};
