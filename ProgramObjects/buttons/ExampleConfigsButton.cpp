#include "ExampleConfigsButton.h"

ExampleConfigsButton::ExampleConfigsButton(int x, int y, int w, int h, std::string ID) :
Button(x, y, w, h, ID) {
    current_frame = MOUSE_OUT; // start at frame 0
    drop_downs.push_back(new DropDown(x, y + height, 200, 35, "euler_3_body")); 
    drop_downs.back()->setConfigFile("resources/mass_configurations/euler_3_body.csv");
    drop_downs.push_back(new DropDown(x, y + height + 35, 200, 35, "unstable_3_body")); 
    drop_downs.back()->setConfigFile("resources/mass_configurations/unstable_3_body.csv");
}

ExampleConfigsButton::~ExampleConfigsButton() {
    while (!drop_downs.empty()) {
        delete drop_downs.back(); 
        drop_downs.pop_back();
    }
}
void ExampleConfigsButton::draw() {
    Button::texture_handler->drawFrame(texture_ID, 0, 0, width, height, 0, 0, width, height, 0, current_frame, Button::renderer);
    if (dropped_down) {
        for (int i = 0; i < drop_downs.size(); ++i) {
            drop_downs[i]->draw();
        }
    }
}
void ExampleConfigsButton::update() {
    Vector2D pMousePos = input_handler->getMousePosition();
    if (Button::input_handler->getState() == 1) {
        current_frame = MOUSE_OUT;
        dropped_down = false;
    }
    else if (dropped_down && 
        !(pMousePos.getX() < (pos.getX() + 2*width)
        && pMousePos.getX() > pos.getX()
        && pMousePos.getY() < (pos.getY() + height + drop_downs.size() * 35)
        && pMousePos.getY() > pos.getY()) &&
        Button::input_handler->getMouseButtonState(LEFT)) {
            current_frame = MOUSE_OUT;
            dropped_down = false;
    }
    else if (current_frame == CLICKED) {
        if (!Button::input_handler->getMouseButtonState(LEFT)) {
            dropped_down = true;
        }
    }
    else {
        if (pMousePos.getX() < (pos.getX() + width)
            && pMousePos.getX() > pos.getX()
            && pMousePos.getY() < (pos.getY() + height)
            && pMousePos.getY() > pos.getY()) {
            if (Button::input_handler->getMouseButtonState(LEFT)) {
                current_frame = CLICKED;
            }
            else {
                current_frame = MOUSE_OVER;
                dropped_down = false;
            }
        }
        else {
            current_frame = MOUSE_OUT;
            dropped_down = false;
        }
    }

    if (dropped_down) {
        for (int i = 0; i < drop_downs.size(); ++i) {
            drop_downs[i]->update();
        }
    }
}
void ExampleConfigsButton::clean() {
}

void ExampleConfigsButton::clickBehavior() {
    dropped_down = true;
}