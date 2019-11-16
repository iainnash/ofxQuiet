#include "ofxQuietEncoder.h"

void ofxQuietEncoder::setup(const char *profileName) {
    quiet_encoder_options* options = quiet_encoder_profile_filename("/usr/local/share/quiet/quiet-profiles.json", profileName);
    options->frame_len = 512;
    localBuf.allocate(512, 1);
    encoder = quiet_encoder_create(options, 44000);
    quiet_encoder_set_blocking(encoder, 0, 10000);
}

size_t ofxQuietEncoder::writeBuffer(float *buf, size_t size) {
    return quiet_encoder_emit(encoder, buf, size);
}

size_t ofxQuietEncoder::writeBuffer(ofSoundBuffer &buf) {
    quiet_encoder_emit(encoder, buf.getBuffer().data(), buf.getNumFrames());
}

size_t ofxQuietEncoder::writeBufferChannel(ofSoundBuffer &buf, size_t channel) {
    size_t written = quiet_encoder_emit(encoder, localBuf.getBuffer().data(), buf.getNumFrames());
    buf.setChannel(localBuf, channel);
    return written;
}

size_t ofxQuietEncoder::addText(char *text, size_t size) {
    return quiet_encoder_send(encoder, text, size);
}

size_t ofxQuietEncoder::addText(std::string text) {
    return quiet_encoder_send(encoder, text.c_str(), text.size());
}
