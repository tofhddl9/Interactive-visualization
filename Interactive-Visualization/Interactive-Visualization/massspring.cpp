#include "massspring.h"

MassSpring::~MassSpring()
{
    for (auto mass : masses_) {
        delete mass;
    }
    for (auto spring : springs_) {
        delete spring;
    }
}

PointMass* MassSpring::AddMass(float mass, glm::vec3 pos)
{
    PointMass* pm = new PointMass(mass, pos);
    masses_.push_back(pm);

    return pm;
}

Spring* MassSpring::AddSpring(float sc, float dc, float len, PointMass* pm1, PointMass* pm2)
{
    Spring* sp = new Spring(sc, dc, len, pm1, pm2);
    pm1->AddSpring(sp);
    pm2->AddSpring(sp);
    springs_.push_back(sp);

    return sp;
}

void MassSpring::Update(float dt)
{
    for (auto mass : masses_) {
        mass->Update(dt);
    }
}

void MassSpring::Render()
{
    for (auto mass : masses_) {
        mass->Render();
    }
    for (auto spring : springs_) {
        spring->Render();
    }
}
