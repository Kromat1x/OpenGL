#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Astro.h"
#include "Platform.h"
#include "Asteroid.h"

class Kitty : public SimpleScene
{
	public:
		Kitty();
		~Kitty();
		int count = 0;
		int direction;
		float angle, collisionX, collisionY, topOrBottomX, topOrBottomY;
		bool start, launch, collision, finish;
		float length = 25.0;
		float rotationAngle = 0;
		glm::vec2 scaleFactor = glm::vec2(1, 1);
		glm::vec2 translateFactor = glm::vec2(1, 1);
		glm::vec2 auxTrans, auxCentre, savedCentre, trans, centre, auxTop, top;
		std::vector<Platform> platforms;
		std::vector<Asteroid*> asteroids;
		glm::mat3 modelMatrixAux;
		Astro kitty;
		std::string lastCollision = "bottomBorder";
		Platform platty1, topBorder, bottomBorder, leftBorder, rightBorder, plattyReflect1, platty2, plattyReflect2, finishLine;
		Asteroid astero1, astero2, astero3;
		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
};
