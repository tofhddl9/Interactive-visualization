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
    sc_ = sc;
}

void Spring::SetDampingCoefficient(float dc)
{
    dc_ = dc;
}

glm::vec3 Spring::GetForce(PointMass* p)
{
    float dist = glm::distance(pm1_->GetPosition(), pm2_->GetPosition());
    float hook = sc_ * (dist - length_);

    glm::vec3 dir = glm::normalize(pm2_->GetPosition() - pm1_->GetPosition());
    float damping = -dc_ * glm::dot((pm2_->GetVelocity() + pm1_->GetVelocity()), dir);

    if (p == pm1_)
        return (hook + damping) * dir;
    else
        return (-hook + damping) * dir;
}

void Spring::Render()
{
    glColor4f(0.0, 0.3, 1.0, 1.0);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    glVertex3f(pm1_->GetPosition().x,
        pm1_->GetPosition().y,
        pm1_->GetPosition().z);

    glVertex3f(pm2_->GetPosition().x,
        pm2_->GetPosition().y,
        pm2_->GetPosition().z);
    glEnd();
}
