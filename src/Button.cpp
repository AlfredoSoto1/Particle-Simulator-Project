#include "Button.h"
#include <string>

int Button::LEFT = 0;
int Button::CENTERED = 1;

Button::Button() {
    alignment = CENTERED;
}

void Button::setListeners(void(*pressed)(), void(*clicked)()) {
    this->pressed = pressed;
    this->clicked = clicked;
 }

 void Button::setText(const std::string& text, int alignment) {
    this->text = text;
    this->alignment = alignment;
 }

void Button::draw() {

    if(alignment == CENTERED) {
        ofSetColor(ofColor::white);
        int centeredX = xpos + width / 2 - text.length() * 2;
	    ofDrawBitmapString(text, centeredX, ypos);
    }

    if(isPressed && isHovered) {
        glm::vec3 dim = color * 0.75;
        ofSetColor(dim.r, dim.g, dim.b);
    }else {
        ofSetColor(color.r, color.g, color.b);
    }
    ofDrawRectangle(xpos, ypos, width, height);
}

void Button::update() {

    if(ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        if(!isClicked) {
            bool inArea = isInArea(ofGetMouseX(), ofGetMouseY());
            isHovered = inArea;
            if(inArea)
                clicked();
            isClicked = true;
        } else {
            pressed();
            isPressed = true;
        }
    }else {
        isClicked = false;
        isPressed = false;
        isHovered = false;
    }

}