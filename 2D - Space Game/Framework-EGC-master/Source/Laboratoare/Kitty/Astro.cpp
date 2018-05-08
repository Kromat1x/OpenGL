#include "Astro.h"



Astro::Astro()
{
}


Astro::~Astro()
{
}

Astro::Astro(glm::vec2 centre, glm::vec2 top, float length, std::string name)
{
	this->centre = centre;
	this->top = top;
	this->length = length;
	this->name = name;
}
