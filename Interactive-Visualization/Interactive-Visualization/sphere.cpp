#include "sphere.h"

Sphere::Sphere(glm::vec3 pos, float radius, int sectors, int stacks) : interleavedStride_(24)
{
    pos_ = pos;
    radius_ = radius;
    sectorCount_ = sectors;
    stackCount_ = stacks;
    BuildVertices();
}

void Sphere::ClearArrays()
{
    std::vector<float>().swap(vertices_);
    std::vector<float>().swap(normals_);
    std::vector<int>().swap(indices_);
}

void Sphere::BuildVertices()
{
    ClearArrays();
    const float PI = acos(-1);

    float x, y, z, xy;
    float nx, ny, nz;
    float s, t;

    float sectorStep = 2 * PI / sectorCount_;
    float stackStep = PI / stackCount_;

    for (int i = 0; i <= stackCount_; ++i) {
        float stackAngle = PI / 2 - i * stackStep;
        xy = radius_ * cosf(stackAngle);
        z = radius_ * sinf(stackAngle);

        for (int j = 0; j <= sectorCount_; ++j) {
            float sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            AddVertex(x, y, z);

            nx = x / radius_;
            ny = y / radius_;
            nz = z / radius_;
            AddNormal(nx, ny, nz);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    int k1, k2;
    for (int i = 0; i < stackCount_; ++i) {
        k1 = i * (sectorCount_ + 1);
        k2 = k1 + sectorCount_ + 1;

        for (int j = 0; j < sectorCount_; ++j, ++k1, ++k2) {
            if (i != 0) {
                AddIndices(k1, k2, k1 + 1);
            }

            if (i != (stackCount_ - 1)) {
                AddIndices(k1 + 1, k2, k2 + 1);
            }
        }
    }

    BuildInterleavedVertices();
}

void Sphere::BuildInterleavedVertices()
{
    std::vector<float>().swap(interleavedVertices_);

    std::size_t i, j;
    std::size_t count = vertices_.size();
    for (i = 0, j = 0; i < count; i += 3)
    {
        interleavedVertices_.push_back(vertices_[i]);
        interleavedVertices_.push_back(vertices_[i + 1]);
        interleavedVertices_.push_back(vertices_[i + 2]);

        interleavedVertices_.push_back(normals_[i]);
        interleavedVertices_.push_back(normals_[i + 1]);
        interleavedVertices_.push_back(normals_[i + 2]);
    }
    // stride = 4 * (3 + 3) = 24
}

void Sphere::Render()
{
    BuildVertices();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, interleavedStride_, &interleavedVertices_[0]);
    glNormalPointer(GL_FLOAT, interleavedStride_, &interleavedVertices_[3]);

    glDrawElements(GL_TRIANGLES, (unsigned int)indices_.size(), GL_UNSIGNED_INT, indices_.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Sphere::AddVertex(float x, float y, float z)
{
    vertices_.push_back(x + pos_.x);
    vertices_.push_back(y + pos_.y);
    vertices_.push_back(z + pos_.z);
}

void Sphere::AddNormal(float nx, float ny, float nz)
{
    normals_.push_back(nx);
    normals_.push_back(ny);
    normals_.push_back(nz);
}

void Sphere::AddIndices(int i1, int i2, int i3)
{
    indices_.push_back(i1);
    indices_.push_back(i2);
    indices_.push_back(i3);
}

void Sphere::ResolveCollision(PointMass* pm)
{
    float dist = glm::length(pm->GetPosition() - pos_);

    if (dist < radius_) {
        glm::vec3 intersection_normal = glm::normalize(pm->GetPosition() - pos_);
        float penetration = radius_ - dist;
            
        glm::vec3 pos = pm->GetPosition();

        pos += (1.0f * penetration) * intersection_normal;
        pm->SetPosition(pos);
        glm::vec3 v = pm->GetVelocity();
        pm->SetVelocity(v * 0.0f);
    }
}

void Sphere::MovePX(float dt)
{
    pos_ += glm::vec3(1, 0, 0) * dt;
}

void Sphere::MoveNX(float dt)
{
    pos_ -= glm::vec3(1, 0, 0) * dt;
}

void Sphere::MovePZ(float dt)
{
    pos_ += glm::vec3(0, 0, 1) * dt;
}

void Sphere::MoveNZ(float dt)
{
    pos_ -= glm::vec3(0, 0, 1) * dt;
}