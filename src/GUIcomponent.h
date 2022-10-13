#ifndef GUI_HEADER
#define GUI_HEADER

#include "ofMain.h"

class GUIcomponent {
public:

    virtual void draw();
    virtual void update();

    void setPosition(int x, int y);
    void setDimensions(int width, int height);
    void setColor(ofColor color);
    void setColor(glm::vec3 color);

protected:

    bool isInArea(int x, int y);

    int xpos;
    int ypos;
    int width;
    int height;

    glm::vec3 color;
};

#endif