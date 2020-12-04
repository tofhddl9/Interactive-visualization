#pragma once
#include "massspring.h"
#include "Floor.h"
#include "sphere.h"

class Cloth {
public:
    Cloth() {}
    Cloth(int w, int h, float step, float len, float ks, float kd);

    void CheckCollision(Floor *floor, Sphere *sphere);
    void CheckCollisionWithFloor(Floor *floor);
    void CheckCollisionWithSphere(Sphere *sphere);

    void Update(float dt);
    void Render();

    void SetAllUnFixed();

    void operator=(const Cloth&);

private:
    void Init();
    void MakeCheckImage();

    int width_, height_;
    float step_, len_, ks_, kd_;
    MassSpring* massSpring_;
    PointMass*** grid_;

    GLuint texName;
    const int checkImageWidth = 2;
    const int checkImageHeight = 2;
    GLubyte checkImage[2][2][4];
};