#include "Object3D.h"

#include <Core/Engine.h>

Mesh * Object3D::CreateRect(std::string name, glm::vec3 leftBottomCorner, float length, float width, float height, glm::vec3 color1, glm::vec3 color2)
{
	glm::vec3 leftBottomCornerUp = leftBottomCorner + glm::vec3(0.05f, height, 0.05f);
	float lengthUp = length - 0.5f;
	float widthUp = width - 0.1f;
	float heightUp = height - 0.05f;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(leftBottomCorner, color1),//0
		VertexFormat(leftBottomCorner + glm::vec3(width, 0, 0), color1),//1
		VertexFormat(leftBottomCorner + glm::vec3(width, 0, length), color1),//2
		VertexFormat(leftBottomCorner + glm::vec3(0, 0, length), color1),//3
		VertexFormat(leftBottomCorner + glm::vec3(0, height, 0), color1),//4
		VertexFormat(leftBottomCorner + glm::vec3(width, height, 0), color1),//5
		VertexFormat(leftBottomCorner + glm::vec3(width, height, length), color1),//6
		VertexFormat(leftBottomCorner + glm::vec3(0, height, length), color1),//7
		VertexFormat(leftBottomCornerUp, color2),//8
		VertexFormat(leftBottomCornerUp + glm::vec3(widthUp, 0, 0), color2),//9
		VertexFormat(leftBottomCornerUp + glm::vec3(widthUp, 0, lengthUp), color2),//10
		VertexFormat(leftBottomCornerUp + glm::vec3(0, 0, lengthUp), color2),//11
		VertexFormat(leftBottomCornerUp + glm::vec3(0, heightUp, 0), color2),//12
		VertexFormat(leftBottomCornerUp + glm::vec3(widthUp, heightUp, 0), color2),//13
		VertexFormat(leftBottomCornerUp + glm::vec3(widthUp, heightUp, lengthUp), color2),//14
		VertexFormat(leftBottomCornerUp + glm::vec3(0, heightUp, lengthUp), color2),//15
	};
	
	Mesh* rect = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 5, 0, 4, 5, 0, 1, 2, 0, 3, 2, 1, 6, 2, 1, 5, 6, 0, 7, 3, 0, 4, 7, 3, 6, 2, 3, 6, 7, 4, 5, 6, 4, 7, 6,
											8, 9, 13, 8, 12, 13, 8, 9, 10, 8, 11, 10, 9, 14, 10, 9, 13, 14, 8, 15, 11, 8, 12, 15, 11, 14, 10, 11, 14, 15, 12, 13, 14, 12, 15, 14};
	rect->SetDrawMode(GL_TRIANGLES);
	rect->InitFromData(vertices, indices);
	return rect;

}

Mesh * Object3D::CreateRect3(std::string name, glm::vec3 leftBottomCorner, float length, float width, float height, glm::vec3 color)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(leftBottomCorner, color),//0
		VertexFormat(leftBottomCorner + glm::vec3(width, 0, 0), color),//1
		VertexFormat(leftBottomCorner + glm::vec3(width, 0, length), color),//2
		VertexFormat(leftBottomCorner + glm::vec3(0, 0, length), color),//3
		VertexFormat(leftBottomCorner + glm::vec3(0, height, 0), color),//4
		VertexFormat(leftBottomCorner + glm::vec3(width, height, 0), color),//5
		VertexFormat(leftBottomCorner + glm::vec3(width, height, length), color),//6
		VertexFormat(leftBottomCorner + glm::vec3(0, height, length), color)//7
	};

	Mesh* rect = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 5, 0, 4, 5, 0, 1, 2, 0, 3, 2, 1, 6, 2, 1, 5, 6, 0, 7, 3, 0, 4, 7, 3, 6, 2, 3, 6, 7, 4, 5, 6, 4, 7, 6 };
	rect->SetDrawMode(GL_TRIANGLES);
	rect->InitFromData(vertices, indices);
	return rect;
}

Mesh * Object3D::CreateRect2(std::string name, glm::vec3 pct1, glm::vec3 pct2, glm::vec2 add1, glm::vec2 add2, glm::vec3 color)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(pct1, color),
		VertexFormat(pct2, color),
		VertexFormat(pct2 + glm::vec3(add1.x, 0, add1.y), color),
		VertexFormat(pct1 + glm::vec3(add2.x, 0, add2.y), color),
		VertexFormat(pct1 + glm::vec3(0, 0.1f, 0), color),
		VertexFormat(pct2 + glm::vec3(0, 0.1f, 0), color),
		VertexFormat(pct2 + glm::vec3(add1.x, 0.1f, add1.y), color),
		VertexFormat(pct1 + glm::vec3(add2.x, 0.1f, add2.y), color)

	};

	Mesh* rect = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 5, 0, 4, 5, 0, 1, 2, 0, 3, 2, 1, 6, 2, 1, 5, 6, 0, 7, 3, 0, 4, 7, 3, 6, 2, 3, 6, 7, 4, 5, 6, 4, 7, 6 };
	rect->SetDrawMode(GL_TRIANGLES);
	rect->InitFromData(vertices, indices);
	return rect;

}

Mesh * Object3D::CreateCircuit(std::string name, glm::vec3 start, glm::vec3 color, float width, float length)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(start, color),//0
		VertexFormat(start + glm::vec3(width, 0, 0), color),//1
		VertexFormat(start + glm::vec3(0, 0, length), color),//2
		VertexFormat(start + glm::vec3(width, 0, length), color),//3

	};
	Mesh* street = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 1, 2, 3};
	street->SetDrawMode(GL_TRIANGLES);
	street->InitFromData(vertices, indices);
	return street;

}

Mesh * Object3D::CreatePara(std::string name, glm::vec3 pct1, glm::vec3 pct2, glm::vec2 add1, glm::vec2 add2, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(pct1, color),
		VertexFormat(pct2, color),
		VertexFormat(pct2 + glm::vec3(add1.x, 0, add1.y), color),
		VertexFormat(pct1 + glm::vec3(add2.x, 0, add2.y), color)
	};

	Mesh* para = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 0, 2, 3 };
	para->SetDrawMode(GL_TRIANGLES);
	para->InitFromData(vertices, indices);
	return para;
}
