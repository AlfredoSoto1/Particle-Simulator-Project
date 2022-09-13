#include "magnifier.h"

Magnifier::Magnifier() {
    isGettingLastParametersFlag = false;
    isGettingInitialParametersFlag = false;

    //initial box color
    boundingBoxColor.r = 255;
    boundingBoxColor.g = 0;
    boundingBoxColor.b = 0;
}

Magnifier::~Magnifier() {
    
}

glm::ivec2& Magnifier::getPosition() {
    return this->initialPosition;
}

glm::ivec2& Magnifier::getScale() {
    return this->scale;
}

void Magnifier::setup() {

}

void Magnifier::loadDynamicPosition(const int& x, const int& y) {
    this->position.x = x;
    this->position.y = y;
}

void Magnifier::loadInitialPosition(const int& x, const int& y, const int& button) {
    isGettingLastParametersFlag = true;
    if(button == OF_MOUSE_BUTTON_LEFT) {
        if(isGettingInitialParametersFlag) {
            initialPosition.x = x;
            initialPosition.y = y;
            isGettingInitialParametersFlag = false;
        }
    }
}

void Magnifier::loadFinalPosition(const int& x, const int& y, const int& button) {
    isGettingInitialParametersFlag = true;

    if(button == OF_MOUSE_BUTTON_LEFT) {
        if(isGettingLastParametersFlag) {
            lastPosition.x = x;
            lastPosition.y = y;
            isGettingLastParametersFlag= false;
        }
    }
}

void Magnifier::draw() {
    
    ofSetColor(boundingBoxColor.r, boundingBoxColor.g, boundingBoxColor.b);

    float scaleX = position.x - initialPosition.x;
    float scaleY = position.y - initialPosition.y;

    ofDrawRectangle((float)initialPosition.x, (float)initialPosition.y, scaleX, scaleY);
}

void Magnifier::update() {
    
}

