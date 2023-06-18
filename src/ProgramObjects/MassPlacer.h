#ifndef MassPlacer_h
#define MassPlacer_h

#include "../utility/MassConfigurer.h"
#include "Object.h"
#include <unordered_map>


class PlacementMass : public Mass {
    int x_displacement; int y_displacement;
public:
    PlacementMass(float mass, float width, float height, float mouse_x, float mouse_y, int x_displacement, int y_displacement) :
    Mass(mass, width, height, mouse_x, mouse_y, 0, 0, 0, 0, "green_mass"),
    x_displacement(x_displacement), y_displacement(y_displacement) 
    { }
    void update(int x, int y) {
        pos.setX(x + x_displacement);
        pos.setY(y + y_displacement);
    }

    void draw() override {
        texture_handler->drawPlacement(texture_ID, pos.getX(), pos.getY(), width, height, 0, 0, 100, 100, renderer);
    }
};

class MassPlacer : public Object {
private:
public:
    MassPlacer();
    void draw() override;
    void update() override;
    void loadMasses();
    float num_particles = 1;
    float mass = 1;
    float particle_width = 5; float particle_height = 5;
    bool placing = false;
    Vector2D placement_pos;
    std::vector<PlacementMass*> placement_masses;
    bool example_configs_button_dropped;
    bool spawn_particle_button_dropped;
};

#endif