#include <Recorder.h>
#include "ofApp.h"

Recorder::Recorder() {
    lapsePerType = 0;
}

Recorder::~Recorder() {

}

bool Recorder::isRecording() {
    return _isRecording;
}

int Recorder::getRecordedKey(int index) {
    return 0;//recordedkeys[index].key;
}

int Recorder::getRecordedKeysCount() {
    return 0;//recordedkeys.size();
}

void Recorder::draw() {

}

void Recorder::update() {
    if(!_isRecording)
        return;
    lapsePerType++;
}

void Recorder::record(int key) {
    if(!_isRecording)
        return;
    // recordedkeys.push_back({key, lapsePerType});
    lapsePerType = 0;
}

void Recorder::startRecording() {
    if(_isRecording)
        return;
    _isRecording = true;
    lapsePerType = 0;
}

void Recorder::stopRecording() {
    if(!_isRecording)
        return;
    _isRecording = false;
    lapsePerType = 0;
}

void Recorder::pause() {
    if(_isPaused)
        return;
}

void Recorder::dispose() {
    if(_isDisposed)
        return;
    
}

void Recorder::replay(int gameTick) {

}

