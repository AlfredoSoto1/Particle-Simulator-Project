#ifndef _MAGNIFIER_DEFINED
#define _MAGNIFIER_DEFINED

#include "ofMain.h"

class Magnifier {
    public:
    
    

    private:

    glm::vec2 position;
    glm::vec2 scale;

    float boundingBoxThickness;

    glm::vec3 boundingBoxColor;
};

#endif