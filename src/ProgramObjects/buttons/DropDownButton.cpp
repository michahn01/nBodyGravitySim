#include "DropDownButton.h"

DropDownButton::DropDownButton(int x, int y, int w, int h, std::string ID, bool& dropped) :
Button(x, y, w, h, ID), dropped_down(dropped) {
    current_frame = MOUSE_OUT; // start at frame 0
    dropped_down = false;
}

DropDownButton::~DropDownButton() {
    while (!drop_downs.empty()) {
        delete drop_downs.back(); 
        drop_downs.pop_back();
    }
}
void DropDownButton::draw() {
    Object::texture_handler->drawFrame(texture_ID, pos.getX(), pos.getY(), width, height, 0, 0, width, height, 0, current_frame, Button::renderer);
    if (dropped_down) {
        for (int i = 0; i < drop_downs.size(); ++i) {
            drop_downs[i]->draw();
        }
    }
}
void DropDownButton::update() {
    Vector2D pMousePos = Object::input_handler->getMousePosition();
    if (Object::input_handler->getState() != old_state) {
        current_frame = MOUSE_OUT;
        dropped_down = false;
    }
    old_state = Object::input_handler->getState();
    if (dropped_down) {
        if (current_frame == CLICKED_DROPPED) {
            if (!Object::input_handler->getMouseButtonState(LEFT)) {
                current_frame = MOUSE_OVER;
                dropped_down = false;
            }
        }
        else if (pMousePos.getX() < (pos.getX() + width)
                 && pMousePos.getX() > pos.getX()
                 && pMousePos.getY() < (pos.getY() + height)
                 && pMousePos.getY() > pos.getY()) {
                if (Object::input_handler->getMouseButtonState(LEFT)) {
                    current_frame = CLICKED_DROPPED;
                }
                else {
                    current_frame = MOUSE_OVER_DROPPED;
                }
            }
        else {
            current_frame = MOUSE_OUT_DROPPED;
        }
    }
    else {
        if (current_frame == CLICKED) {
            if (!Object::input_handler->getMouseButtonState(LEFT)) {
                current_frame = MOUSE_OVER_DROPPED;
                dropped_down = true;
            }
        }
        else if (pMousePos.getX() < (pos.getX() + width)
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

    if (dropped_down) {
        for (int i = 0; i < drop_downs.size(); ++i) {
            drop_downs[i]->update();
        }
    }
}
void DropDownButton::clean() {
}

void DropDownButton::clickBehavior() {
    dropped_down = true;
}