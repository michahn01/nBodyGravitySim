// Barnes-Hut Algorithm

#ifndef ForceComputer_h
#define ForceComputer_h

#include <vector>
#include "../ProgramObjects/Mass.h"

class Quadrant {
public:
    float width;
    int origin_x;
    int origin_y;
    float total_mass;
    float center_of_mass_x;
    float center_of_mass_y;
    bool has_children = false;

    Quadrant* NW_quad = nullptr;
    Quadrant* NE_quad = nullptr;
    Quadrant* SW_quad = nullptr;
    Quadrant* SE_quad = nullptr;

    std::vector<Mass*> mass;
    float mass_x; float mass_y;

    float threshold = 0.5f;


    Quadrant() {}
    Quadrant(float w, int o_x, int o_y, 
             float t_mass, float c_x, float c_y) :
             width(w), origin_x(o_x), origin_y(o_y), 
             total_mass(t_mass), center_of_mass_x(c_x), center_of_mass_y(c_y)
    {}

    bool hasChildren() {
        return NW_quad || NE_quad || SW_quad || SE_quad;
    }

    void updateCenterOfMass(Mass* body) {
        center_of_mass_x *= total_mass;
        center_of_mass_y *= total_mass;
        total_mass += body->getMass();
        center_of_mass_x = (center_of_mass_x + (body->getPos().getX() * body->getMass())) / total_mass;
        center_of_mass_y = (center_of_mass_y + (body->getPos().getY() * body->getMass())) / total_mass;
    }
    
    void iterativeQuadInsert(Mass* body) {
        Quadrant* current = this;
        bool empty_quadrant_found = false;
        int x = body->getPos().getX();
        int y = body->getPos().getY();

        if (!current->hasChildren() && current->mass.empty()) {
            empty_quadrant_found = true;
        }

        while (!empty_quadrant_found) {
            if (!current->mass.empty() && 
                fabs(current->mass_x - x) < 1.0f && 
                fabs(current->mass_y - y) < 1.0f) {
                    current->mass.push_back(body);
                    current->updateCenterOfMass(body);
                    return;
            }
            float quarter_width = current->width / 4.0f;

            if (!current->mass.empty()) {
                Quadrant* selected_quad;
                if (current->mass_x < current->origin_x) {
                    if (current->mass_y < current->origin_y) {
                        if (current->NW_quad == nullptr) {
                            selected_quad = current->NW_quad = 
                            new Quadrant(2 * quarter_width, current->origin_x - quarter_width, current->origin_y - quarter_width, 0, 0, 0);
                        }
                    }
                    else {
                        if (current->SW_quad == nullptr) { 
                            selected_quad = current->SW_quad = 
                            new Quadrant(2 * quarter_width, current->origin_x - quarter_width, current->origin_y + quarter_width, 0, 0, 0);
                        }
                    }
                }
                else {
                    if (current->mass_y > current->origin_y) {
                        if (current->SE_quad == nullptr) { 
                            selected_quad = current->SE_quad = 
                            new Quadrant(2 * quarter_width, current->origin_x + quarter_width, current->origin_y + quarter_width, 0, 0, 0);
                        }
                    }
                    else {
                        if (current->NE_quad == nullptr) { 
                            selected_quad = current->NE_quad = 
                            new Quadrant(2 * quarter_width, current->origin_x + quarter_width, current->origin_y - quarter_width, 0, 0, 0);
                        }
                    }
                }
                while (!current->mass.empty()) {
                    selected_quad->mass.push_back(current->mass.back()); 
                    selected_quad->updateCenterOfMass(mass.back());
                    current->mass.pop_back();
                }
            }

            
            if (x < current->origin_x) {
                if (y < current->origin_y) {
                    if (current->NW_quad == nullptr) { 
                        current->NW_quad = 
                        new Quadrant(2 * quarter_width, current->origin_x - quarter_width, current->origin_y - quarter_width, 0, 0, 0);
                        empty_quadrant_found = true;
                    }
                    current->updateCenterOfMass(body);
                    current = current->NW_quad;
                }
                else {
                    if (current->SW_quad == nullptr) { 
                        current->SW_quad = 
                        new Quadrant(2 * quarter_width, current->origin_x - quarter_width, current->origin_y + quarter_width, 0, 0, 0);
                        empty_quadrant_found = true;
                    }
                    current->updateCenterOfMass(body);
                    current = current->SW_quad;
                }
            }
            else {
                if (y > current->origin_y) {
                    if (current->SE_quad == nullptr) { 
                        current->SE_quad = 
                        new Quadrant(2 * quarter_width, current->origin_x + quarter_width, current->origin_y + quarter_width, 0, 0, 0);
                        empty_quadrant_found = true;
                    }
                    current->updateCenterOfMass(body);
                    current = current->SE_quad;
                }
                else {
                    if (current->NE_quad == nullptr) { 
                        current->NE_quad = 
                        new Quadrant(2 * quarter_width, current->origin_x + quarter_width, current->origin_y - quarter_width, 0, 0, 0);
                        empty_quadrant_found = true;
                    }
                    current->updateCenterOfMass(body);
                    current = current->NE_quad;
                }
            }
        }
        current->mass.push_back(body);
        current->total_mass = body->getMass();
        current->center_of_mass_x = mass_x = x;
        current->center_of_mass_y = mass_y = y;
    }


    void addForceToBody(Mass* body, Vector2D& net_force) {
        int x = 0;
        for (int i = 0; i < mass.size(); ++i) {
            x++;
            if (mass[i] == body) continue;
            float dX = mass[i]->getPos().getX() - body->getPos().getX();
            float dY = mass[i]->getPos().getY() - body->getPos().getY();
            float temp = (body->getMass() * mass[i]->getMass()) / pow(std::max(pow(dX, 2) + pow(dY, 2), 20.0), 1.5);
            net_force += Vector2D(temp * dX, temp * dY);
        }
        if (x > 0) return;
        float dX = center_of_mass_x - body->getPos().getX();
        float dY = center_of_mass_y - body->getPos().getY();
        float dist_sq = pow(dX, 2) + pow(dY, 2);
        if (width / sqrt(dist_sq) < threshold) {
            float temp = (body->getMass() * total_mass) / pow(std::max(dist_sq, 20.0f), 1.5);
            net_force += Vector2D(temp * dX, temp * dY);
            return;
        }
        if (NW_quad) NW_quad->addForceToBody(body, net_force);
        if (NE_quad) NE_quad->addForceToBody(body, net_force);
        if (SW_quad) SW_quad->addForceToBody(body, net_force);
        if (SE_quad) SE_quad->addForceToBody(body, net_force);
    }

};

class ForceComputer {
public:
    ForceComputer(std::vector<Mass*>& masses, int& root_width) : masses(masses), root_width(root_width) {
    }
    void update();
    void updateWithBarnesHut();
    void updateAcc(Mass* mass);
    int& root_width;

private:
    std::vector<Mass*>& masses;
    void cleanAllNodes(Quadrant* node) {
        if (node == nullptr) {
            return;
        } 
        if (!node->hasChildren()) {
            delete node;
            node = nullptr;
            return;
        }
        cleanAllNodes(node->NW_quad);
        cleanAllNodes(node->NE_quad);
        cleanAllNodes(node->SW_quad);
        cleanAllNodes(node->SE_quad);
        delete node;
        node = nullptr;
    }

};

#endif