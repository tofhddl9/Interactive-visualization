#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "pointmass.h"

class Floor {

public:
    Floor() {}
    Floor(glm::vec3 pos, float size);

    void Render();

    void ResolveCollision(PointMass *);

private:
    glm::vec3 position_;
    float size_;

    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> faceNormals_;
    std::vector<glm::vec3> vertexNormals_;

    glm::vec4 ambient_;
    glm::vec4 diffuse_;
    glm::vec4 specular_;

    void CreateVertices();
    void CreateFaceNormals();
    void CreateVertexNormals();
};
