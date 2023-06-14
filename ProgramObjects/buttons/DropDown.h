#ifndef DropDown_h
#define DropDown_h

#include "Button.h"
#include <vector>
class DropDown : public Button {
protected:
    virtual void clickBehavior() override;
public:
    DropDown(int x, int y, int w, int h, std::string ID);
    virtual void draw();
    virtual void update();
    virtual void clean();
    void setConfigFile(std::string file_name);
    std::string config_file;
};

#endif