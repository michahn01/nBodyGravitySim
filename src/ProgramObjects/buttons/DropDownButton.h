#ifndef DropDownButton_h
#define DropDownButton_h

#include "Button.h"
#include "DropDown.h"
#include "../../utility/MassConfigurer.h"
#include <vector>
class DropDownButton : public Button {
private:
    std::vector<DropDown*> drop_downs;
    int old_state = 0;
protected:
    enum button_state {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2,
        MOUSE_OUT_DROPPED = 3,
        MOUSE_OVER_DROPPED = 4,
        CLICKED_DROPPED = 5
    };
    MassConfigurer* mass_configurer;
    virtual void clickBehavior() override;

public:
    DropDownButton(int x, int y, int w, int h, std::string ID, bool& dropped);
    ~DropDownButton();
    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
    bool& dropped_down;
    void addConfigDropDown(DropDown* button, std::string config_file) {
        drop_downs.push_back(button);
        drop_downs.back()->setConfigFile(config_file);
    }
    void addDropDown(DropDown* button) {
        drop_downs.push_back(button);
    }
};

#endif