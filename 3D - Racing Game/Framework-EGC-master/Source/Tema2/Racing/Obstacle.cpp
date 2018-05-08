#include "Obstacle.h"

using namespace std;
Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

Obstacle::Obstacle(glm::vec3 unu, glm::vec3 doi)
{
	this->unu = unu;
	this->doi = doi;

	if (this->doi.x == this->unu.x) {
		this->a = 0;
	}
	else {
		this->a = (this->doi.z - this->unu.z) / (this->doi.x - this->unu.x);
	}

	this->b = this->unu.z - this->a;
}