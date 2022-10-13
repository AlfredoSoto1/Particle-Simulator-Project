
#ifndef BUTTON_HEADER
#define BUTTON_HEADER
#include <string>
#include "GUIcomponent.h"

class Button : public GUIcomponent {
public:

    Button();

    void draw() override;
    void update() override;

    void setListeners(void(*pressed)(), void(*clicked)());
    
    void changeTextString(const std::string& text);
    void setText(const std::string& text, const ofColor& color, int xRel, int yRel);

    void toggleLock();

private:

    bool isClicked = false;
    bool isPressed = false;
    bool isHovered = false;
    bool isLocked = false;

    int xRel;
    int yRel;
    std::string text;

    ofColor textColor;

    void(*pressed)();
    void(*clicked)();
};

#endif