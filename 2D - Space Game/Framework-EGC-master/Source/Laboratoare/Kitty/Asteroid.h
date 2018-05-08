#pragma once

#include <Component/SimpleScene.h>
#include <include/glm.h>
#include <string>
#include <Core/Engine.h>

class Asteroid
{
public:
	Asteroid();
	~Asteroid();
	glm::vec3 centre;
	float radius;
	bool destroyed;
	int points;
	glm::vec3 savedCentre;
	glm::vec3 color;
	std::string name;
	glm::mat3 modelMatrix;
	Asteroid(glm::vec3 centre, float radius, std::string name, int points, glm::vec3 color, glm::mat3 modelMatrix, bool destroyed, glm::vec3 savedCentre);
};