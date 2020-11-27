#include "cloth.h"

Cloth::Cloth(int w, int h, float step, float len, float ks, float kd)
{
	width_ = w, height_ = h, step_ = step;
	len_ = len, ks_ = ks, kd_ = kd;

	massSpring_ = new MassSpring();
	
	grid_ = new PointMass**[h];
	for (int i = 0; i < h; ++i) {
		grid_[i] = new PointMass * [w];
	}

	float z = 5.0f;
	for (int i = 0; i < height_; ++i) {
		float x = 5.0f;
		for (int j = 0; j < width_; ++j) {
			grid_[i][j] = massSpring_->AddMass(0.01, glm::vec3(x, 10.0f, z));
			x += step_;

			if (j == 0)
				grid_[i][j]->SetIsFixed(true);
		}
		z += step_;
	}

	//structural + shear
	for (int i = 0; i < height_ - 1; ++i) {
		for (int j = 0; j < width_ - 1; ++j) {
			Spring* s1 = massSpring_
				->AddSpring(len_, ks_, kd_, grid_[i][j], grid_[i][j + 1]);

			Spring* s2 = massSpring_
				->AddSpring(len_, ks_, kd_, grid_[i][j], grid_[i + 1][j]);

			if (i == height_ - 2) {
				Spring* s3 = massSpring_
					->AddSpring(len_, ks_, kd_, grid_[i + 1][j], grid_[i + 1][j + 1]);
			}
			if (j == width_ - 2) {
				Spring* s4 = massSpring_
					->AddSpring(len_, ks_, kd_, grid_[i][j + 1], grid_[i + 1][j + 1]);
			}

			Spring* s5 = massSpring_
				->AddSpring(len_ * 1.4142f, ks_, kd_, grid_[i][j], grid_[i + 1][j + 1]);

			Spring* s6 = massSpring_
				->AddSpring(len_ * 1.4142f, ks_, kd_, grid_[i + 1][j], grid_[i][j + 1]);
		}
	}

	//bending
	for (int i = 0; i < height_ - 2; ++i) {
		for (int j = 0; j < width_ - 2; ++j) {
			Spring* s1 = massSpring_
				->AddSpring(2 * len_, ks_, kd_, grid_[i][j], grid_[i][j + 2]);

			Spring* s2 = massSpring_
				->AddSpring(2 * len_, ks_, kd_, grid_[i][j], grid_[i + 2][j]);

			if (i == height_ - 3) {
				Spring* s3 = massSpring_
					->AddSpring(2 * len_, ks_, kd_, grid_[i + 2][j], grid_[i + 2][j + 2]);
			}
			if (j == width_ - 3) {
				Spring* s4 = massSpring_
					->AddSpring(2 * len_, ks_, kd_, grid_[i][j + 2], grid_[i + 2][j + 2]);
			}
		}
	}

	//faces
	for (int i = 0; i < height_ - 1; ++i) {
		for (int j = 0; j < width_ - 1; ++j) {
			massSpring_->AddFace(grid_[i][j], grid_[i + 1][j], grid_[i + 1][j + 1]);
			massSpring_->AddFace(grid_[i][j], grid_[i + 1][j + 1], grid_[i][j + 1]);
		}
	}
}

void Cloth::Update(float dt)
{
	massSpring_->Update(dt);
}

void Cloth::Render()
{
	massSpring_->Render();
}

void Cloth::CheckCollision(Floor *floor, Sphere * sphere)
{
	CheckCollisionWithFloor(floor);
	CheckCollisionWithSphere(sphere);
}

void Cloth::CheckCollisionWithFloor(Floor* floor)
{
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			floor->ResolveCollision(grid_[i][j]);
		}
	}
}

void Cloth::CheckCollisionWithSphere(Sphere * sphere)
{
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			sphere->ResolveCollision(grid_[i][j]);
		}
	}
}