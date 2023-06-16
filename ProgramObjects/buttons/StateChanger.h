#ifndef StateChanger_h
#define StateChanger_h

#include "Button.h"
#include <vector>
class StateChanger : public Button {
public:
    StateChanger(int x, int y, int w, int h, std::string ID, int state) : Button(x, y, w, h, ID), change_state(state) {}
    void setChangeState(int state) {
        change_state = state;
    }
    virtual void clickBehavior() override {
        if (change_state == 0) {
            Button::mass_configurer->clear_current_config();
            Button::texture_handler->resetCamera();
        }
        Button::input_handler->changeState(change_state);
    }

    virtual void draw() override {
        if (Button::mass_configurer->masses_size) {
            Button::draw();
        }
    }

    virtual void update() override {
        if (Button::mass_configurer->masses_size) {
            Button::update();
        }
    }

private:
    int change_state;
};




#endif