#include "GUIcomponent.h"

void GUIcomponent::draw() {

}

void GUIcomponent::update() {

}

bool GUIcomponent::isInArea(int x, int y) {
    return (x >= xpos && x <= xpos + width) && (y >= ypos && y <= ypos + height);
}

void GUIcomponent::setPosition(int x, int y) {
    xpos = x;
    ypos = y;
}

void GUIcomponent::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void GUIcomponent::setColor(ofColor color) {
   setColor(glm::vec3(color.r,color.g, color.b));
}

void GUIcomponent::setColor(glm::vec3 color) {
    this->color = color;
}
