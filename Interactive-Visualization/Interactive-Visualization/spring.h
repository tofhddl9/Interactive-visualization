#pragma once

#include "glm/glm.hpp"
#include "pointmass.h"

class Spring {
public:
    Spring(float len, float sc, float dc, PointMass* pm1, PointMass* pm2);
    void SetLength(float len);
    void SetSpringCoefficient(float sc);
    void SetDampingCoefficient(float dc);
    glm::vec3 getForce(PointMass *p);
    void Render();

private:
    float length_;
    float sc_; //spring coefficient
    float dc_; //damping coefficient
    PointMass* pm1_, *pm2_;
};