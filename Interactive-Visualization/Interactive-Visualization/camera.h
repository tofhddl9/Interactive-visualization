#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

class Camera
{
public:
    Camera() {}
    Camera(glm::vec3 pos, glm::vec3 rot);

    void Forward(float dt);
    void Backward(float dt);
    void Up(float dt);
    void Down(float dt);
    void Left(float dt);
    void Right(float dt);

    void RotateUp(float rad);
    void RotateDown(float rad);
    void RotateLeft(float rad);
    void RotateRight(float rad);

    void RollRight(float rad);
    void RollLeft(float rad);

    glm::vec3 GetPosition();
    glm::vec3 GetDirection();
    glm::vec3 GetUp();

private:
    glm::vec3 pos_;
    glm::vec3 dir_;
    glm::vec3 up_;
};