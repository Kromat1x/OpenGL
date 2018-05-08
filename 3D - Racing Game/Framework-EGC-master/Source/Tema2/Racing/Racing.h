#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include "Object3D.h"
#include "Transform3D.h"
#include "Car.h"
#include "Obstacle.h"
class Racing : public SimpleScene
{
	public:
		Racing();
		~Racing();
		std::vector<std::string> names;
		int count = 0;
		Car* myCar;
		bool freeCam = false;
		bool timeBend = false;
		float time = 26;
		int score;
		int gameTimer;
		bool gameOver;
		bool scoreShown;
		bool scoreDec;
		int lastCollisionTimer;
		bool canMakeCollision;
		std::vector<Obstacle> obs;
		bool collisionFront = false;
		bool collisionRear = false;
		bool collision = false;
		bool thirdPersCamera;
		glm::vec3 connectionPoint;
		float wheelAngleTurn = 15;
		float initialLength = 1.25f;
		float initialWidth = 0.5f;
		float initialX = 2;
		float initialY = 0.2f;
		float initialZ = 2;
		float height = 0.15f;
		GLenum polygonMode;
		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
};
