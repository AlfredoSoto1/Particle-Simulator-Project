#ifndef _MAGNIFIER_DEFINED
#define _MAGNIFIER_DEFINED

#include "ofMain.h"
#include "Particle.h"

class Magnifier
{
public:
    Magnifier();
    ~Magnifier();

    glm::ivec2 &getScale();
    glm::ivec2 &getPosition();

    void toggleOnSelect();

    void draw();
    void update();
    void reset(const int &button);

    void loadDraggedPosition(const int &x, const int &y);
    void loadInitialPosition(const int &x, const int &y, const int &button);

    void magnifyParticle(Particle *particle);

private:
    bool onSelect;
    bool holdClick;

    int currentButtonClicked;
    float boundingBoxThickness;

    glm::ivec2 scale;
    glm::ivec2 lastPosition;
    glm::ivec2 initialPosition;

    ofColor boundingBoxColor;
};

#endif