#include "ForceComputer.h"
#include <cmath>
#include <algorithm>

void ForceComputer::update() {
    for (int i = 0; i < masses.size(); ++i) {
        Vector2D net_force(0, 0);
        Mass* m1 = masses[i]; 
        for (int j = 0; j < i; ++j) {
            Mass* m2 = masses[j]; 
            float dX = m2->getPos().getX() - m1->getPos().getX();
            float dY = m2->getPos().getY() - m1->getPos().getY();
            // std::cout << pow(dX, 2) + pow(dY, 2) << std::endl;
            float temp = (m1->getMass() * m2->getMass()) / pow(std::max(pow(dX, 2) + pow(dY, 2), 20.0), 1.5);
            net_force += Vector2D(temp * dX, temp * dY);
        }
        for (int j = i + 1; j < masses.size(); ++j) {
            Mass* m2 = masses[j]; 
            float dX = m2->getPos().getX() - m1->getPos().getX();
            float dY = m2->getPos().getY() - m1->getPos().getY();
            // std::cout << pow(dX, 2) + pow(dY, 2) << std::endl;
            float temp = (m1->getMass() * m2->getMass()) / pow(std::max(pow(dX, 2) + pow(dY, 2), 20.0), 1.5);
            net_force += Vector2D(temp * dX, temp * dY);
        }

        net_force /= m1->getMass();
        m1->getAccRef() = net_force;
    }
}

void ForceComputer::updateWithBarnesHut() {
    quad_tree = new Quadrant(root_width, 0, 0, 0, 0, 0);
    for (int i = 0; i < masses.size(); ++i) {
        quad_tree->iterativeQuadInsert(masses[i]);
    }   
    for (int i = 0; i < masses.size(); ++i) {
        Vector2D net_force(0, 0);
        quad_tree->addForceToBody(masses[i], net_force);   
        net_force /= masses[i]->getMass();
        masses[i]->getAccRef() = net_force;   
    }
    cleanAllNodes(quad_tree);

}