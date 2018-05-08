#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{
	Mesh* CreateRect(std::string name, glm::vec3 leftBottomCorner, float length, float width, float height, glm::vec3 color1, glm::vec3 color2);
	Mesh* CreateRect3(std::string name, glm::vec3 leftBottomCorner, float length, float width, float height, glm::vec3 color);
	Mesh* CreateRect2(std::string name, glm::vec3 pct1, glm::vec3 pct2, glm::vec2 add1, glm::vec2 add2, glm::vec3 color);
	Mesh* CreateCircuit(std::string name, glm::vec3 start, glm::vec3 color, float width, float length);
	Mesh* CreatePara(std::string name, glm::vec3 pct1, glm::vec3 pct2, glm::vec2 add1, glm::vec2 add2, glm::vec3 color);

}