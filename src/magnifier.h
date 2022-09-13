#ifndef _MAGNIFIER_DEFINED
#define _MAGNIFIER_DEFINED

#include "ofMain.h"

class Magnifier {
    public:

    Magnifier();
    ~Magnifier();
    
    glm::ivec2& getScale();
    glm::ivec2& getPosition();

    void setup();
    void draw();
    void update();

    void loadDynamicPosition(const int& x, const int& y);
    void loadInitialPosition(const int& x, const int& y, const int& button);
    void loadFinalPosition(const int& x, const int& y, const int& button);

    private:

    bool isGettingLastParametersFlag;
    bool isGettingInitialParametersFlag;

    int boundingBoxThickness;

    glm::ivec2 scale;
    glm::ivec2 position;
    glm::ivec2 lastPosition;
    glm::ivec2 initialPosition;

    glm::ivec3 boundingBoxColor;

};

#endif