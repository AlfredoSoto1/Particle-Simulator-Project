#ifndef RECORDER_HEADER
#define RECORDER_HEADER

#include <vector>

struct RecordedKey {
    int key;
    unsigned int lapse;
};
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

    void togglePlayingPlayList();
    void playNext();
    void playPrev();
    void save();

    void draw();
    void update();

private:

    bool _isPaused = false;
    bool _isRecording = false;
    bool _isReplaying = false;
    bool _isReplayingPlayList = false;

    unsigned int lapsePerType;
    unsigned int replaySpeed;
    unsigned int lapsePerRecordedKey;
    unsigned int nextFrame;

    std::vector<RecordedKey>* recordedkeys;
    std::vector<std::vector<RecordedKey>*> playList;
};

#endif