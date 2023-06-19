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

    float threshold = 0.5f;


    Quadrant() {}
    Quadrant(float w, int o_x, int o_y, 
             float t_mass, float c_x, float c_y) :
             width(w), origin_x(o_x), origin_y(o_y), 
             total_mass(t_mass), center_of_mass_x(c_x), center_of_mass_y(c_y)
    {}
    void insert_mass(Mass* body, int depth) {
        if (!body || depth > 10) return;
        if (mass.empty() && !has_children) {
            mass.push_back(body);
            total_mass = body->getMass();
            center_of_mass_x = body->getPos().getX();
            center_of_mass_y = body->getPos().getY();
            return;
        }
        has_children = true;
        // std::cout << "putting a mass into a nonempty node" << std::endl;

        if (!mass.empty() &&
            fabs(body->getPos().getX() - mass.back()->getPos().getX()) < 3.0f && 
            fabs(body->getPos().getY() - mass.back()->getPos().getY()) < 3.0f) {
                mass.push_back(body); return;
        }

        float x = body->getPos().getX();
        float y = body->getPos().getY();
        float new_width = width / 4;

        center_of_mass_x *= total_mass;
        center_of_mass_y *= total_mass;
        total_mass += body->getMass();
        center_of_mass_x = (center_of_mass_x + (x * body->getMass())) / total_mass;
        center_of_mass_y = (center_of_mass_y + (y * body->getMass())) / total_mass;

        int body_quadrant = 0;

        if (x < origin_x) {
            if (y < origin_y) {
                if (!NW_quad) { 
                    NW_quad = new Quadrant(2 * new_width, origin_x - new_width, origin_y - new_width, 0, 0, 0);
                }
                NW_quad->insert_mass(body, depth + 1);
                body_quadrant = 1;
            }
            else {
                if (!SW_quad) { 
                    SW_quad = new Quadrant(2 * new_width, origin_x - new_width, origin_y + new_width, 0, 0, 0);
                }
                SW_quad->insert_mass(body, depth + 1);
                body_quadrant = 4;
            }
        }
        else {
            if (y > origin_y) {
                if (!SE_quad) { 
                    SE_quad = new Quadrant(2 * new_width, origin_x + new_width, origin_y + new_width, 0, 0, 0);
                }
                SE_quad->insert_mass(body, depth + 1);
                body_quadrant = 3;
            }
            else {
                if (!NE_quad) { 
                    NE_quad = new Quadrant(2 * new_width, origin_x + new_width, origin_y - new_width, 0, 0, 0);
                }
                NE_quad->insert_mass(body, depth + 1);
                body_quadrant = 2;
            }
        }


        while (!mass.empty()) {

            float mx = mass.back()->getPos().getX();
            float my = mass.back()->getPos().getY();
        
            if (mx < origin_x) {
                if (my < origin_y) {
                    if (!NW_quad) { 
                        NW_quad = new Quadrant(2 * new_width, origin_x - new_width, origin_y - new_width, 0, 0, 0);
                    }
                    NW_quad->insert_mass(mass.back(), depth + 1);
                    mass.pop_back();
                }
                else {
                    if (!SW_quad) { 
                        SW_quad = new Quadrant(2 * new_width, origin_x - new_width, origin_y + new_width, 0, 0, 0);
                    }
                    SW_quad->insert_mass(mass.back(), depth + 1);
                    mass.pop_back();
                }
            }
            else {
                if (my > origin_y) {
                    if (!SE_quad) { 
                        SE_quad = new Quadrant(2 * new_width, origin_x + new_width, origin_y + new_width, 0, 0, 0);
                    }
                    SE_quad->insert_mass(mass.back(), depth + 1);
                    mass.pop_back();
                }
                else {
                    if (!NE_quad) { 
                        NE_quad = new Quadrant(2 * new_width, origin_x + new_width, origin_y - new_width, 0, 0, 0);
                    }
                    NE_quad->insert_mass(mass.back(), depth + 1);
                    mass.pop_back();
                }
            }
        }
    }

    void addForceToBody(Mass* body, Vector2D& net_force) {
        int x = 0;
        for (int i = 0; i < mass.size(); ++i) {
            if (mass[i] == body) continue;
            float dX = mass[i]->getPos().getX() - body->getPos().getX();
            float dY = mass[i]->getPos().getY() - body->getPos().getY();
            float temp = (body->getMass() * mass[i]->getMass()) / pow(std::max(pow(dX, 2) + pow(dY, 2), 20.0), 1.5);
            net_force += Vector2D(temp * dX, temp * dY);
            x++;
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
    ForceComputer(std::vector<Mass*>& masses) : masses(masses) {
    }
    void update();
    void updateWithBarnesHut();
    void updateAcc(Mass* mass);
    int root_width = 1200;

private:
    std::vector<Mass*>& masses;
    Quadrant* quad_tree = nullptr;
    void cleanAllNodes(Quadrant* node) {
        if (!node) {
            return;
        } 
        if (!node->has_children) {
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