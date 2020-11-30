#include <windows.h>
#include <vector>
#include <string>

#include <gl/glut.h>
#include "massspring.h"
#include "pointmass.h"
#include "spring.h"
#include "camera.h"
#include "simulation.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int WINDOW_WIDTH = 720;
const int WINDOW_HEIGHT = 720;

//MassSpring massSpring;
Simulation simulation;
Camera camera;

bool pressedKey[256];

unsigned int textureID;

void Initialize()
{
	simulation = Simulation();
	camera = Camera(glm::vec3(9.0, 3.3, 16.1), glm::vec3(-0.63, -0.25, -0.72));

}

void DrawCube() {
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);

	// draw xz plane grid
	float spacing = 0.25;
	int yLines = 120;
	int zLines = 120;
	float height = (float)yLines * spacing;
	float width = (float)zLines * spacing;

	float z = spacing;
	glLineWidth(1.0);
	glColor4f(0.5, 1.0, 0.5, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < yLines; i++) {
		glVertex3f(0.0, 0.0, z);
		glVertex3f(width, 0.0, z);
		z += spacing;
	}

	float x = spacing;
	for (int i = 0; i < zLines; i++) {
		glVertex3f(x, 0.0, 0.0);
		glVertex3f(x, 0.0, height);
		x += spacing;
	}
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void UpdateCamera(float dt) {
	float camSpeed = 10.0;
	float camRotSpeed = 0.05;
	float sphereSpeed = 4.0f;
	//float sphereSpeed = 0.75f;

	if (pressedKey['w']) { camera.Forward(camSpeed * dt); }
	if (pressedKey['s']) { camera.Backward(camSpeed * dt); }
	if (pressedKey['a']) { camera.Left(camSpeed * dt); }
	if (pressedKey['d']) { camera.Right(camSpeed * dt); }
	if (pressedKey['q']) { camera.RotateLeft(camSpeed * dt); }
	if (pressedKey['e']) { camera.RotateRight(camSpeed * dt); }
	if (pressedKey['r']) { camera.RotateUp(camSpeed * dt); }
	if (pressedKey['f']) { camera.RotateDown(camSpeed * dt); }
	if (pressedKey['t']) { camera.RollLeft(camSpeed * dt); }
	if (pressedKey['g']) { camera.RollRight(camSpeed * dt); }

	if (pressedKey['z']) { simulation.MoveSphereNX(sphereSpeed * dt); }
	if (pressedKey['x']) { simulation.MoveSpherePX(sphereSpeed * dt); }
	if (pressedKey['c']) { simulation.MoveSphereNZ(sphereSpeed * dt); }
	if (pressedKey['v']) { simulation.MoveSpherePZ(sphereSpeed * dt); }
}

void PollKeyboard(unsigned char key, int x, int y)
{
	printf("%f %f %f\n", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	printf("%f %f %f\n", camera.GetDirection().x, camera.GetDirection().y, camera.GetDirection().z);

	pressedKey[key] = true;
	if (key == '.') {
		simulation.SetAllUnFixed();
	}
	glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y)
{
	pressedKey[key] = false;
}

void UpdatePerspective() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * WINDOW_WIDTH / WINDOW_HEIGHT, 0.5, 100.0);

	float px = camera.GetPosition().x;
	float py = camera.GetPosition().y;
	float pz = camera.GetPosition().z;
	gluLookAt(px, py, pz, px + camera.GetDirection().x,
		py + camera.GetDirection().y, pz + camera.GetDirection().z,
		camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);
}

void Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-30.0f, 30.0f, -30.0f, 30.0f);

	UpdatePerspective();

	simulation.Render();

	glutSwapBuffers();
}

void Update(int value)
{
	UpdateCamera(0.003f);

	simulation.Update();

	glutPostRedisplay();
	glutTimerFunc(10, Update, 0);
}

int main(int argc, char** argv)
{
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInit(&argc, argv);
	glutCreateWindow("Deformable-Rigidbody Simulation");

	Initialize();

	glutTimerFunc(10, Update, 0);
	glutDisplayFunc(Render);
	glutKeyboardUpFunc(KeyUp);
	glutKeyboardFunc(PollKeyboard);
	glutMainLoop();
	return 0;
}