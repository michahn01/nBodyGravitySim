#include "Button.h"
#include <iostream>

Button::Button() {}
Button::Button(int x, int y, int w, int h, std::string ID) :
Object(x, y, w, h, ID)
{}
void Button::draw() {
    Object::texture_handler->drawFrame(texture_ID, pos.getX(), pos.getY(), width, height, 0, 0, width, height, 0, current_frame, renderer);
}
void Button::update() {
    Vector2D pMousePos = Object::input_handler->getMousePosition();
    if (current_frame == CLICKED) {
        if (!Object::input_handler->getMouseButtonState(LEFT)) clickBehavior();
    }
    if (pMousePos.getX() < (pos.getX() + width)
        && pMousePos.getX() > pos.getX()
        && pMousePos.getY() < (pos.getY() + height)
        && pMousePos.getY() > pos.getY()) {
        if (Object::input_handler->getMouseButtonState(LEFT)) {
            current_frame = CLICKED;
        }
        else {
            current_frame = MOUSE_OVER;
        }
    }
    else {
        current_frame = MOUSE_OUT;
    }
}
void Button::clean() {
}

void Button::clickBehavior() {
    
}