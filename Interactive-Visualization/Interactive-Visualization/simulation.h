#pragma once
#include "camera.h"
#include "cloth.h"
#include "floor.h"
#include "sphere.h"

class Simulation {
public:
    Simulation();

    void Update();
    void Render();

    void MoveSpherePX(float d);
    void MoveSphereNX(float d);
    void MoveSpherePZ(float d);
    void MoveSphereNZ(float d);
    void CheckCollision(Floor *floor, Sphere *sphere);

    void SetAllUnFixed();

private:
    Camera *camera_;
    Cloth *cloth_;
    Floor *floor_;
    Sphere *sphere_;
};