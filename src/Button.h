
#ifndef BUTTON_HEADER
#define BUTTON_HEADER
#include <string>
#include "GUIcomponent.h"

class Button : public GUIcomponent {
public:

    static int LEFT;
    static int CENTERED;

    Button();

    void draw() override;
    void update() override;

    void setListeners(void(*pressed)(), void(*clicked)());
    void setText(const std::string& text, int alignment);

private:

    bool isClicked = false;
    bool isPressed = false;
    bool isHovered = false;

    int alignment;
    std::string text;

    void(*pressed)();
    void(*clicked)();
};

#endif