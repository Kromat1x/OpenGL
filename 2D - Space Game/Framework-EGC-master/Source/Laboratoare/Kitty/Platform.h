#pragma once

#include <Component/SimpleScene.h>
#include <include/glm.h>
#include <string>
#include <Core/Engine.h>

class Platform
{
public:
	Platform();
	~Platform();
	glm::vec3 startingPoint;
	float width;
	float height;
	int type;
	std::string name;
	bool finish;
	Platform(glm::vec3 startingPoint, float height, float width, std::string name, int type, bool finish);
};