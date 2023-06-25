#include "MassPlacer.h"
#include "cmath"

MassPlacer::MassPlacer() :
Object(0, 0, 0, 0, "")
{}

void MassPlacer::draw() {
    if (!placing) return;
    for (int i = 0; i < placement_masses.size(); ++i) {
        placement_masses[i]->draw();
    }
}

void MassPlacer::update() {
    if (!placing) return;

    Vector2D mouse_pos = Object::input_handler->getMousePosition();
    int x = mouse_pos.getX(); int y = mouse_pos.getY();
    if (y > 0 && y < 50 && x > 0 && 
        ((x < 400) || (Object::mass_configurer->masses_size > 0 && x < 600))) {
            return;
    }
    if (example_configs_button_dropped &&
        x > 0 && x < 200 && y > 0 && y < 190) return;
    if (spawn_particle_button_dropped &&    
        x > 200 && x < 400 && y > 0 && y < 220) return;
    for (int i = 0; i < placement_masses.size(); ++i) {
        placement_masses[i]->update(x, y);
    }
    if (Object::input_handler->getMouseButtonState(LEFT)) {
        while (!placement_masses.empty()) {
            Vector2D pos = placement_masses.back()->getPos();
            Object::mass_configurer->add_mass(new Mass(mass, particle_width, particle_height,
            Object::texture_handler->getAbsolutePosX(pos.getX()), 
            Object::texture_handler->getAbsolutePosY(pos.getY()), 0, 0, 0, 0, "white_mass"));
            delete placement_masses.back(); placement_masses.pop_back();
        }
        placing = false;
    }
}

void MassPlacer::loadMasses() {
    placing = true;
    while (!placement_masses.empty()) {
        delete placement_masses.back();
        placement_masses.pop_back();
    }
    Vector2D mouse_pos = Object::input_handler->getMousePosition();
    if (fabs(mass - 1) < 0.01) particle_height = particle_width = 10; 
    else if (fabs(mass - 10) < 0.01) particle_height = particle_width = 25; 
    else particle_height = particle_width = 5;
    if (int(num_particles) == 1) {
        placement_masses.push_back
        (new PlacementMass(mass, particle_width, particle_height, 
        mouse_pos.getX() - 10, 
        mouse_pos.getY() - 10, -10, -10));
    }
    if (int(num_particles) == 10) {
        int disps[10][2] = {};
        for (int i = 0; i < 10; ++i) {
            disps[i][0] = 35 * std::cos(36 * i * 0.0174532925) - 10;
            disps[i][1] = 35 * std::sin(36 * i * 0.0174532925) - 10;
        }
        for (int i = 0; i < 10; ++i) {
            placement_masses.push_back
            (new PlacementMass(mass, particle_width, particle_height, 
            mouse_pos.getX() + disps[i][0], 
            mouse_pos.getY() + disps[i][1], disps[i][0], disps[i][1]));
        }
    }
}