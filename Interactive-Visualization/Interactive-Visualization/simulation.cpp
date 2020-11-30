#include "simulation.h"

Simulation::Simulation()
{
	GLfloat ambient[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat diffuse[] = { 0.7, 0.7, 0.7, 1 };
	GLfloat matSpecular[] = { 1, 1, 1, 1 };
	GLfloat matShininess[] = { 128 };

	GLfloat lightPosition[] = { 1, 5, 7, 0 };
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, matSpecular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	//scene1
	cloth_ = new Cloth(12, 18, 0.3f, 0.33f, 25.0f, 0.05f);
	sphere_ = new Sphere(glm::vec3(5, 1, 12), 1.0f, 36, 36);

	//scene2 : camera vel 0.5
	//cloth_ = new Cloth(12, 20, 0.3f, 0.25f, 25.0f, 0.05f);
	//sphere_ = new Sphere(glm::vec3(8, 1.5, 12), 0.5f, 36, 36);

	//scene3 cloth revision
	//cloth_ = new Cloth(12, 20, 0.3f, 0.25f, 25.0f, 0.05f);
	//sphere_ = new Sphere(glm::vec3(5.2, 1.0, 11.5), 1.0f, 36, 36);

	//scene4 cloth vertical speed 1/150
	//cloth_ = new Cloth(20, 20, 0.3f, 0.25f, 20.0f, 0.1f);
	//sphere_ = new Sphere(glm::vec3(50.2, 1.0, 11.5), 1.0f, 36, 36);
	floor_ = new Floor(glm::vec3(0, 0, 0), 20.0f);
}

void Simulation::MoveSpherePX(float d)
{
	sphere_->MovePX(d);
}

void Simulation::MoveSphereNX(float d)
{
	sphere_->MoveNX(d);
}

void Simulation::MoveSpherePZ(float d)
{
	sphere_->MovePZ(d);
}

void Simulation::MoveSphereNZ(float d)
{
	sphere_->MoveNZ(d);
}

void Simulation::CheckCollision(Floor *floor, Sphere *sphere)
{
	cloth_->CheckCollision(floor, sphere);
}

void Simulation::SetAllUnFixed()
{
	cloth_->SetAllUnFixed();
}

void Simulation::Update()
{
	CheckCollision(floor_, sphere_);
	cloth_->Update(1.0f / 150);
}

void Simulation::Render()
{
	floor_->Render();
	sphere_->Render();
	cloth_->Render();
}


