#include "cloth.h"

void Cloth::MakeCheckImage()
{
	for (int i = 0; i < checkImageHeight; i++) {
		for (int j = 0; j < checkImageWidth; j++) {
			int c;
			if ((((i & 1) == 0) ^ ((j & 1)) == 0))
				c = 255;
			else 
				c = 0;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
}

void Cloth::Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	MakeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

Cloth::Cloth(int w, int h, float step, float len, float ks, float kd)
{
	width_ = w, height_ = h, step_ = step;
	len_ = len, ks_ = ks, kd_ = kd;

	massSpring_ = new MassSpring();
	
	grid_ = new PointMass**[h];
	for (int i = 0; i < h; ++i) {
		grid_[i] = new PointMass * [w];
	}

	//scene 1, 2
	float z = 8.0f;
	for (int i = 0; i < height_; ++i) {
		float x = 5.0f;
		for (int j = 0; j < width_; ++j) {
			grid_[i][j] = massSpring_->AddMass(0.01, glm::vec3(x, 3.0f, z));
			x += step_;

			if (j ==  0 && (i % 3 == 0)) grid_[i][j]->SetIsFixed(true);
		}
		z += step_;
	}
	

	//scene 3
	/*
	float z = 8.0f;
	for (int i = 0; i < height_; ++i) {
		float x = 5.0f;
		for (int j = 0; j < width_; ++j) {
			grid_[i][j] = massSpring_->AddMass(0.01, glm::vec3(x, 3.0f, z));
			x += step_;

		}
		z += step_;
	}
	*/

	//scene4
	/*
	float z = 8.0f;
	for (int i = 0; i < height_; ++i) {
		float x = 5.0f;
		for (int j = 0; j < width_; ++j) {
			grid_[i][j] = massSpring_->AddMass(0.03, glm::vec3(x, 3.0f, z));
			x += step_;

			if (j % 5 == 0 || i % 5 == 0) grid_[i][j]->SetIsFixed(true);
		}
		z += step_;
	}
	*/

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

	Init();
}

void Cloth::Update(float dt)
{
	massSpring_->Update(dt);
}

void Cloth::Render()
{	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_QUADS);
	// p1 p2
	// p4 p3
	for (int i = 0; i < height_ - 1; i++) {
		for (int j = 0; j < width_ - 1; j++) {
			auto p1 = grid_[i][j]->GetPosition();
			auto p2 = grid_[i][j + 1]->GetPosition();
			auto p3 = grid_[i + 1][j + 1]->GetPosition();
			auto p4 = grid_[i + 1][j]->GetPosition();
			glTexCoord2f(0.0, 0.0); glVertex3f(p1.x, p1.y, p1.z);
			glTexCoord2f(0.0, 1.0); glVertex3f(p2.x, p2.y, p2.z);
			glTexCoord2f(1.0, 1.0); glVertex3f(p3.x, p3.y, p3.z);
			glTexCoord2f(1.0, 0.0); glVertex3f(p4.x, p4.y, p4.z);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	massSpring_->Render();
}

void Cloth::CheckCollision(Floor *floor, Sphere *sphere)
{
	CheckCollisionWithFloor(floor);
	CheckCollisionWithSphere(sphere);
}

void Cloth::CheckCollisionWithFloor(Floor *floor)
{
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			floor->ResolveCollision(grid_[i][j]);
		}
	}
}

void Cloth::CheckCollisionWithSphere(Sphere *sphere)
{
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			sphere->ResolveCollision(grid_[i][j]);
		}
	}
}

void Cloth::operator=(const Cloth& c)
{
	width_ = c.width_;
	height_ = c.height_;
	step_ = c.step_;
	len_ = c.len_;
	ks_ = c.ks_;
	kd_ = c.kd_;

	for (int i = 0; i < checkImageHeight; ++i) {
		for (int j = 0; j < checkImageWidth; ++j) {
			for (int k = 0; k < 4; ++k) {
				checkImage[i][j][k] = c.checkImage[i][j][k];
			}
		}
	}

	massSpring_ = c.massSpring_;
	grid_ = c.grid_;
}

void Cloth::SetAllUnFixed()
{
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_; ++j) {
			grid_[i][j]->SetIsFixed(false);
		}
	}
}
