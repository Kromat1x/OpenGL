#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateTriangle(std::string name, glm::vec3 center, float length);
	Mesh* CreatePlatform(std::string name, glm::vec3 startingPoint, float length, float width, glm::vec3 color);
	Mesh* CreateAsteroid(std::string name, glm::vec3 centre, float radius, int points, glm::vec3 color);
}

