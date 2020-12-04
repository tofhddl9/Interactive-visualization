#include "camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 rot)
{
    pos_ = pos;
    dir_ = glm::normalize(rot);

    glm::vec3 right = glm::cross(dir_, glm::vec3(0.0, 1.0, 0.0));
    up_ = glm::normalize(glm::cross(right, dir_));
}

void Camera::Up(float dt)
{
    pos_ += up_ * dt;
}

void Camera::Down(float dt)
{
    pos_ -= up_ * dt;
}

void Camera::Forward(float dt)
{
    pos_ += dir_ * dt;
}

void Camera::Backward(float dt)
{
    pos_ -= dir_ * dt;
}

void Camera::Left(float dt)
{
    glm::vec3 left = -glm::cross(dir_, up_);
    pos_ += left * dt;
}

void Camera::Right(float dt)
{
    glm::vec3 right = glm::cross(dir_, up_);
    pos_ += right * dt;
}

void Camera::RotateUp(float rad)
{
    glm::vec3 right = glm::cross(dir_, up_);
    up_ = glm::rotate(up_, rad, right);
    dir_ = glm::rotate(dir_, rad, right);
}

void Camera::RotateDown(float rad)
{
    glm::vec3 right = glm::cross(dir_, up_);
    up_ = glm::rotate(up_, -rad, right);
    dir_ = glm::rotate(dir_, -rad, right);
}

void Camera::RotateLeft(float rad)
{
    dir_ = glm::rotate(dir_, -rad, -up_);
}

void Camera::RotateRight(float rad)
{
    dir_ = glm::rotate(dir_, rad, -up_);
}

void Camera::RollRight(float rad)
{
    up_ = glm::rotate(up_, rad, -dir_);
}

void Camera::RollLeft(float rad)
{
    up_ = glm::rotate(up_, -rad, -dir_);
}

glm::vec3 Camera::GetPosition()
{
    return pos_;
}

glm::vec3 Camera::GetDirection()
{
    return dir_;
}

glm::vec3 Camera::GetUp()
{
    return up_;
}
