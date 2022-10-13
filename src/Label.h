#ifndef LABEL_HEADER
#define LABEL_HEADER
#include <string>
#include "GUIcomponent.h"

class Label : public GUIcomponent {
public:

    Label();

    void draw() override;
    void update() override;

private:
    std::string text;
};

#endif