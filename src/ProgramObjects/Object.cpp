#include "Object.h"
#include <iostream>

Object::Object() {}
Object::Object(int x, int y, int w, int h, std::string ID) :
pos(x, y), vel(0, 0), acc(0, 0), width(w), height(h), texture_ID(ID) {
    current_frame = MOUSE_OUT; // start at frame 0
}
void Object::draw() {
    texture_handler->drawFrame(texture_ID, pos.getX(), pos.getY(), width, height, 0, 0, width, height, 0, current_frame, renderer);
}
void Object::update() {
    
}
void Object::clean() {
}

void Object::clickBehavior() {

}



SDL_Renderer* Object::renderer = nullptr;
TextureHandler* Object::texture_handler = nullptr;
InputHandler* Object::input_handler = nullptr;
MassConfigurer* Object::mass_configurer = nullptr;

void Object::set_utilities(SDL_Renderer* r, TextureHandler* t, InputHandler* i, MassConfigurer* m) {
        renderer = r;
        texture_handler = t;
        input_handler = i;
        mass_configurer = m;
} 