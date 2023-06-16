#ifndef DropDown_h
#define DropDown_h

#include "Button.h"
#include <vector>
class DropDown : public Button {
protected:
    virtual void clickBehavior() override;
public:
    DropDown(int x, int y, int w, int h, std::string ID);
    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
    void setConfigFile(std::string file_name);
    std::string config_file;
};

#endif