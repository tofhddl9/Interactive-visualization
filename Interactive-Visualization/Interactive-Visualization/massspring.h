#pragma once

#include <vector>
#include "pointmass.h"
#include "spring.h"

class MassSpring {
public:
    MassSpring() {}
    ~MassSpring();

    PointMass* AddMass(float mass, glm::vec3 pos);
    Spring* AddSpring(float len, float sc, float dc,
        PointMass * pm1, PointMass * pm2);
    void AddFace(PointMass* pm1, PointMass* pm2, PointMass* pm3);
    
    void Update(float dt);
    void Render();

private:
    std::vector<PointMass*> masses_;
    std::vector<Spring*> springs_;
    std::vector<PointMass*> faces_; 
};

