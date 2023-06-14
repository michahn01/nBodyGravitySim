#include "Button.h"
#include <iostream>

Button::Button() {}
Button::Button(int x, int y, int w, int h, std::string ID) :
pos(x, y), vel(0, 0), acc(0, 0), width(w), height(h), texture_ID(ID) {
    current_frame = MOUSE_OUT; // start at frame 0
}
void Button::draw() {
    texture_handler->drawFrame(texture_ID, pos.getX(), pos.getY(), width, height, 0, 0, width, height, 0, current_frame, renderer);
}
void Button::update() {
    Vector2D pMousePos = input_handler->getMousePosition();
    if (current_frame == CLICKED) {
        if (!input_handler->getMouseButtonState(LEFT)) clickBehavior();
    }
    if (pMousePos.getX() < (pos.getX() + width)
        && pMousePos.getX() > pos.getX()
        && pMousePos.getY() < (pos.getY() + height)
        && pMousePos.getY() > pos.getY()) {
        if (input_handler->getMouseButtonState(LEFT)) {
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



SDL_Renderer* Button::renderer = nullptr;
TextureHandler* Button::texture_handler = nullptr;
InputHandler* Button::input_handler = nullptr;
MassConfigurer* Button::mass_configurer = nullptr;

void Button::set_utilities(SDL_Renderer* r, TextureHandler* t, InputHandler* i, MassConfigurer* m) {
        renderer = r;
        texture_handler = t;
        input_handler = i;
        mass_configurer = m;
} 