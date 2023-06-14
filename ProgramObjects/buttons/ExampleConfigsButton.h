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
        CLICKED = 2
    };
    MassConfigurer* mass_configurer;
    virtual void clickBehavior() override;

public:
    ExampleConfigsButton(int x, int y, int w, int h, std::string ID);
    ~ExampleConfigsButton();
    virtual void draw();
    virtual void update();
    virtual void clean();
    bool dropped_down = false;
};

#endif