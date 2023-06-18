#ifndef Button_h
#define Button_h

#include "../Object.h"
#include <vector>
class Button : public Object {
protected:
    virtual void clickBehavior() override;
 
public:
    Button();
    Button(int x, int y, int w, int h, std::string ID);
    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
};


#endif