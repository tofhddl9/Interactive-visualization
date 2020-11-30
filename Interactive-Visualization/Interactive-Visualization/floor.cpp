#include "floor.h"

Floor::Floor(glm::vec3 pos, float size) : position_(pos), size_(size){
    
    Floor::CreateVertices();
    Floor::CreateFaceNormals();
    Floor::CreateVertexNormals();
}

void Floor::CreateVertices() {
    vertices_.push_back(glm::vec3(-1.0f * size_ + position_.x,
                                  -0.2f + position_.y,
                                  -1.0f * size_ + position_.z));

    vertices_.push_back(glm::vec3(-1.0f * size_ + position_.x,
                                  -0.2f + position_.y,
                                  1.0f * size_ + position_.z));

    vertices_.push_back(glm::vec3(1.0f * size_ + position_.x,
                                 -0.2f + position_.y,
                                  1.0f * size_ + position_.z));

    vertices_.push_back(glm::vec3(-1.0f * size_ + position_.x,
                                  -0.2f + position_.y,
                                  -1.0f * size_ + position_.z));

    vertices_.push_back(glm::vec3(1.0f * size_ + position_.x,
                                 -0.2f + position_.y,
                                  1.0f * size_ + position_.z));

    vertices_.push_back(glm::vec3(1.0f * size_ + position_.x,
                                 -0.2f + position_.y,
                                 -1.0f * size_ + position_.z));
}


void Floor::CreateFaceNormals() {

    for (auto it = vertices_.begin(); it != vertices_.end(); std::advance(it, 3)) {
        glm::vec3 v0 = (*(it + 1)) - (*it);
        glm::vec3 v1 = (*(it + 2)) - (*it);
        faceNormals_.push_back(glm::normalize(glm::cross(v0, v1)));
    }
}


void Floor::CreateVertexNormals() {

    unsigned int i = 0;

    for (auto it = faceNormals_.begin(); it != faceNormals_.end(); ++it, ++i) {
        vertexNormals_.push_back(faceNormals_.at(i));
        vertexNormals_.push_back(faceNormals_.at(i));
        vertexNormals_.push_back(faceNormals_.at(i));
    }
}

void Floor::ResolveCollision(PointMass* pm) {

    if (pm->GetPosition().y < this->position_.y) {

        float dist = abs(pm->GetPosition().y - this->position_.y);

        glm::vec3 p = pm->GetPosition();

        pm->SetPosition(glm::vec3(p.x, this->position_.y + dist * 4.0f, p.z));

        pm->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void Floor::Render() {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glColor4f(0.1, 0.3, 0.5, 1.0);
    glBegin(GL_POLYGON);
    for (auto v : vertices_) {
        glNormal3f(0, 1, 0);
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}