#pragma once

#include <Component/SimpleScene.h>
#include <include/glm.h>
#include <string>
#include <Core/Engine.h>

class Astro
{
public:
	Astro();
	~Astro();
	glm::vec2 centre;
	glm::vec2 top;
	float length;
	std::string name;
	Astro(glm::vec2 centre, glm::vec2 top, float length, std::string name);
};