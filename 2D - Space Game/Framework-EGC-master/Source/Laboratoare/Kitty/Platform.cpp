#include "Platform.h"



Platform::Platform()
{
}


Platform::~Platform()
{
}

Platform::Platform(glm::vec3 startingPoint, float height, float width, std::string name, int type, bool finish)
{
	this->finish = finish;
	this->startingPoint = startingPoint;
	this->width = width;
	this->type = type;
	this->height = height;
	this->name = name;
}