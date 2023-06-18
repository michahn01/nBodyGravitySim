#ifndef MassPlaceDropDown_h
#define MassPlaceDropDown_h

#include "DropDown.h"
#include "../MassPlacer.h"

class MassPlaceDropDown : public DropDown {
    float config_value;
    float& config_item;
    MassPlacer* mass_placer;
public:
    MassPlaceDropDown();
    MassPlaceDropDown(int x, int y, int w, int h, std::string ID, float config_value, float& config_item, MassPlacer* mp);
    void update() override;
    void clickBehavior() override;
};

class PlaceParticles : public DropDown {
    MassPlacer* mass_placer;
public:
    PlaceParticles();
    PlaceParticles(int x, int y, int w, int h, std::string ID, MassPlacer* mp);
    void clickBehavior() override;
};

#endif


