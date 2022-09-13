#include "magnifier.h"

Magnifier::Magnifier() {
    isGettingLastParametersFlag = false;
    isGettingInitialParametersFlag = false;
}

Magnifier::~Magnifier() {
    
}

glm::ivec2& Magnifier::getPosition() {
    return this->position;
}

glm::ivec2& Magnifier::getInitialPosition() {
    return this->initialPosition;
}

glm::ivec2& Magnifier::getLastPosition() {
    return this->lastPosition;
}

void Magnifier::setup() {

}

void Magnifier::loadInitialParameters(const int& x, const int& y, const int& button) {
    if(button == OF_MOUSE_BUTTON_1) {
        if(isGettingInitialParametersFlag) {
            initialPosition.x = x;
            initialPosition.y = y;
            isGettingInitialParametersFlag = false;
        }
    }else {
        isGettingInitialParametersFlag = true;
    }
}

void Magnifier::loadLastParameters(const int& x, const int& y, const int& button) {
    if(button == OF_MOUSE_BUTTON_1) {
        if(isGettingLastParametersFlag) {
            lastPosition.x = x;
            lastPosition.y = y;
            isGettingLastParametersFlag= false;
        }
    }else {
        isGettingLastParametersFlag = true;
    }
}

void Magnifier::draw() {
    
}

void Magnifier::update() {
    
}

