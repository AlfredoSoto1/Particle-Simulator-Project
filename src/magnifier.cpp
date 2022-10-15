#include "magnifier.h"

Magnifier::Magnifier()
{
    onSelect = false;
    holdClick = false;

    scale.x = 0;
    scale.y = 0;

    boundingBoxThickness = 5.0f;

    // initial box color
    boundingBoxColor.set(255, 255, 255);
}

Magnifier::~Magnifier()
{
}

void Magnifier::toggleOnSelect()
{
    this->onSelect = !onSelect;
}

glm::ivec2 &Magnifier::getPosition()
{
    return this->initialPosition;
}

glm::ivec2 &Magnifier::getScale()
{
    return this->scale;
}

void Magnifier::reset(const int &button)
{
    if (button == OF_MOUSE_BUTTON_LEFT)
    {
        holdClick = false;
    }
    currentButtonClicked = button;
}

void Magnifier::loadDraggedPosition(const int &x, const int &y)
{

    bool xMouseInBoundry = (x > initialPosition.x && x < initialPosition.x + scale.x) || (x < initialPosition.x && x > initialPosition.x + scale.x);
    bool yMouseInBoundry = (y > initialPosition.y && y < initialPosition.y + scale.y) || (y < initialPosition.y && y > initialPosition.y + scale.y);
    if (onSelect && currentButtonClicked == OF_MOUSE_BUTTON_LEFT && xMouseInBoundry && yMouseInBoundry)
    {
        initialPosition.x = x - scale.x / 2;
        initialPosition.y = y - scale.y / 2;
        this->lastPosition.x = initialPosition.x + scale.x;
        this->lastPosition.y = initialPosition.y + scale.y;
        return;
    }
    if (currentButtonClicked == OF_MOUSE_BUTTON_LEFT)
    {
        this->lastPosition.x = x;
        this->lastPosition.y = y;
    }
}

void Magnifier::loadInitialPosition(const int &x, const int &y, const int &button)
{
    currentButtonClicked = button;

    if (onSelect)
        return;
    if (currentButtonClicked == OF_MOUSE_BUTTON_LEFT)
    {
        if (!holdClick)
        {
            initialPosition.x = x;
            initialPosition.y = y;
            lastPosition.x = x;
            lastPosition.y = y;
            holdClick = true;
        }
    }

    bool xPossibleBoundries = (x > initialPosition.x && x < lastPosition.x) || (x < initialPosition.x && x > lastPosition.x);
    bool yPossibleBoundries = (y > initialPosition.y && y < lastPosition.y) || (y < initialPosition.y && y > lastPosition.y);

    if (xPossibleBoundries && yPossibleBoundries)
    {

        if (currentButtonClicked == OF_MOUSE_BUTTON_RIGHT)
        {
            initialPosition.x = 0;
            initialPosition.y = 0;
            lastPosition.x = 0;
            lastPosition.y = 0;
            scale.x = 0;
            scale.y = 0;
        }
    }
}

void Magnifier::magnifyParticle(Particle *particle)
{

    glm::vec3 &pos = particle->pos;

    bool xPossibleBoundries = (pos.x > initialPosition.x && pos.x < lastPosition.x) || (pos.x < initialPosition.x && pos.x > lastPosition.x);
    bool yPossibleBoundries = (pos.y > initialPosition.y && pos.y < lastPosition.y) || (pos.y < initialPosition.y && pos.y > lastPosition.y);

    if (xPossibleBoundries && yPossibleBoundries)
    {
        particle->magnifyingfactor = 3.0;
    }
    else
    {
        particle->magnifyingfactor = 1.0;
    }
}

void Magnifier::draw()
{

    ofSetColor(boundingBoxColor);

    ofNoFill();
    ofSetLineWidth(boundingBoxThickness);
    ofDrawRectangle(initialPosition.x, initialPosition.y, scale.x, scale.y);
    ofFill();
}

void Magnifier::update()
{

    if (onSelect)
        return;
    if (holdClick)
    {
        if (currentButtonClicked == OF_MOUSE_BUTTON_LEFT)
        {
            scale.x = lastPosition.x - initialPosition.x;
            scale.y = lastPosition.y - initialPosition.y;
        }
    }
}