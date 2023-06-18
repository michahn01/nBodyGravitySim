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
            Object::mass_configurer->clear_current_config();
            Object::texture_handler->resetCamera();
        }
        Object::input_handler->changeState(change_state);
    }

    virtual void draw() override {
        if (Object::mass_configurer->masses_size) {
            Button::draw();
        }
    }

    virtual void update() override {
        if (Object::mass_configurer->masses_size) {
            Button::update();
        }
    }

private:
    int change_state;
};




#endif