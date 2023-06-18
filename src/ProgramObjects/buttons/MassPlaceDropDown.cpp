#include "MassPlaceDropDown.h"

MassPlaceDropDown::MassPlaceDropDown(int x, int y, int w, int h, 
std::string ID, float config_value, float& config_item, MassPlacer* mp) :
DropDown(x, y, w, h, ID), config_value(config_value), config_item(config_item), mass_placer(mp) {
}

void MassPlaceDropDown::clickBehavior() {
    config_item = config_value;
    if (mass_placer->placing) mass_placer->loadMasses();
}

void MassPlaceDropDown::update() {
    Vector2D pMousePos = Object::input_handler->getMousePosition();

    if (config_value == config_item) {
        current_frame = CLICKED;
    }
    else if (pMousePos.getX() < (pos.getX() + width)
            && pMousePos.getX() > pos.getX()
            && pMousePos.getY() < (pos.getY() + height)
            && pMousePos.getY() > pos.getY()) {
            if (Object::input_handler->getMouseButtonState(LEFT)) {
                clickBehavior();
            }
            else {
                current_frame = MOUSE_OVER;
            }
    }
    else {
        current_frame = MOUSE_OUT;
    }
}

PlaceParticles::PlaceParticles(int x, int y, int w, int h, std::string ID, MassPlacer* mp) :
DropDown(x, y, w, h, ID), mass_placer(mp) {
}

void PlaceParticles::clickBehavior() {
    mass_placer->loadMasses();
}
