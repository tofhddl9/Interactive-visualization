#pragma once

#include <vector>
#include "pointmass.h"
#include "spring.h"

class MassSpring {
public:
    ~MassSpring();
    PointMass* AddMass(float mass, glm::vec3 pos);
    Spring* AddSpring(float sc, float dc, float len,
        PointMass * pm1, PointMass * pm2);

    void Update(float dt);
    void Render();
private:
    std::vector<PointMass*> masses_;
    std::vector<Spring*> springs_;
};