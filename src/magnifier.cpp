#include "magnifier.h"

Magnifier::Magnifier() {
    isGettingLastParametersFlag = false;
    isGettingInitialParametersFlag = false;
}

Magnifier::~Magnifier() {
    
}

void Magnifier::setup() {

}

void Magnifier::loadInitialParameters(const int& x, const int& y, const int& button) {
    if(button == OF_MOUSE_BUTTON_1) {
        if(isGettingInitialParametersFlag) {
            mousePosition.x = x;
            mousePosition.y = y;
            isGettingInitialParametersFlag = false;
        }
    }else {
        isGettingInitialParametersFlag = true;
    }
}

void Magnifier::loadLastParameters(const int& x, const int& y, const int& button) {
    if(button == OF_MOUSE_BUTTON_1) {
        if(isGettingLastParametersFlag) {
            mousePosition.x = x;
            mousePosition.y = y;
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

