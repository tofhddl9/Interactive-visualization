#include "pointmass.h"

PointMass::PointMass(float mass, glm::vec3 pos)
{
    mass_ = mass;
    position_ = pos;

    isFixed_ = false;
    velocity_ = acceleration_ = glm::vec3(0, 0, 0);
}

void PointMass::SetMass(float mass)
{
    mass_ = mass;
}

glm::vec3 PointMass::GetPosition()
{
    return position_;
}

void PointMass::SetPosition(glm::vec3 pos)
{
    position_ = pos;
}

glm::vec3 PointMass::GetVelocity()
{
    return velocity_;
}

void PointMass::SetVelocity(glm::vec3 vel)
{
    velocity_ = vel;
}

void PointMass::SetIsFixed(bool isFixed)
{
    isFixed_ = isFixed;
}

void PointMass::AddSpring(Spring* spring)
{
    springs_.push_back(spring);
}

glm::vec3 PointMass::ComputeForces()
{
    glm::vec3 force = mass_ * GRAVITY;
    for (auto spring : springs_) {
        force += spring->GetForce();
    }

    return force;
}

void PointMass::Update(float dt)
{
    acceleration_ = ComputeForces() / mass_;
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
}

void PointMass::Render()
{
    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POINTS);
    glVertex3f(position_.x, position_.y, position_.z);
    glEnd();
}
