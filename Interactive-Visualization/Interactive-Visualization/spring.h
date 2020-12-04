#pragma once

#include "glm/glm.hpp"
#include "pointmass.h"

class PointMass;

class Spring {
public:
    Spring(float len, float sc, float dc,
        PointMass* pm1, PointMass* pm2);
    void SetLength(float len);
    void SetSpringCoefficient(float sc);
    void SetDampingCoefficient(float dc);

    glm::vec3 GetForce(PointMass *p);
    void Render();

private:
    float length_;
    float sc_;
    float dc_;
    PointMass *pm1_;
    PointMass *pm2_;
};