#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "pointmass.h"

class Sphere
{
public:
    Sphere(glm::vec3 pos, float radius = 1.0f, int sectorCount = 36, int stackCount = 18);
    ~Sphere() {}

    void Render();

    void ResolveCollision(PointMass* pm);
    void MovePX(float dt);
    void MoveNX(float dt);
    void MovePZ(float dt);
    void MoveNZ(float dt);

private:

    void BuildVertices();
    void BuildInterleavedVertices();
    void ClearArrays();

    void AddVertex(float x, float y, float z);
    void AddNormal(float x, float y, float z);
    void AddTexCoord(float s, float t);
    void AddIndices(unsigned int i1, unsigned int i2, unsigned int i3);

    glm::vec3 pos_;
    float radius_;
    int sectorCount_;
    int stackCount_;

    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<float> texCoords_;
    std::vector<unsigned int> indices_;

    int interleavedStride_;
    std::vector<float> interleavedVertices_;

};