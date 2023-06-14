#include "DropDown.h"
#include <iostream>

DropDown::DropDown(int x, int y, int w, int h, std::string ID) :
                   Button(x, y, w, h, ID)
                   {}

void DropDown::draw() {
    Button::draw();
}

void DropDown::update() {
    Button::update();
}

void DropDown::clean() {
    
}

void DropDown::clickBehavior() {
    Button::mass_configurer->load_configuration(config_file);
}

void DropDown::setConfigFile(std::string file_name) {
    config_file = file_name;
}

