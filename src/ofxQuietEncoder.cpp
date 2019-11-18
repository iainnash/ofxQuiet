#include "ofxQuietEncoder.h"

#include "quietProfileData.h"

void ofxQuietEncoder::setup(const char *profileName) {
    quiet_encoder_options* options = quiet_encoder_profile_str(
        _usr_local_share_quiet_quiet_profiles_json,
        profileName
    );
    setupWithOptions(options);
}

void ofxQuietEncoder::setup(const char *profileName, const char *profilePath) {
    quiet_encoder_options* options = quiet_encoder_profile_filename(profilePath, profileName);
    setupWithOptions(options);
}

void ofxQuietEncoder::setupWithOptions(quiet_encoder_options *options) {
    // default guess for 512 frames in a channel, will resize later
    options->frame_len = 512;
    localBuf.allocate(512, 1);
    encoder = quiet_encoder_create(options, 44100);
    quiet_encoder_set_blocking(encoder, 0, 10000);
}

size_t ofxQuietEncoder::writeBuffer(ofSoundBuffer &buf) {
    quiet_encoder_emit(encoder, buf.getBuffer().data(), buf.getNumFrames());
}

size_t ofxQuietEncoder::writeBufferChannel(ofSoundBuffer &buf, size_t channel) {
    size_t samplesToWrite = buf.getNumFrames();
    // if sample rate doesn't match, resize dynamically
    if (samplesToWrite < localBuf.size()) {
        localBuf.resize(samplesToWrite);
    }
    ssize_t written = quiet_encoder_emit(encoder, localBuf.getBuffer().data(), samplesToWrite);
    if (written != samplesToWrite) {
        return 0;
    }
    size_t at;
    for (at = 0; at < samplesToWrite; at++) {
        buf.getSample(at, channel) = localBuf[at];
    }
    return at;
}

size_t ofxQuietEncoder::addText(char *text, size_t size) {
    return quiet_encoder_send(encoder, text, size);
}

size_t ofxQuietEncoder::addText(std::string text) {
    return quiet_encoder_send(encoder, text.c_str(), text.size());
}
