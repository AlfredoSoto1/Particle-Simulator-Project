#include "magnifier.h"

Magnifier::Magnifier() {
    holdClick = false;

    scale.x = 0;
    scale.y = 0;

    boundingBoxThickness = 5.0f;

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

void Magnifier::reset(const int& button) {
    if(button == OF_MOUSE_BUTTON_LEFT) {
        holdClick = false;
        prefferedMouseToDrag = button;
    }
}

void Magnifier::loadDraggedPosition(const int& x, const int& y) {
    this->lastPosition.x = x;
    this->lastPosition.y = y;
}

void Magnifier::loadInitialPosition(const int& x, const int& y, const int& button) {
    if(button == OF_MOUSE_BUTTON_LEFT) {
        if(!holdClick) {
            initialPosition.x = x;
            initialPosition.y = y;
            lastPosition.x = x;
            lastPosition.y = y;
            prefferedMouseToDrag = button;
            holdClick = true;
        }
    }
}

void Magnifier::draw() {
    
    ofSetColor(boundingBoxColor.r, boundingBoxColor.g, boundingBoxColor.b);

    ofNoFill();
    ofSetLineWidth(boundingBoxThickness);
    ofDrawRectangle(initialPosition.x, initialPosition.y, scale.x, scale.y);
    ofFill();
}

void Magnifier::update() {
    if(holdClick) {
        if(prefferedMouseToDrag == OF_MOUSE_BUTTON_LEFT) {
            scale.x = lastPosition.x - initialPosition.x;
            scale.y = lastPosition.y - initialPosition.y;
        }
    }
}

