#pragma once
#include <vector>

#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "spring.h"

class Spring;

class PointMass {
public:
    PointMass(float mass, glm::vec3 pos);

    void SetMass(float mass);

    glm::vec3 GetPosition();
    void SetPosition(glm::vec3 pos);

    glm::vec3 GetVelocity();
    void SetVelocity(glm::vec3 vel);

    void SetIsFixed(bool isFixed);

    void AddSpring(Spring *spring);

    glm::vec3 ComputeForces();
    void Update(float dt);
    void Render();

private:
    std::vector <Spring*> springs_;

    glm::vec3 acceleration_;
    glm::vec3 velocity_;
    glm::vec3 position_;

    float mass_;
    bool isFixed_;

};