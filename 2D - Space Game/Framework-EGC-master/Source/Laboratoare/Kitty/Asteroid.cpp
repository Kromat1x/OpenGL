#include "Asteroid.h"



Asteroid::Asteroid()
{
}


Asteroid::~Asteroid()
{
}

Asteroid::Asteroid(glm::vec3 centre, float radius, std::string name, int points, glm::vec3 color, glm::mat3 modelMatrix, bool destroyed, glm::vec3 savedCentre)
{
	this->savedCentre = savedCentre;
	this->centre = centre;
	this->radius = radius;
	this->points = points;
	this->name = name;
	this->destroyed = destroyed;
	this->color = color;
	this->modelMatrix = modelMatrix;
}