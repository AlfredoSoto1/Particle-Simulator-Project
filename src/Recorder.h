#ifndef RECORDER_HEADER
#define RECORDER_HEADER

#include <vector>

class Recorder {
public:
    Recorder();
    ~Recorder();

    bool isRecording();
    
    int getRecordedKeysCount();

    void startRecording();
    void stopRecording();
    
    void addUsableKeys(unsigned int length, int* keys);
    void record(int key);
    void pause();
    void dispose();
    void replay(int gameTick);

    void draw();
    void update();
private:

    bool _isPaused = false;
    bool _isRecording = false;
    bool _isDisposed = false;

    int lapsePerType;

    struct RecordedKey {
        int key;
        int lapse;
    };

    vector<RecordedKey> recordedkeys;
};

#endif