#pragma once

#include <Component/SimpleScene.h>
#include <include/glm.h>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include "Object3D.h"

class Car
{
public:
	Car();
	~Car();
	float length;
	float width;
	float height;
	float speed;
	float wheelAngle;
	float totalAngleCar = 0;
	float totalAngleWheels = 0;
	bool turnedLeft;
	bool turnedRight;
	glm::vec3 corner;
	glm::vec3 color1;
	glm::vec3 color2;
	glm::vec3 direction;
	glm::vec3 centre;
	glm::vec3 cameraPos;
	glm::vec3 cameraCentre;
	glm::vec3 cameraCentreThirdP;
	std::vector<Mesh*> meshes;
	std::vector<glm::vec3> collisionPoints;
	std::vector<glm::vec3> wheelsCentre;
	std::vector<glm::mat4> Matrixes;
	std::string name;
	Car(float length, float width, float height, glm::vec3 corner, glm::vec3 color1, glm::vec3 color2, std::string name, std::vector<glm::vec3> wheelsCentre);
	void moveCar();
	void turnCar(float angle);
	void turnWheels(float angle, int a, int b);
	void rotateWheels();
};