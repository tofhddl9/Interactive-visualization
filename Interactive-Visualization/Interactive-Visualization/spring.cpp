#include "spring.h"

Spring::Spring(float len, float sc, float dc, PointMass* pm1, PointMass* pm2)
{
    length_ = len;
    sc_ = sc;
    dc_ = dc;
    pm1_ = pm1;
    pm2_ = pm2;
}

void Spring::SetLength(float len)
{
    length_ = len;
}

void Spring::SetSpringCoefficient(float sc)
{
    sc_ = c;
}

void Spring::SetDampingCoefficient(float dc)
{
    dc_ = dc;
}

glm::vec3 Spring::getForce(PointMass* p)
{
    if (p != pm1_ && p != pm2_) return glm::vec3(0, 0, 0);

    float dist = glm::distance(pm1_->GetPosition(), pm2_->GetPosition());
    float displacement = dist - length_;
    glm::vec3 dir = glm::normalize(pm2_->GetPosition() - pm1_->GetPosition());
    float hook = sc_ * displacement;
    
    glm::vec3 relV = pm2_->GetVelocity() - pm1_->GetVelocity();
    float damping = dc_ * glm::dot(relV, dir);

    glm::vec3 internalForce = dir * (hook + damping);

    if (p == pm1_) {
        return internalForce;
    }
    else {
        return -internalForce;
    }
}
