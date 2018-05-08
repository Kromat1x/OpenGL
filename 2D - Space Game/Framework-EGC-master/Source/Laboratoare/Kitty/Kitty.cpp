#include "Kitty.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Astro.h"

using namespace std;

Kitty::Kitty()
{
}

Kitty::~Kitty()
{
}

void Kitty::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	
	modelMatrix = glm::mat3(1);
	auxTop = glm::vec2(0, 0);
	savedCentre = glm::vec2(0, 0);
	auxCentre = glm::vec2(0, 0);
	trans = glm::vec2(0, 0);
	auxTrans = glm::vec2(0, 0);
	resolution = window->GetResolution();
	top = glm::vec2(length / 2 + 10, sqrt(3) * length / 2);
	centre = glm::vec2((0 + length + length / 2) / 3 + 10, (0 + 0 + sqrt(3) * length / 2) / 3);

	astero1 = Asteroid(glm::vec3(200, 300, 0), 50, "astero1", 8, glm::vec3(1, 0.54902f, 0), glm::mat3(1), false, glm::vec3(200, 300, 0));
	Mesh* astero1mesh = Object2D::CreateAsteroid(astero1.name, astero1.centre, astero1.radius, astero1.points, astero1.color);

	astero2 = Asteroid(glm::vec3(750, 425, 0), 30, "astero2", 10, glm::vec3(0.545098f, 0.270588f, 0.0745098f), glm::mat3(1), false, glm::vec3(750, 425, 0));
	Mesh* astero2mesh = Object2D::CreateAsteroid(astero2.name, astero2.centre, astero2.radius, astero2.points, astero2.color);

	astero3 = Asteroid(glm::vec3(1100, 500, 0), 75, "astero3", 12, glm::vec3(0.862745f, 0.0784314f, 0.235294f), glm::mat3(1), false, glm::vec3(1100, 500, 0));
	Mesh* astero3mesh = Object2D::CreateAsteroid(astero3.name, astero3.centre, astero3.radius, astero3.points, astero3.color);

	asteroids = { &astero1, &astero2, &astero3 };

	Mesh* triangle1 = Object2D::CreateTriangle("triangle1", glm::vec3(10, 0, 0), length);
	kitty = Astro(centre, top, length, "kitty");

	leftBorder = Platform(glm::vec3(0, 0, 0), float(resolution.y), 1.0f, "leftBorder", 2, false);
	rightBorder = Platform(glm::vec3(resolution.x, 0, 0), float(resolution.y), 1.0f, "rightBorder", 2, false);
	topBorder = Platform(glm::vec3(0, resolution.y, 0), 1.0f, float(resolution.x), "topBorder", 2, false);
	bottomBorder = Platform(glm::vec3(0, 0, 0), 1.0f, float(resolution.x), "bottomBorder", 2, false);

	finishLine = Platform(glm::vec3(1100, 150, 0), 10, 100, "platform9", 1, true);

	Mesh* platform9 = Object2D::CreatePlatform(finishLine.name, finishLine.startingPoint, finishLine.width, finishLine.height, glm::vec3(1, 1, 1));
	Mesh* platform3 = Object2D::CreatePlatform(leftBorder.name, leftBorder.startingPoint, leftBorder.width, leftBorder.height, glm::vec3(1, 1, 1));
	Mesh* platform4 = Object2D::CreatePlatform(rightBorder.name, rightBorder.startingPoint, rightBorder.width, rightBorder.height, glm::vec3(1, 1, 1));
	Mesh* platform5 = Object2D::CreatePlatform(topBorder.name, topBorder.startingPoint, topBorder.width, topBorder.height, glm::vec3(1, 1, 1));
	Mesh* platform6 = Object2D::CreatePlatform(bottomBorder.name, bottomBorder.startingPoint, bottomBorder.width, bottomBorder.height, glm::vec3(1, 1, 1));

	platty1 = Platform(glm::vec3(200, 550, 0), 10, 150, "platform1", 1, false);
	Mesh* platform1 = Object2D::CreatePlatform(platty1.name, platty1.startingPoint, platty1.width, platty1.height, glm::vec3(1, 0, 0));

	plattyReflect1 = Platform(glm::vec3(600, 550, 0), 10, 100, "platform2", 2, false);
	Mesh* platform2 = Object2D::CreatePlatform(plattyReflect1.name, plattyReflect1.startingPoint, plattyReflect1.width, plattyReflect1.height, glm::vec3(0, 1, 1));

	platty2 = Platform(glm::vec3(400, 200, 0), 10, 250, "platform7", 1, false);
	Mesh* platform7 = Object2D::CreatePlatform(platty2.name, platty2.startingPoint, platty2.width, platty2.height, glm::vec3(1, 0, 0));

	plattyReflect2 = Platform(glm::vec3(700, 100, 0), 10, 200, "platform8", 2, false);
	Mesh* platform8 = Object2D::CreatePlatform(plattyReflect2.name, plattyReflect2.startingPoint, plattyReflect2.width, plattyReflect2.height, glm::vec3(0, 1, 1));

	platforms = { platty1, plattyReflect1, rightBorder, topBorder, bottomBorder, leftBorder, platty2, plattyReflect2, finishLine};

	AddMeshToList(astero1mesh);
	AddMeshToList(astero2mesh);
	AddMeshToList(astero3mesh);
	AddMeshToList(triangle1);
	AddMeshToList(platform1);
	AddMeshToList(platform2);
	AddMeshToList(platform3);
	AddMeshToList(platform4);
	AddMeshToList(platform5);
	AddMeshToList(platform6);
	AddMeshToList(platform7);
	AddMeshToList(platform8);
	AddMeshToList(platform9);
}

