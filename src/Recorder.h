#ifndef RECORDER_HEADER
#define RECORDER_HEADER

class Recorder {

public:

    Recorder();
    ~Recorder();

    void record();
    void pause();
    void dispose();
    void replay(int gameTick);

private:



};

#endif