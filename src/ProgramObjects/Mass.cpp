#include "Mass.h"

void Mass::draw() {
    texture_handler->drawZoom(texture_ID, pos.getX(), pos.getY(), width, height, 0, 0, 100, 100, renderer);
}
void Mass::update(int dT) {
    vel += acc * dT/2.0;
    pos += vel * dT;
}
void Mass::clean() {
}

SDL_Renderer* Mass::renderer = nullptr;
TextureHandler* Mass::texture_handler = nullptr;
InputHandler* Mass::input_handler = nullptr;

void Mass::set_utilities(SDL_Renderer* r, TextureHandler* t, InputHandler* i) {
        renderer = r;
        texture_handler = t;
        input_handler = i;
}

void Mass::leapFrog1(int dT) {
    vel += acc*dT/2.0;
    pos += vel*dT;
}

void Mass::leapFrog2(int dT) {
    vel += acc*dT/2.0;
}