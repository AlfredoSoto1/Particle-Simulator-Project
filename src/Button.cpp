#include "Button.h"
#include <string>

int Button::LEFT = 0;
int Button::CENTERED = 1;

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
}

void Button::setListeners(void(*pressed)(), void(*clicked)()) {
    this->pressed = pressed;
    this->clicked = clicked;
 }

 void Button::setText(const std::string& text, int xRel, int yRel) {
    this->text = text;
    this->xRel = xRel;
    this->yRel = yRel;
 }

void Button::draw() {

    ofSetColor(ofColor::white);
    int centeredX = xpos + width / 2 - text.length() * 3;
    ofDrawBitmapString(text, centeredX, ypos);

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