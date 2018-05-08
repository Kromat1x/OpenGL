#include "Car.h"
#include "Transform3D.h"
using namespace std;
Car::Car()
{
}


Car::~Car()
{
}

Car::Car(float length, float width, float height, glm::vec3 corner, glm::vec3 color1, glm::vec3 color2, std::string name, std::vector<glm::vec3> wheelsCentre)
{
	this->length = length;
	this->width = width;
	this->height = height;
	this->corner = corner;
	this->color1 = color1;
	this->color2 = color2;
	this->name = name;
	this->speed = 0;
	this->turnedLeft = false;
	this->turnedRight = false;
	this->wheelAngle = 0;
	
	this->centre = glm::vec3(2.25f, 0.2f, 2);
	this->direction = glm::vec3(0, 0, 1);
	this->wheelsCentre = wheelsCentre;
	this->Matrixes.push_back(glm::mat4(1));
	glm::vec3 aux = centre - glm::vec3(0, 0.1f, 0);
	this->collisionPoints.push_back(aux);
	this->collisionPoints.push_back(aux + glm::vec3(-this->width / 2, 0, 0));
	this->collisionPoints.push_back(aux + glm::vec3(this->width / 2, 0, 0));
	this->collisionPoints.push_back(aux + glm::vec3(-this->width / 2, 0, this->length / 2));
	this->collisionPoints.push_back(aux + glm::vec3(this->width / 2, 0, this->length / 2));
	this->collisionPoints.push_back(aux + glm::vec3(-this->width / 2, 0, this->length));
	this->collisionPoints.push_back(aux + glm::vec3(this->width / 2, 0, this->length));
	this->collisionPoints.push_back(aux + glm::vec3(0, 0, this->length));
	for (int i = 1; i < 5; i++) {
		glm::mat4 auxMatrix = glm::mat4(1);
		auxMatrix = Transform3D::Scale(0.1f, 0.05f, 0.1f) * auxMatrix;
		auxMatrix = Transform3D::RotateOZ(M_PI / 2) * auxMatrix;
		glm::vec3 aux = this->wheelsCentre[i - 1];
		auxMatrix = Transform3D::Translate(aux.x, aux.y, aux.z) * auxMatrix;
		this->Matrixes.push_back(auxMatrix);
	}
}

void Car::moveCar()
{
	for (int i = 0; i < 5; i++) {
		this->Matrixes[i] = Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed) * this->Matrixes[i];
	}
	this->centre = glm::vec3(Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed) * glm::vec4(this->centre, 1));
	this->cameraPos = glm::vec3(Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed) * glm::vec4(this->cameraPos, 1));
	this->cameraCentre = glm::vec3(Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed) * glm::vec4(this->cameraCentre, 1));
	this->cameraCentreThirdP = glm::vec3(Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed) * glm::vec4(this->cameraCentreThirdP, 1));
	for (int i = 0; i < 4; i++) {
		this->wheelsCentre[i] = glm::vec3(Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed) * glm::vec4(this->wheelsCentre[i], 1));
	}
	for (int i = 0; i < 8; i++) {
		this->collisionPoints[i] = glm::vec3(Transform3D::Translate(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed)*glm::vec4(this->collisionPoints[i], 1));
	}
}

