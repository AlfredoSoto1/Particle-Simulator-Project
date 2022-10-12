#ifndef RECORDER_HEADER
#define RECORDER_HEADER

#include <vector>

class Recorder {
public:
    Recorder();
    ~Recorder();

    bool isRecording();
    bool isOnReplay();
    
    int getRecordedKey(int index);
    int getRecordedKeysCount();
    int getCurrentPlayBackKey();

    void startRecording();
    void stopRecording();
    
    void addUsableKeys(unsigned int length, int* keys);
    void record(int key);
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

    unsigned int lapsePerType;
    unsigned int replaySpeed;
    unsigned int lapsePerRecordedKey;
    unsigned int nextFrame;

    struct RecordedKey {
        int key;
        unsigned int lapse;
    };

    std::vector<RecordedKey> recordedkeys;
};

#endif