#ifndef RECORDER_HEADER
#define RECORDER_HEADER

#include <vector>
#include "ofMain.h"

class Recorder
{
public:
    Recorder();
    ~Recorder();

    bool isRecording();
    bool isOnReplay();

    int getRecordedKeysCount();
    int getCurrentPlayBackKey();
    void freeCurrentPlayBackKey();
    ofColor getCurrentPlayBackColor();

    void startRecording();
    void stopRecording();

    void addUsableKeys(unsigned int length, int *keys);
    void record(int key, ofColor color);
    void resume();
    void pause();
    void replay();
    void endReplay();
    void dispose();

    void draw();
    void update();


private:
    bool _isPaused = false;
    bool _isRecording = false;
    bool _isReplaying = false;
    bool _playBackKeyShown = false;

    unsigned int lapsePerType;
    unsigned int replaySpeed;
    unsigned int lapsePerRecordedKey;
    unsigned int nextFrame;

    struct RecordedKey {
        int key;
        ofColor color;
        unsigned int lapse;
    };

    std::vector<RecordedKey> recordedkeys;
};

#endif