void Car::turnCar(float angle)
{
	for (int i = 0; i < 5; i++) {
		this->Matrixes[i] = Transform3D::Translate(-this->centre.x, -this->centre.y, -this->centre.z) * this->Matrixes[i];
		this->Matrixes[i] = Transform3D::RotateOY(RADIANS(angle)) * this->Matrixes[i];
		this->Matrixes[i] = Transform3D::Translate(this->centre.x, this->centre.y, this->centre.z) * this->Matrixes[i];
		if (i < 4) {
			this->wheelsCentre[i] = glm::vec3(Transform3D::Translate(-this->centre.x, -this->centre.y, -this->centre.z) * glm::vec4(this->wheelsCentre[i], 1));
			this->wheelsCentre[i] = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(this->wheelsCentre[i], 1));
			this->wheelsCentre[i] = glm::vec3(Transform3D::Translate(this->centre.x, this->centre.y, this->centre.z) * glm::vec4(this->wheelsCentre[i], 1));
		}
	}
	for (int i = 0; i < 8; i++) {
		this->collisionPoints[i] = glm::vec3(Transform3D::Translate(-this->centre.x, -this->centre.y, -this->centre.z) * glm::vec4(this->collisionPoints[i], 1));
		this->collisionPoints[i] = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(this->collisionPoints[i], 1));
		this->collisionPoints[i] = glm::vec3(Transform3D::Translate(this->centre.x, this->centre.y, this->centre.z) * glm::vec4(this->collisionPoints[i], 1));
	}
	this->direction = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(this->direction, 1));
	this->cameraPos = glm::vec3(Transform3D::Translate(-this->centre.x, -this->centre.y, -this->centre.z) * glm::vec4(this->cameraPos, 1));
	this->cameraCentre = glm::vec3(Transform3D::Translate(-this->centre.x, -this->centre.y, -this->centre.z) * glm::vec4(this->cameraCentre, 1));
	this->cameraCentreThirdP = glm::vec3(Transform3D::Translate(-this->centre.x, -this->centre.y, -this->centre.z) * glm::vec4(this->cameraCentreThirdP, 1));
	this->cameraPos = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(this->cameraPos, 1));
	this->cameraCentre = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(this->cameraCentre, 1));
	this->cameraCentreThirdP = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(this->cameraCentreThirdP, 1));
	this->cameraPos = glm::vec3(Transform3D::Translate(this->centre.x, this->centre.y, this->centre.z) * glm::vec4(this->cameraPos, 1));
	this->cameraCentre = glm::vec3(Transform3D::Translate(this->centre.x, this->centre.y, this->centre.z) * glm::vec4(this->cameraCentre, 1));
	this->cameraCentreThirdP = glm::vec3(Transform3D::Translate(this->centre.x, this->centre.y, this->centre.z) * glm::vec4(this->cameraCentreThirdP, 1));
}

void Car::turnWheels(float angle, int a, int b)
{
	//Roti fata 2, 4 la matrici
	//1, 3 la centre
	glm::vec3 savedCentre1 = this->wheelsCentre[a - 1];
	glm::vec3 savedCentre3 = this->wheelsCentre[b - 1];
	this->Matrixes[a] = Transform3D::Translate(-savedCentre1.x, -savedCentre1.y, -savedCentre1.z) * this->Matrixes[a];
	this->Matrixes[b] = Transform3D::Translate(-savedCentre3.x, -savedCentre3.y, -savedCentre3.z) * this->Matrixes[b];
	this->Matrixes[a] = Transform3D::RotateOY(RADIANS(angle)) * this->Matrixes[a];
	this->Matrixes[b] = Transform3D::RotateOY(RADIANS(angle)) * this->Matrixes[b];
	this->Matrixes[a] = Transform3D::Translate(savedCentre1.x, savedCentre1.y, savedCentre1.z) * this->Matrixes[a];
	this->Matrixes[b] = Transform3D::Translate(savedCentre3.x, savedCentre3.y, savedCentre3.z) * this->Matrixes[b];
	this->wheelsCentre[a - 1] = glm::vec3(Transform3D::Translate(-savedCentre1.x, -savedCentre1.y, -savedCentre1.z) * glm::vec4(this->wheelsCentre[a - 1], 1));
	this->wheelsCentre[b - 1] = glm::vec3(Transform3D::Translate(-savedCentre3.x, -savedCentre3.y, -savedCentre3.z) * glm::vec4(this->wheelsCentre[b - 1], 1));
	this->wheelsCentre[a - 1] = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(wheelsCentre[a - 1], 1));
	this->wheelsCentre[b - 1] = glm::vec3(Transform3D::RotateOY(RADIANS(angle)) * glm::vec4(wheelsCentre[b - 1], 1));
	this->wheelsCentre[a - 1] = glm::vec3(Transform3D::Translate(savedCentre1.x, savedCentre1.y, savedCentre1.z) * glm::vec4(this->wheelsCentre[a - 1], 1));
	this->wheelsCentre[b - 1] = glm::vec3(Transform3D::Translate(savedCentre3.x, savedCentre3.y, savedCentre3.z) * glm::vec4(this->wheelsCentre[b - 1], 1));

}

void Car::rotateWheels()
{
	this->turnWheels(-(this->totalAngleWheels + this->totalAngleCar), 2, 4);
	this->turnWheels(-this->totalAngleCar, 1, 3);

	for (int i = 1; i < 5; i++) {
		glm::vec3 savedCentre = this->wheelsCentre[i - 1];
		this->Matrixes[i] = Transform3D::Translate(0, -savedCentre.y, -savedCentre.z) * this->Matrixes[i];
		this->Matrixes[i] = Transform3D::RotateOX(RADIANS(this->wheelAngle)) * this->Matrixes[i];
		this->Matrixes[i] = Transform3D::Translate(0, savedCentre.y, savedCentre.z) * this->Matrixes[i];
	}

	this->turnWheels(this->totalAngleWheels + this->totalAngleCar, 2, 4);
	this->turnWheels(this->totalAngleCar, 1, 3);
}