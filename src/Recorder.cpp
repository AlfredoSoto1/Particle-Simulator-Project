#include <Recorder.h>
#include "ofApp.h"

Recorder::Recorder()
{
    lapsePerType = 0;
    replaySpeed = 1;
    lapsePerRecordedKey = 0;
    nextFrame = 0;

}

Recorder::~Recorder()
{
    dispose();
}

bool Recorder::isRecording()
{
    return _isRecording;
}

bool Recorder::isOnReplay()
{
    return _isReplaying;
}

int Recorder::getRecordedKey(int index)
{
    return recordedkeys[index].key;
}

int Recorder::getRecordedKeysCount()
{
    return recordedkeys.size();
}

int Recorder::getCurrentPlayBackKey()
{
    if (recordedkeys.size() == 0 || !_isReplaying)
        return -1;
    if(_playBackKeyShown)
        return -1;
    return recordedkeys[nextFrame].key;
}

void Recorder::freeCurrentPlayBackKey() {
    _playBackKeyShown = true;
}

void Recorder::draw()
{

    if (!_isRecording && !_isReplaying)
        return;

    ofSetColor(ofColor::red);
    ofDrawCircle(ofGetWidth() - 200, 15, 21);

    ofSetColor(ofColor::white);

    if (_isRecording)
    {
        string rec = _isRecording ? "true" : "false";
        ofDrawBitmapString("\n\nIs Recording: " + rec, ofGetWidth() - 200, 15);
    }

    if (_isReplaying)
    {
        string rep = _isReplaying ? "true" : "false";
        ofDrawBitmapString("\n\nIs Replaying: " + rep, ofGetWidth() - 200, 30);
    }
}

void Recorder::update()
{

    if (_isReplaying)
    {

        if (nextFrame >= recordedkeys.size())
        {
            endReplay();
            return;
        }

        unsigned int actionLapse = recordedkeys[nextFrame].lapse;
        if (lapsePerRecordedKey >= actionLapse)
        {
            lapsePerRecordedKey = 0;
            nextFrame++;
            _playBackKeyShown = false;
        }
        else
        {
            if (!_isPaused)
            {
                lapsePerRecordedKey += replaySpeed;
            }
        }
    }

    if (!_isRecording)
        return;
    lapsePerType++;
}

void Recorder::record(int key)
{
    if (!_isRecording)
        return;
    if (_isReplaying)
        return;
    recordedkeys.push_back({key, lapsePerType});
    lapsePerType = 0;
}

void Recorder::startRecording()
{
    if (_isReplaying)
        return;
    if (_isRecording)
        return;
    _isRecording = true;
    lapsePerType = 0;
}

void Recorder::stopRecording()
{
    if (_isReplaying)
        return;
    if (!_isRecording)
        return;
    _isRecording = false;
    lapsePerType = 0;
}

void Recorder::pause()
{
    if (_isPaused)
        return;
    _isPaused = true;
}

void Recorder::resume()
{
    if (!_isPaused)
        return;
    _isPaused = false;
}

void Recorder::dispose()
{
    if (_isRecording)
        return;
    recordedkeys.clear();
}

void Recorder::endReplay()
{
    if (!_isReplaying)
        return;
    _isReplaying = false;
    nextFrame = 0;
    lapsePerRecordedKey = 0;
}

void Recorder::replay()
{
    if (_isRecording && !_isReplaying)
        return;
    _isReplaying = true;
}
