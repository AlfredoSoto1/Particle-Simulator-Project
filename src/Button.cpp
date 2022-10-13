#include "Button.h"
#include <string>

Button::Button() {
    this->pressed = nullptr;
    this->clicked = nullptr;

    this->text = "Click me";
    this->xpos = 0;
    this->ypos = 0;
    this->width = 100;
    this->height = 50;
    this->xRel = 0;
    this->yRel = 0;

    textColor = ofColor::white;
}

void Button::setListeners(void(*pressed)(), void(*clicked)()) {
    this->pressed = pressed;
    this->clicked = clicked;
 }

 void Button::setText(const std::string& text, const ofColor& color, int xRel, int yRel) {
    this->text = text;
    this->xRel = xRel;
    this->yRel = yRel;
    this->textColor = color;
 }

void Button::changeTextString(const std::string& text) {
    this->text = text;
 }

void Button::toggleLock() {
    isLocked = !isLocked;
}

void Button::draw() {

    if(isLocked) {
        glm::vec3 dim = color * 0.65;
        ofSetColor(dim.r, dim.g, dim.b);
    } else if(isPressed && isHovered) {
        glm::vec3 dim = color * 0.75;
        ofSetColor(dim.r, dim.g, dim.b);
    } else {
        ofSetColor(color.r, color.g, color.b);
    }
    ofDrawRectangle(xpos, ypos, width, height);

    ofSetColor(textColor);
    ofDrawBitmapString(text, xpos + xRel, ypos + yRel);
}

void Button::update() {

    if(isLocked)
        return;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        if(!isClicked) {
            bool inArea = isInArea(ofGetMouseX(), ofGetMouseY());
            isHovered = inArea;
            if(inArea)
                if(clicked != nullptr)
                    clicked();
            isClicked = true;
        } else {
            if(pressed != nullptr)
                pressed();
            isPressed = true;
        }
    }else {
        isClicked = false;
        isPressed = false;
        isHovered = false;
    }

}