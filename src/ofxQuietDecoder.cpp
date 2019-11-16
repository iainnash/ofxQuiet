#include "ofxQuietDecoder.h"

void ofxQuietDecoder::setup(const char *profileName) {
    quiet_decoder_options* options = quiet_decoder_profile_filename("/usr/local/share/quiet/quiet-profiles.json", profileName);
    localBuf.allocate(512, 1);
    recvBuffer.resize(4096);
    decoder = quiet_decoder_create(options, 44000);
    quiet_decoder_set_nonblocking(decoder);
    recvSize = 0;
}

void ofxQuietDecoder::pollForInput() {
    if (decoder == NULL) {
        return;
    }
    if (recvSize > 0) {
        return;
    }
    recvSize = quiet_decoder_recv(decoder, recvBuffer.data(), recvBuffer.capacity());
    if (recvSize > 0) {
        size_t recvSizePos = recvSize;
        onMessage.notify(recvSizePos);
    }
}

std::string ofxQuietDecoder::consumeMessage() {
    std::string str;
    str += (char *)recvBuffer.data();
    recvBuffer.clear();
    recvSize = 0;
    return str;
}

size_t ofxQuietDecoder::readBuffer(ofSoundBuffer &buf) {
    size_t len = quiet_decoder_consume(decoder, buf.getBuffer().data(), buf.getNumFrames());
    pollForInput();
    return len;
}

size_t ofxQuietDecoder::readBufferChannel(ofSoundBuffer &buf, size_t channel) {
    localBuf.setChannel(buf, channel);
    size_t len = quiet_decoder_consume(decoder, localBuf.getBuffer().data(), localBuf.getNumFrames());
    pollForInput();
    return len;
}

