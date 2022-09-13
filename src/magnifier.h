#ifndef _MAGNIFIER_DEFINED
#define _MAGNIFIER_DEFINED

#include "ofMain.h"

class Magnifier {
    public:

    Magnifier();
    ~Magnifier();
    
    glm::ivec2& getPosition();
    glm::ivec2& getInitialPosition();
    glm::ivec2& getLastPosition();

    void setup();
    void draw();
    void update();

    void loadLastParameters(const int& x, const int& y, const int& button);
    void loadInitialParameters(const int& x, const int& y, const int& button);

    private:

    bool isGettingLastParametersFlag;
    bool isGettingInitialParametersFlag;

    glm::ivec2 lastPosition;
    glm::ivec2 initialPosition;

    glm::ivec2 position;
    glm::ivec2 scale;

    float boundingBoxThickness;

    glm::vec3 boundingBoxColor;
};

#endif