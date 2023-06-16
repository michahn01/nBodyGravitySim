// Barnes-Hut Algorithm

#ifndef QuadTree_h
#define QuadTree_h

#include <vector>
#include "../ProgramObjects/Mass.h"

class QuadTree {
public:

    QuadTree(std::vector<Mass*>& masses) : masses(masses) {

    }
    void update();
    void updateAcc(Mass* mass);

private:

    std::vector<Mass*>& masses;

};

#endif