void Kitty::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Kitty::Update(float deltaTimeSeconds)
{
	if (!finish) {

		if (start)
		{
			//Calculul unghiului si activarea lansarii
			float p12 = sqrt(pow(kitty.centre.x - kitty.top.x, 2) + pow(kitty.centre.y - kitty.top.y, 2));
			float p13 = sqrt(pow(kitty.centre.x - trans.x, 2) + pow(kitty.centre.y - trans.y, 2));
			float p23 = sqrt(pow(kitty.top.x - trans.x, 2) + pow(kitty.top.y - trans.y, 2));
			float puteri = pow(p12, 2) + pow(p13, 2) - pow(p23, 2);
			float numitor = (2 * p12 * p13);
			angle = acos(puteri / numitor);

			auxTop.x = kitty.top.x - kitty.centre.x;
			auxTop.y = kitty.top.y - kitty.centre.y;

			float aux1 = auxTop.x;
			float aux2 = auxTop.y;

			auxTop.x = aux1 * cos(angle) - aux2 * sin(angle);
			auxTop.y = aux1 * sin(angle) + aux2 * cos(angle);


			auxTop.x += kitty.centre.x;
			auxTop.y += kitty.centre.y;

			float a = (kitty.centre.y - trans.y) / (kitty.centre.x - trans.x);
			float b = trans.y - a * trans.x;

			if (abs(auxTop.y - a * auxTop.x - b) > 0.2) {
				angle = -angle;
			}
			launch = true;

			savedCentre = kitty.centre;
			//Translatez in centru
			modelMatrix = Transform2D::Translate(-savedCentre.x, -savedCentre.y) *  modelMatrix;

			//Updatez
			kitty.centre.x = 0;
			kitty.centre.y = 0;
			kitty.top.x += -savedCentre.x;
			kitty.top.y += -savedCentre.y;

			//Rotesc
			modelMatrix = Transform2D::Rotate(angle) * modelMatrix;

			//Updatez
			auxCentre.x = kitty.centre.x * cos(angle) - kitty.centre.y * sin(angle);
			auxCentre.y = kitty.centre.x * sin(angle) + kitty.centre.y * cos(angle);

			kitty.centre = auxCentre;

			auxTop.x = kitty.top.x * cos(angle) - kitty.top.y * sin(angle);
			auxTop.y = kitty.top.x * sin(angle) + kitty.top.y * cos(angle);

			kitty.top = auxTop;

			//Translatez la loc in pozitia initiala
			modelMatrix = Transform2D::Translate(savedCentre.x, savedCentre.y) * modelMatrix;

			//Updatez
			kitty.centre.x += savedCentre.x;
			kitty.centre.y += savedCentre.y;
			kitty.top.x += savedCentre.x;
			kitty.top.y += savedCentre.y;

			auxTop = kitty.top;
			savedCentre = kitty.centre;
		}




		if (launch) {
			//Deplasare
			float dx = kitty.top.x - kitty.centre.x;
			float dy = kitty.top.y - kitty.centre.y;
			float nx = dx / sqrt(pow(dx, 2) + pow(dy, 2));
			float ny = dy / sqrt(pow(dx, 2) + pow(dy, 2));
			auxTrans.x = nx * 250 * deltaTimeSeconds;
			auxTrans.y = ny * 250 * deltaTimeSeconds;
			modelMatrix = Transform2D::Translate(auxTrans.x, auxTrans.y) * modelMatrix;
			kitty.top.x += auxTrans.x;
			kitty.top.y += auxTrans.y;
			kitty.centre.x += auxTrans.x;
			kitty.centre.y += auxTrans.y;
			start = false;
		}

		//Collision detection mechanism
		for each (Platform plat in platforms)
		{
			float deltaX = kitty.centre.x - max(plat.startingPoint.x, min(kitty.centre.x, plat.startingPoint.x + plat.width));
			float deltaY = kitty.centre.y - max(plat.startingPoint.y, min(kitty.centre.y, plat.startingPoint.y + plat.height));

			if ((deltaX * deltaX + deltaY * deltaY) < (pow(kitty.length / sqrt(3), 2)) && plat.name != lastCollision) {
				cout << "Collision DETECTED !!! with " << plat.name << endl;
				launch = false;
				lastCollision = plat.name;
				collisionX = max(plat.startingPoint.x, min(kitty.centre.x, plat.startingPoint.x + plat.width));
				collisionY = max(plat.startingPoint.y, min(kitty.centre.y, plat.startingPoint.y + plat.height));

				if (plat.type == 1) {
					modelMatrix = glm::mat3(1);
					kitty.top = glm::vec2(length / 2 + 10, sqrt(3) * length / 2);
					kitty.centre = glm::vec2((0 + length + length / 2) / 3 + 10, (0 + 0 + sqrt(3) * length / 2) / 3);
					//Platforma de stationare
					launch = false;
					//collision = true;
					topOrBottomX = -(kitty.length / 2 + 10);
					topOrBottomY = 0;
					savedCentre = kitty.centre;
					if (collisionY < plat.startingPoint.y + plat.height) {
						topOrBottomX = -(kitty.length / 2 + 10);
						topOrBottomY = - kitty.length / float(sqrt(3));

						//Translatez in centru
						modelMatrix = Transform2D::Translate(-savedCentre.x, -savedCentre.y) *  modelMatrix;

						//Updatez
						kitty.centre.x += -savedCentre.x;
						kitty.centre.y += -savedCentre.y;
						kitty.top.x += -savedCentre.x;
						kitty.top.y += -savedCentre.y;

						//Rotesc
						modelMatrix = Transform2D::Rotate(float(M_PI)) * modelMatrix;

						//Updatez
						auxCentre.x = kitty.centre.x * cos(float(M_PI)) - kitty.centre.y * sin(float(M_PI));
						auxCentre.y = kitty.centre.x * sin(float(M_PI)) + kitty.centre.y * cos(float(M_PI));

						kitty.centre = auxCentre;

						auxTop.x = kitty.top.x * cos(float(M_PI)) - kitty.top.y * sin(float(M_PI));
						auxTop.y = kitty.top.x * sin(float(M_PI)) + kitty.top.y * cos(float(M_PI));

						kitty.top = auxTop;

						//Translatez la loc in pozitia initiala
						modelMatrix = Transform2D::Translate(savedCentre.x, savedCentre.y) * modelMatrix;

						//Updatez
						kitty.centre.x += savedCentre.x;
						kitty.centre.y += savedCentre.y;
						kitty.top.x += savedCentre.x;
						kitty.top.y += savedCentre.y;

					}
					modelMatrix = Transform2D::Translate(collisionX + topOrBottomX, collisionY + topOrBottomY) * modelMatrix;
					kitty.centre.x += collisionX + topOrBottomX;
					kitty.centre.y += collisionY + topOrBottomY;
					kitty.top.x += collisionX + topOrBottomX;
					kitty.top.y += collisionY + topOrBottomY;
					centre.x = collisionX;
					centre.y = collisionY;
					if (plat.finish) {
						finish = true;
						cout << "YOU WON !!! CONGRATS !!!" << endl;
					}
				}
				else if (plat.type == 2) {
					modelMatrix = glm::mat3(1);
					kitty.top = glm::vec2(length / 2 + 10, sqrt(3) * length / 2);
					kitty.centre = glm::vec2((0 + length + length / 2) / 3 + 10, (0 + 0 + sqrt(3) * length / 2) / 3);
					//Platforma de stationare
					launch = false;
					//collision = true;
					topOrBottomX = -(kitty.length / 2 + 10);
					topOrBottomY = 0;
					savedCentre = kitty.centre;
					if (collisionY < plat.startingPoint.y + plat.height) {
						topOrBottomX = -(kitty.length / 2 + 10);
						topOrBottomY = -kitty.length / float(sqrt(3));

						//Translatez in centru
						modelMatrix = Transform2D::Translate(-savedCentre.x, -savedCentre.y) *  modelMatrix;

						//Updatez
						kitty.centre.x += -savedCentre.x;
						kitty.centre.y += -savedCentre.y;
						kitty.top.x += -savedCentre.x;
						kitty.top.y += -savedCentre.y;

						//Rotesc
						modelMatrix = Transform2D::Rotate(float(M_PI)) * modelMatrix;

						//Updatez
						auxCentre.x = kitty.centre.x * cos(float(M_PI)) - kitty.centre.y * sin(float(M_PI));
						auxCentre.y = kitty.centre.x * sin(float(M_PI)) + kitty.centre.y * cos(float(M_PI));

						kitty.centre = auxCentre;

						auxTop.x = kitty.top.x * cos(float(M_PI)) - kitty.top.y * sin(float(M_PI));
						auxTop.y = kitty.top.x * sin(float(M_PI)) + kitty.top.y * cos(float(M_PI));

						kitty.top = auxTop;

						//Translatez la loc in pozitia initiala
						modelMatrix = Transform2D::Translate(savedCentre.x, savedCentre.y) * modelMatrix;

						//Updatez
						kitty.centre.x += savedCentre.x;
						kitty.centre.y += savedCentre.y;
						kitty.top.x += savedCentre.x;
						kitty.top.y += savedCentre.y;

					}
					modelMatrix = Transform2D::Translate(collisionX + topOrBottomX, collisionY + topOrBottomY) * modelMatrix;
					kitty.centre.x += collisionX + topOrBottomX;
					kitty.centre.y += collisionY + topOrBottomY;
					kitty.top.x += collisionX + topOrBottomX;
					kitty.top.y += collisionY + topOrBottomY;



					if (plat.name == "leftBorder" || plat.name == "rightBorder") {
						trans.x = centre.x;
						trans.y = collisionY * 2 - centre.y;
						start = true;
						centre.x = collisionX;
						centre.y = collisionY;
					}
					else {
						trans.y = centre.y;
						trans.x = collisionX * 2 - centre.x;
						start = true;
						centre.x = collisionX;
						centre.y = collisionY;
					}
				}
			}
		}


		for each (Asteroid* astr in asteroids) {
			float dx = kitty.centre.x - astr->centre.x;
			float dy = kitty.centre.y - astr->centre.y;

			float dist = sqrt(pow(dx, 2) + pow(dy, 2));
			if (dist < kitty.length / sqrt(3) + astr->radius && lastCollision != astr->name && !astr->destroyed) {
				cout << "Collision Detected - Asteroid !!! " << astr->name << endl;
				lastCollision = astr->name;
				astr->destroyed = true;
				collision = true;

				float a = (astr->centre.y - kitty.centre.y) / (astr->centre.x - kitty.centre.x);
				float c = kitty.centre.y - a * kitty.centre.x;

				float d = (centre.x + (centre.y - c) * a) / (1 + pow(a, 2));
				glm::vec3 newPoint = glm::vec3(2 * d - centre.x, 2 * d * a - centre.y + 2 * c, 0);

				trans.x = newPoint.x;
				trans.y = newPoint.y;
				start = true;
				centre.x = kitty.centre.x;
				centre.y = kitty.centre.y;
			}
		}
	}

	for each(Asteroid* astr in asteroids) {
		
		if (!astr->destroyed) {
			if (astr->name == "astero1") {
				astr->modelMatrix = glm::mat3(1);
				//Translate -> translateFactor
				count++;
				if (count % 650 < 325) {
					direction = 1;
				}
				else {
					direction = -1;
				}
				float aux = direction * deltaTimeSeconds * 50;
				translateFactor.x += aux;
				translateFactor.y += aux;
				astr->modelMatrix *= Transform2D::Translate(translateFactor.x, translateFactor.y);
				astr->centre.x += aux;
				astr->centre.y += aux;
			}
			else if (astr->name == "astero2") {
				//Rotate -> rotationAngle
				astr->modelMatrix = glm::mat3(1);
				rotationAngle += deltaTimeSeconds;
				astr->modelMatrix = Transform2D::Translate(-650, -375) * astr->modelMatrix;
				astr->centre.x = astr->savedCentre.x;
				astr->centre.y = astr->savedCentre.y;
				astr->centre.x -= 650;
				astr->centre.y -= 375;
				astr->modelMatrix = Transform2D::Rotate(rotationAngle) * astr->modelMatrix;
				float aux1 = astr->centre.x * cos(rotationAngle) - astr->centre.y * sin(rotationAngle);
				float aux2 = astr->centre.x * sin(rotationAngle) + astr->centre.y * cos(rotationAngle);
				astr->centre.x = aux1;
				astr->centre.y = aux2;
				astr->modelMatrix = Transform2D::Translate(650, 375) * astr->modelMatrix;
				astr->centre.x += 650;
				astr->centre.y += 375;


			}
			else {
				//Scale -> scaleFactor
				count++;
				if (count % 100 < 50) {
					scaleFactor.x = 1.01f;
					scaleFactor.y = 1.01f;
				}
				else {
					scaleFactor.x = 1 / 1.01f;
					scaleFactor.y = 1 / 1.01f;
				}

				astr->modelMatrix = Transform2D::Translate(-1100, -500) * astr->modelMatrix;
				astr->modelMatrix = Transform2D::Scale(scaleFactor.x, scaleFactor.y) * astr->modelMatrix;
				astr->radius *= scaleFactor.x;
				astr->modelMatrix = Transform2D::Translate(1100, 500) * astr->modelMatrix;
			}
			RenderMesh2D(meshes[astr->name], shaders["VertexColor"], astr->modelMatrix);
		}
	}
	
	for each(Platform platty in platforms) {
		RenderMesh2D(meshes[platty.name], shaders["VertexColor"], glm::mat3(1));
	}
	RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
}

void Kitty::FrameEnd()
{

}

void Kitty::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Kitty::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Kitty::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Kitty::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Kitty::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		trans.x = (float) mouseX;
		glm::ivec2 resolution = window->GetResolution();
		trans.y = abs((float)mouseY - resolution.y);
		centre.x = kitty.centre.x;
		centre.y = kitty.centre.y;
		start = true;
		collision = false;
	}
}

void Kitty::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Kitty::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Kitty::OnWindowResize(int width, int height)
{
}
