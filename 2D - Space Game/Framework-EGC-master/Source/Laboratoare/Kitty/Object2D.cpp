#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 center, float length)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, glm::vec3(0, 0, 1)),
		VertexFormat(center + glm::vec3(length, 0, 0), glm::vec3(0, 1, 0)),
		VertexFormat(center + glm::vec3(length / 2, sqrt(3)* length / 2, 0), glm::vec3(1, 0, 0))
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };
	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreatePlatform(std::string name, glm::vec3 startingPoint, float width, float height, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(startingPoint, color),
		VertexFormat(startingPoint + glm::vec3(width, 0, 0), color),
		VertexFormat(startingPoint + glm::vec3(width,height, 0), color),
		VertexFormat(startingPoint + glm::vec3(0, height, 0), color)
		
	};

	Mesh* platform = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	platform->SetDrawMode(GL_POLYGON);

	platform->InitFromData(vertices, indices);
	return platform;
}

Mesh* Object2D::CreateAsteroid(std::string name, glm::vec3 centre, float radius, int points, glm::vec3 color)
{
	std::vector<VertexFormat> vertices = {};
	std::vector<unsigned short> indices = {};
	glm::vec3 top = glm::vec3(centre.x, centre.y + radius, 0);
	glm::vec3 newPoint = top;

	float angle = float(M_PI) * 2 / points;

	for (int i = 0; i < points; i++) {

		vertices.push_back(VertexFormat(newPoint, color));
		glm::vec3 saved = newPoint;

		float auxX;
		float auxY;

		newPoint.x += -centre.x;
		newPoint.y += -centre.y;

		auxX = newPoint.x * cos(angle) - newPoint.y * sin(angle);
		auxY = newPoint.x * sin(angle) + newPoint.y * cos(angle);

		newPoint = glm::vec3(auxX, auxY, 0);

		newPoint.x += centre.x;
		newPoint.y += centre.y;
		indices.push_back(i);
	}

	Mesh* astero = new Mesh(name);
	astero->SetDrawMode(GL_POLYGON);

	astero->InitFromData(vertices, indices);
	return astero;

}
