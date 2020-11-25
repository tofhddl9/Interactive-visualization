#pragma once
#include <vector>

#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "spring.h"

class PointMass {
public:
    const glm::vec3 GRAVITY = glm::vec3(0.0f, -9.8f, 0.0f);

    PointMass(float mass, glm::vec3 pos);
    void SetMass(float);
    glm::vec3 GetPosition();
    void SetPosition(glm::vec3);
    glm::vec3 GetVelocity();
    void SetVelocity(glm::vec3);
    void SetIsFixed(bool);
    void AddSpring(Spring *);

    glm::vec3 ComputeForces();
    void Update(float dt);
    void Render();

private:
    glm::vec3 acceleration_;
    glm::vec3 velocity_;
    glm::vec3 position_;
    float mass_;
    bool isFixed_;

    std::vector <Spring*> springs_;
};