#pragma once

#include <Component/SimpleScene.h>
#include <include/glm.h>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include "Object3D.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	glm::vec3 unu;
	glm::vec3 doi;
	float a, b;
	Obstacle(glm::vec3 unu, glm::vec3 doi);
};
