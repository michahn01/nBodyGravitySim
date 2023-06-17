#ifndef ExampleConfigsButton_h
#define ExampleConfigsButton_h

#include "Button.h"
#include "DropDown.h"
#include "../../utility/MassConfigurer.h"
#include <vector>
class ExampleConfigsButton : public Button {
private:
    std::vector<DropDown*> drop_downs;
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
    ExampleConfigsButton(int x, int y, int w, int h, std::string ID);
    ~ExampleConfigsButton();
    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
    bool dropped_down = false;
};

#endif