#include <Recorder.h>

Recorder::Recorder() {
    lapsePerType = 0;
    replaySpeed = 1;
    lapsePerRecordedKey = 0;
    nextFrame = 0;

}

Recorder::~Recorder() {
    dispose();
}

bool Recorder::isRecording() {
    return _isRecording;
}

bool Recorder::isOnReplay() {
    return _isReplaying;
}

int Recorder::getRecordedKeysCount() {
    return recordedkeys.size();
}

ofColor Recorder::getCurrentPlayBackColor() {
    if (recordedkeys.size() == 0 || !_isReplaying)
        return ofColor::black;
    if(_playBackKeyShown)
        return ofColor::black;
    return recordedkeys[nextFrame].color;
}

int Recorder::getCurrentPlayBackKey() {
    if (recordedkeys.size() == 0 || !_isReplaying)
        return -1;
    if(_playBackKeyShown)
        return -1;
    return recordedkeys[nextFrame].key;
}

void Recorder::freeCurrentPlayBackKey() {
    _playBackKeyShown = true;
}

void Recorder::draw() {

    if (!_isRecording && !_isReplaying)
        return;

    if (_isRecording) {
        ofSetColor(ofColor::red);
        ofDrawCircle(ofGetWidth() - 15, 15, 15);
        string rec = _isRecording ? "true" : "false";
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Is Recording:\n" + rec, ofGetWidth() - 150, 30);
    }
    if (_isReplaying) {
        ofSetColor(ofColor::green);
        ofDrawCircle(ofGetWidth() - 15, 15, 15);
        string rep = _isReplaying ? "true" : "false";
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Is Replaying:\n" + rep, ofGetWidth() - 150, 30);
    }
}

void Recorder::update() {

    if (_isReplaying) {
        if (nextFrame >= recordedkeys.size()) {
            endReplay();
            return;
        }

        unsigned int actionLapse = recordedkeys[nextFrame].lapse;
        if (lapsePerRecordedKey >= actionLapse) {
            lapsePerRecordedKey = 0;
            nextFrame++;
            _playBackKeyShown = false;
        } else {
            if (!_isPaused)
                lapsePerRecordedKey += replaySpeed;
        }
    }

    if (!_isRecording)
        return;
    lapsePerType++;
}

void Recorder::record(int key, ofColor color) {
    if (!_isRecording)
        return;
    if (_isReplaying)
        return;
    recordedkeys.push_back({key, color, lapsePerType});
    lapsePerType = 0;
}

void Recorder::startRecording() {
    if (_isReplaying)
        return;
    if (_isRecording)
        return;
    _isRecording = true;
    lapsePerType = 0;
}

void Recorder::stopRecording() {
    if (_isReplaying)
        return;
    if (!_isRecording)
        return;
    _isRecording = false;
    lapsePerType = 0;
}

void Recorder::pause() {
    if (_isPaused)
        return;
    _isPaused = true;
}

void Recorder::resume() {
    if (!_isPaused)
        return;
    _isPaused = false;
}

void Recorder::dispose() {
    if (_isRecording)
        return;
    recordedkeys.clear();
}

void Recorder::endReplay() {
    if (!_isReplaying)
        return;
    _isReplaying = false;
    nextFrame = 0;
    lapsePerRecordedKey = 0;
}

void Recorder::replay() {
    if (_isRecording && !_isReplaying)
        return;
    _isReplaying = true;
}
