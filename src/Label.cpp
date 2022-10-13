#include "Label.h"

Label::Label() {
   
}

void Label::update() {

}

void Label::draw() {
    ofSetColor(color.x, color.y, color.z);
    ofDrawBitmapString(text, xpos, ypos);
}