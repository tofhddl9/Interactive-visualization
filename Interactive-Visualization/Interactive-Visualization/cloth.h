#pragma once
#include "massspring.h"
#include "Floor.h"
#include "sphere.h"

class Cloth {
public:
    Cloth(){}
    Cloth(int w, int h, float step, float len, float ks, float kd);

    void Update(float dt);
    void Render();
    void CheckCollision(Floor *floor, Sphere * sphere);
    void CheckCollisionWithFloor(Floor* floor);
    void CheckCollisionWithSphere(Sphere* sphere);

private:
    int width_, height_, step_;
    float len_, ks_, kd_;

    MassSpring* massSpring_;
    PointMass*** grid_;
};