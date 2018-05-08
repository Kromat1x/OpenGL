#include "Racing.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Object3D.h"
using namespace std;

Racing::Racing()
{
}

Racing::~Racing()
{
}

void Racing::Init()
{

	{
		Shader *shader1 = new Shader("SkyShader");
		shader1->AddShader("Source/Tema2/Racing/SkyVertex.glsl", GL_VERTEX_SHADER);
		shader1->AddShader("Source/Tema2/Racing/SkyFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader1->CreateAndLink();
		shaders[shader1->GetName()] = shader1;
	}

	{
		Shader *shader2 = new Shader("SkyShader2");
		shader2->AddShader("Source/Tema2/Racing/SkyVertex2.glsl", GL_VERTEX_SHADER);
		shader2->AddShader("Source/Tema2/Racing/SkyFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader2->CreateAndLink();
		shaders[shader2->GetName()] = shader2;
	}

	{
		Shader *shader3 = new Shader("SkyShader3");
		shader3->AddShader("Source/Tema2/Racing/SkyVertex3.glsl", GL_VERTEX_SHADER);
		shader3->AddShader("Source/Tema2/Racing/SkyFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader3->CreateAndLink();
		shaders[shader3->GetName()] = shader3;
	}

	renderCameraTarget = false;
	time = 0;
	lastCollisionTimer = 0;
	polygonMode = GL_FILL;
	score = 0;
	canMakeCollision = true;
	gameTimer = 0;
	gameOver = false;
	scoreShown = false;
	scoreDec = false;
	std::vector<glm::vec3> wheelsCentreAux;
	
	wheelsCentreAux.push_back(glm::vec3(1.95f, 0.2f, 2.2f));
	wheelsCentreAux.push_back(glm::vec3(1.95f, 0.2f, 2 + initialLength - 0.2f));
	wheelsCentreAux.push_back(glm::vec3(2.05f + initialWidth, 0.2f, 2.2f));
	wheelsCentreAux.push_back(glm::vec3(2.05f + initialWidth, 0.2f, 2 + initialLength - 0.2f));

	myCar = new Car(1.25f, 0.5f, 0.15f, glm::vec3(2, 0.2f, 2), glm::vec3(1, 0.270588f, 0), glm::vec3(0.517647f, 0.439216f, 1), "myCar", wheelsCentreAux);

	//Obstacole
	{
		Mesh* obs1 = Object3D::CreateRect3("obs1", glm::vec3(2.25f, 0.1f, 5.45f), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs1->GetMeshID()] = obs1;
		glm::vec3 aux = glm::vec3(2.25f, 0.1f, 5.45f);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs2 = Object3D::CreateRect3("obs2", glm::vec3(-1.34f, 0.1f, 12), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs2->GetMeshID()] = obs2;
		aux = glm::vec3(-1.34f, 0.1f, 12);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs3 = Object3D::CreateRect3("obs3", glm::vec3(-12.7f, 0.1f, 13.5f), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs3->GetMeshID()] = obs3;
		aux = glm::vec3(-12.7f, 0.1f, 13.5f);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs4 = Object3D::CreateRect3("obs4", glm::vec3(-21.8f, 0.1f, 9), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs4->GetMeshID()] = obs4;
		aux = glm::vec3(-21.8f, 0.1f, 9);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs5 = Object3D::CreateRect3("obs5", glm::vec3(-17.4f, 0.1f, 2.4f), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs5->GetMeshID()] = obs5;
		aux = glm::vec3(-17.4f, 0.1f, 2.4f);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs6 = Object3D::CreateRect3("obs6", glm::vec3(-10.5f, 0.1f, 0.4f), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs6->GetMeshID()] = obs6;
		aux = glm::vec3(-10.5f, 0.1f, 0.4f);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs7 = Object3D::CreateRect3("obs7", glm::vec3(-4.3f, 0.1f, -4.8f), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs7->GetMeshID()] = obs7;
		aux = glm::vec3(-4.3f, 0.1f, -4.8f);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));

		Mesh* obs8 = Object3D::CreateRect3("obs8", glm::vec3(1.4f, 0.1f, -6.5f), 0.25f, 0.25f, 0.5f, glm::vec3(1, 0, 0));
		meshes[obs8->GetMeshID()] = obs8;
		aux = glm::vec3(1.4f, 0.1f, -6.5f);
		obs.push_back(Obstacle(aux, aux + glm::vec3(0, 0, 0.25f)));
		obs.push_back(Obstacle(aux, aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0.25f, 0, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux + glm::vec3(0, 0.25f, 0)));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0.25f), aux));
		obs.push_back(Obstacle(aux + glm::vec3(0.25f, 0, 0), aux + glm::vec3(0, 0, 0.25f)));
	}
	Mesh* sky = Object3D::CreateRect("sky", glm::vec3(-50, -1, -50), 100, 100, 51, glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	meshes[sky->GetMeshID()] = sky;
	//Car
	{

		thirdPersCamera = true;
		Mesh* car1 = Object3D::CreateRect(myCar->name, myCar->corner, myCar->length, myCar->width, myCar->height, myCar->color1, myCar->color2);
		myCar->meshes.push_back(car1);

		myCar->cameraPos = myCar->centre + glm::vec3(0, 0.25f, 1.1f);
		myCar->cameraCentre = myCar->centre + glm::vec3(0, 0, 3);
		myCar->cameraCentreThirdP = myCar->cameraCentre + glm::vec3(0, 2, -5);

		camera = new Laborator::Camera();
		camera->Set(myCar->cameraPos, myCar->cameraCentre, glm::vec3(0, 1, 0));

		Mesh* wheel1 = new Mesh("wheel1");
		wheel1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		myCar->meshes.push_back(wheel1);

		Mesh* wheel2 = new Mesh("wheel2");
		wheel2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		myCar->meshes.push_back(wheel2);

		Mesh* wheel3 = new Mesh("wheel3");
		wheel3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		myCar->meshes.push_back(wheel3);

		Mesh* wheel4 = new Mesh("wheel4");
		wheel4->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		myCar->meshes.push_back(wheel4);
	}
	Mesh* grass = Object3D::CreateCircuit("grass", glm::vec3(-50, 0.09f, -50), glm::vec3(0.133333f, 0.545098f, 0.133333f), 100, 100);
	meshes[grass->GetMeshID()] = grass;

	//Circuit
	{
		//-----
		Mesh* street1 = Object3D::CreateCircuit("street1", myCar->centre + glm::vec3(-1.25f, -0.1f, 0), glm::vec3(0.184314f, 0.309804f, 0.309804f), 3, 6);
		meshes[street1->GetMeshID()] = street1;
		glm::vec3 aux = myCar->centre + glm::vec3(-1.25f, -0.1f, 0);
		Mesh* bord11 = Object3D::CreateRect2("bord11", aux, aux - glm::vec3(0.1f, 0, 0), glm::vec2(0, 6), glm::vec2(0, 6), glm::vec3(0, 0, 0.545098f));
		meshes[bord11->GetMeshID()] = bord11;
		obs.push_back(Obstacle(aux - glm::vec3(0.1f, 0, 0), aux + glm::vec3(0, 0, 6)));
		Mesh* bord12 = Object3D::CreateRect2("bord12", aux + glm::vec3(3, 0, 0), aux + glm::vec3(3.1f, 0, 0), glm::vec2(0, 6), glm::vec2(0, 6), glm::vec3(0, 0, 0.545098f));
		meshes[bord12->GetMeshID()] = bord12;
		obs.push_back(Obstacle(aux + glm::vec3(3.1f, 0, 0), aux + glm::vec3(3, 0, 0) + glm::vec3(0, 0, 6)));
		//-----
		//-----
		Mesh* curba1 = Object3D::CreatePara("curba1", glm::vec3(1, 0.1f, 8), glm::vec3(4, 0.1f, 8), glm::vec2(-8, 8), glm::vec2(-5, 5), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba1->GetMeshID()] = curba1;
		Mesh* bord21 = Object3D::CreateRect2("bord21", glm::vec3(0.9f, 0.1f, 8), glm::vec3(1, 0.1f, 8), glm::vec2(-5, 5), glm::vec2(-5, 5), glm::vec3(0, 0, 0.545098f));
		meshes[bord21->GetMeshID()] = bord21;
		obs.push_back(Obstacle(glm::vec3(1, 0.1f, 8), glm::vec3(1, 0.1f, 8) + glm::vec3(-5, 0, 5)));
		Mesh* bord22 = Object3D::CreateRect2("bord22", glm::vec3(4, 0.1f, 8), glm::vec3(4.1f, 0.1f, 8), glm::vec2(-8, 8), glm::vec2(-8, 8), glm::vec3(0, 0, 0.545098f));
		meshes[bord22->GetMeshID()] = bord22;
		obs.push_back(Obstacle(glm::vec3(4.1f, 0.1f, 8), glm::vec3(4.1f, 0.1f, 8) + glm::vec3(-8, 0, 8)));
		//-----
		//-----
		Mesh* curba2 = Object3D::CreatePara("curba2", glm::vec3(-4, 0.1f, 13), glm::vec3(-4, 0.1f, 16), glm::vec2(-5, -5), glm::vec2(-5, -5), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba2->GetMeshID()] = curba2;
		Mesh* bord31 = Object3D::CreateRect2("bord31", glm::vec3(-4.1f, 0.1f, 13), glm::vec3(-4, 0.1f, 13), glm::vec2(-5, -5), glm::vec2(-5, -5), glm::vec3(0, 0, 0.545098f));
		meshes[bord31->GetMeshID()] = bord31;
		obs.push_back(Obstacle(glm::vec3(-4, 0.1f, 13), glm::vec3(-4, 0.1f, 13) + glm::vec3(-5, 0, -5)));
		Mesh* bord32 = Object3D::CreateRect2("bord32", glm::vec3(-4.1f, 0.1f, 16), glm::vec3(-4, 0.1f, 16), glm::vec2(-5, -5), glm::vec2(-5, -5), glm::vec3(0, 0, 0.545098f));
		meshes[bord32->GetMeshID()] = bord32;
		obs.push_back(Obstacle(glm::vec3(-4, 0.1f, 16), glm::vec3(-4, 0.1f, 16) + glm::vec3(-5, 0, -5)));
		//-----
		//-----
		Mesh* curba3 = Object3D::CreatePara("curba3", glm::vec3(-9, 0.1f, 8), glm::vec3(-9, 0.1f, 11), glm::vec2(-5, 5), glm::vec2(-5, 5), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba3->GetMeshID()] = curba3;
		Mesh* bord41 = Object3D::CreateRect2("bord41", glm::vec3(-9.1f, 0.1f, 8), glm::vec3(-9, 0.1f, 8), glm::vec2(-5, 5), glm::vec2(-5, 5), glm::vec3(0, 0, 0.545098f));
		meshes[bord41->GetMeshID()] = bord41;
		obs.push_back(Obstacle(glm::vec3(-9, 0.1f, 8), glm::vec3(-9, 0.1f, 8) + glm::vec3(-5, 0, 5)));
		Mesh* bord42 = Object3D::CreateRect2("bord42", glm::vec3(-9.1f, 0.1f, 11), glm::vec3(-9, 0.1f, 11), glm::vec2(-5, 5), glm::vec2(-5, 5), glm::vec3(0, 0, 0.545098f));
		meshes[bord42->GetMeshID()] = bord42;
		obs.push_back(Obstacle(glm::vec3(-9, 0.1f, 11), glm::vec3(-9, 0.1f, 11) + glm::vec3(-5, 0, 5)));
		//-----
		//-----
		Mesh* curba4 = Object3D::CreatePara("curba4", glm::vec3(-14, 0.1f, 13), glm::vec3(-14, 0.1f, 16), glm::vec2(-2, -2), glm::vec2(-2, -2), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba4->GetMeshID()] = curba4;
		Mesh* bord51 = Object3D::CreateRect2("bord51", glm::vec3(-14.1f, 0.1f, 13), glm::vec3(-14, 0.1f, 13), glm::vec2(-2, -2), glm::vec2(-2, -2), glm::vec3(0, 0, 0.545098f));
		meshes[bord51->GetMeshID()] = bord51;
		obs.push_back(Obstacle(glm::vec3(-14, 0.1f, 13), glm::vec3(-14, 0.1f, 13) + glm::vec3(-2, 0, -2)));
		Mesh* bord52 = Object3D::CreateRect2("bord52", glm::vec3(-14.1f, 0.1f, 16), glm::vec3(-14, 0.1f, 16), glm::vec2(-2, -2), glm::vec2(-2, -2), glm::vec3(0, 0, 0.545098f));
		meshes[bord52->GetMeshID()] = bord52;
		obs.push_back(Obstacle(glm::vec3(-14, 0.1f, 16), glm::vec3(-14, 0.1f, 16) + glm::vec3(-2, 0, -2)));
		//-----
		//-----
		Mesh* curba5 = Object3D::CreatePara("curba5", glm::vec3(-16, 0.1f, 11), glm::vec3(-16, 0.1f, 14), glm::vec2(-3, 0), glm::vec2(-3, 0), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba5->GetMeshID()] = curba5;
		Mesh* bord61 = Object3D::CreateRect2("bord61", glm::vec3(-16.1f, 0.1f, 10.9f), glm::vec3(-16, 0.1f, 11), glm::vec2(-3, 0), glm::vec2(-3, 0), glm::vec3(0, 0, 0.545098f));
		meshes[bord61->GetMeshID()] = bord61;
		obs.push_back(Obstacle(glm::vec3(-16, 0.1f, 11), glm::vec3(-16, 0.1f, 11) + glm::vec3(-3, 0, 0)));
		Mesh* bord62 = Object3D::CreateRect2("bord62", glm::vec3(-16.1f, 0.1f, 13.9), glm::vec3(-16, 0.1f, 14), glm::vec2(-3, 0), glm::vec2(-3, 0), glm::vec3(0, 0, 0.545098f));
		meshes[bord62->GetMeshID()] = bord62;
		obs.push_back(Obstacle(glm::vec3(-16, 0.1f, 14), glm::vec3(-16, 0.1f, 14) + glm::vec3(-3, 0, 0)));
		//-----
		//-----
		Mesh* curba6 = Object3D::CreatePara("curba6", glm::vec3(-19, 0.1f, 11), glm::vec3(-19, 0.1f, 14), glm::vec2(-6, -6), glm::vec2(-3, -3), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba6->GetMeshID()] = curba6;
		Mesh* bord71 = Object3D::CreateRect2("bord71", glm::vec3(-19.1f, 0.1f, 11), glm::vec3(-19, 0.1f, 11), glm::vec2(-3, -3), glm::vec2(-3, -3), glm::vec3(0, 0, 0.545098f));
		meshes[bord71->GetMeshID()] = bord71;
		obs.push_back(Obstacle(glm::vec3(-19, 0.1f, 11), glm::vec3(-19, 0.1f, 11) + glm::vec3(-3, 0, -3)));
		Mesh* bord72 = Object3D::CreateRect2("bord72", glm::vec3(-19.1f, 0.1f, 14), glm::vec3(-19, 0.1f, 14), glm::vec2(-6, -6), glm::vec2(-6, -6), glm::vec3(0, 0, 0.545098f));
		meshes[bord72->GetMeshID()] = bord72;
		obs.push_back(Obstacle(glm::vec3(-19.1f, 0.1f, 14), glm::vec3(-19.1f, 0.1f, 14) + glm::vec3(-6, 0, -6)));
		//-----
		//-----
		Mesh* curba7 = Object3D::CreatePara("curba7", glm::vec3(-22, 0.1f, 8), glm::vec3(-25, 0.1f, 8), glm::vec2(8, -8), glm::vec2(5, -5), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba7->GetMeshID()] = curba7;
		Mesh* bord81 = Object3D::CreateRect2("bord81", glm::vec3(-22.1f, 0.1f, 8), glm::vec3(-22, 0.1f, 8), glm::vec2(5, -5), glm::vec2(5, -5), glm::vec3(0, 0, 0.545098f));
		meshes[bord81->GetMeshID()] = bord81;
		obs.push_back(Obstacle(glm::vec3(-22, 0.1f, 8), glm::vec3(-22, 0.1f, 8) + glm::vec3(5, 0, -5)));
		Mesh* bord82 = Object3D::CreateRect2("bord82", glm::vec3(-25.1f, 0.1f, 8), glm::vec3(-25, 0.1f, 8), glm::vec2(8, -8), glm::vec2(8, -8), glm::vec3(0, 0, 0.545098f));
		meshes[bord82->GetMeshID()] = bord82;
		obs.push_back(Obstacle(glm::vec3(-25, 0.1f, 8), glm::vec3(-25, 0.1f, 8) + glm::vec3(8, 0, -8)));
		//-----
		//-----
		Mesh* curba8 = Object3D::CreatePara("curba8", glm::vec3(-17, 0.1f, 3), glm::vec3(-17, 0.1f, 0), glm::vec2(5, 0), glm::vec2(6, 0), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba8->GetMeshID()] = curba8;
		Mesh* bord91 = Object3D::CreateRect2("bord91", glm::vec3(-17.1f, 0.1f, 3), glm::vec3(-17, 0.1f, 2.9f), glm::vec2(6, 0), glm::vec2(6, 0), glm::vec3(0, 0, 0.545098f));
		meshes[bord91->GetMeshID()] = bord91;
		obs.push_back(Obstacle(glm::vec3(-17, 0.1f, 2.9f), glm::vec3(-17, 0.1f, 2.9f) + glm::vec3(6, 0, 0)));
		Mesh* bord92 = Object3D::CreateRect2("bord92", glm::vec3(-17.1f, 0.1f, 0), glm::vec3(-17, 0.1f, -0.1f), glm::vec2(5, 0), glm::vec2(5, 0), glm::vec3(0, 0, 0.545098f));
		meshes[bord92->GetMeshID()] = bord92;
		obs.push_back(Obstacle(glm::vec3(-17, 0.1f, -0.1f), glm::vec3(-17, 0.1f, -0.1f) + glm::vec3(5, 0, 0)));
		//-----
		//-----
		Mesh* curba9 = Object3D::CreatePara("curba9", glm::vec3(-11, 0.1f, 3), glm::vec3(-12, 0.1f, 0), glm::vec2(8, -8), glm::vec2(8, -8), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba9->GetMeshID()] = curba9;
		Mesh* bord101 = Object3D::CreateRect2("bord101", glm::vec3(-11.1f, 0.1f, 3), glm::vec3(-11, 0.1f, 3), glm::vec2(8, -8), glm::vec2(8, -8), glm::vec3(0, 0, 0.545098f));
		meshes[bord101->GetMeshID()] = bord101;
		obs.push_back(Obstacle(glm::vec3(-11, 0.1f, 3), glm::vec3(-11, 0.1f, 3) + glm::vec3(8, 0, -8)));
		Mesh* bord102 = Object3D::CreateRect2("bord102", glm::vec3(-12.1f, 0.1f, 0), glm::vec3(-12, 0.1f, 0), glm::vec2(8, -8), glm::vec2(8, -8), glm::vec3(0, 0, 0.545098f));
		meshes[bord102->GetMeshID()] = bord102;
		obs.push_back(Obstacle(glm::vec3(-12, 0.1f, 0), glm::vec3(-12, 0.1f, 0) + glm::vec3(8, 0, -8)));
		//-----
		//-----
		Mesh* curba10 = Object3D::CreatePara("curba10", glm::vec3(-3, 0.1f, -5), glm::vec3(-4, 0.1f, -8), glm::vec2(8, 0), glm::vec2(4, 0), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba10->GetMeshID()] = curba10;
		Mesh* bord111 = Object3D::CreateRect2("bord111", glm::vec3(-3.1f, 0.1f, -5), glm::vec3(-3, 0.1f, -5.1f), glm::vec2(4, 0), glm::vec2(4, 0), glm::vec3(0, 0, 0.545098f));
		meshes[bord111->GetMeshID()] = bord111;
		obs.push_back(Obstacle(glm::vec3(-3, 0.1f, -5.1f), glm::vec3(-3, 0.1f, -5.1f) + glm::vec3(4, 0, 0)));
		Mesh* bord112 = Object3D::CreateRect2("bord112", glm::vec3(-4.1f, 0.1f, -8), glm::vec3(-4, 0.1f, -8.1f), glm::vec2(8, 0), glm::vec2(8, 0), glm::vec3(0, 0, 0.545098f));
		meshes[bord112->GetMeshID()] = bord112;
		obs.push_back(Obstacle(glm::vec3(-4, 0.1f, -8.1f), glm::vec3(-4, 0.1f, -8.1f) + glm::vec3(8, 0, 0)));
		//-----
		//-----
		Mesh* curba11 = Object3D::CreatePara("curba11", glm::vec3(1, 0.1f, -5), glm::vec3(4, 0.1f, -8), glm::vec2(0.1f, 10), glm::vec2(0, 7), glm::vec3(0.184314f, 0.309804f, 0.309804f));
		meshes[curba11->GetMeshID()] = curba11;
		Mesh* bord121 = Object3D::CreateRect2("bord121", glm::vec3(0.9f, 0.1f, -5), glm::vec3(1, 0.1f, -5), glm::vec2(0, 7), glm::vec2(0, 7), glm::vec3(0, 0, 0.545098f));
		meshes[bord121->GetMeshID()] = bord121;
		obs.push_back(Obstacle(glm::vec3(1, 0.1f, -5), glm::vec3(1, 0.1f, -5) + glm::vec3(0, 0, 7)));
		Mesh* bord122 = Object3D::CreateRect2("bord122", glm::vec3(3.9f, 0.1f, -8.1f), glm::vec3(4, 0.1f, -8.1f), glm::vec2(0.1f, 10.1f), glm::vec2(0.1f, 10.1f), glm::vec3(0, 0, 0.545098f));
		meshes[bord122->GetMeshID()] = bord122;
		obs.push_back(Obstacle(glm::vec3(4, 0.1f, -8.1f), glm::vec3(4, 0.1f, -8.1f) + glm::vec3(0.1f, 0, 10.1f)));
		//-----
	}
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	
}

void Racing::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Racing::Update(float deltaTimeSeconds)
{//Z - blue, X - red, Y - green
	
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	if (!freeCam) {
		if (!thirdPersCamera)
			camera->Set(myCar->cameraPos, myCar->cameraCentre, glm::vec3(0, 1, 0));
		else
			camera->Set(myCar->cameraCentreThirdP, myCar->cameraCentre, glm::vec3(0, 1, 0));
	}
	if (!gameOver) {
		score += 500 * myCar->speed;
		gameTimer++;

		if (!canMakeCollision) {
			lastCollisionTimer++;
			if (lastCollisionTimer > 17) {
				canMakeCollision = true;
			}
		}

		if (gameTimer == 1500) {
			gameOver = true;
		}
		if (timeBend) {
			time -= 0.25f;
			if (time == 25) {
				timeBend = false;
			}
		}
		else {
			time += 0.25f;
			if (time == 255) {
				timeBend = true;
			}
		}
		myCar->moveCar();
		myCar->rotateWheels();


		RenderMesh(myCar->meshes[0], shaders["VertexColor"], myCar->Matrixes[0]);
		for (int i = 1; i < 5; i++) {
			RenderMesh(myCar->meshes[i], shaders["VertexNormal"], myCar->Matrixes[i]);
		}
		{
			RenderMesh(meshes["sky"], shaders["SkyShader2"], glm::mat4(1));
			RenderMesh(meshes["grass"], shaders["SkyShader"], glm::mat4(1));
			RenderMesh(meshes["street1"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba1"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba2"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba3"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba4"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba5"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba6"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba7"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba8"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba9"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba10"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["curba11"], shaders["SkyShader3"], glm::mat4(1));
			RenderMesh(meshes["bord11"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord12"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord21"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord22"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord31"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord32"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord41"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord42"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord51"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord52"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord61"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord62"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord71"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord72"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord81"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord82"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord91"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord92"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord101"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord102"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord111"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord112"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord121"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["bord122"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs1"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs2"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs3"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs4"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs5"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs6"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs7"], shaders["VertexColor"], glm::mat4(1));
			RenderMesh(meshes["obs8"], shaders["VertexColor"], glm::mat4(1));
		}
		for each(Obstacle aux in obs) {
			for (int i = 0; i < 8; i++) {
				glm::vec3 auxC = myCar->collisionPoints[i];
				float distAC = sqrt(pow(aux.unu.x - auxC.x, 2) + pow(aux.unu.z - auxC.z, 2));
				float distCB = sqrt(pow(aux.doi.x - auxC.x, 2) + pow(aux.doi.z - auxC.z, 2));
				float distAB = sqrt(pow(aux.doi.x - aux.unu.x, 2) + pow(aux.doi.z - aux.unu.z, 2));
				if (distAC + distCB - distAB <= 0.0005f && canMakeCollision) {
					if (i == 0 || i == 1 || i == 2) {
						collisionRear = true;
					}
					else if (i == 5 || i == 6 || i == 7) {
						collisionFront = true;
					}
					if (!scoreDec) {
						score -= 250;
						cout << "Collision ! Total Points Left : " << score << endl;
						myCar->speed = 0;
						myCar->wheelAngle = 0;
						scoreDec = true;
						lastCollisionTimer = 0;
						canMakeCollision = false;
					}
				}
			}
		}
		scoreDec = false;
	}
	else if (!scoreShown){
		cout << "Game Over ! Total Score : " << score << endl;
		scoreShown = true;
	}
}

void Racing::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Racing::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int lco = glGetUniformLocation(shader->program, "Time");
	glUniform1f(lco, this->time);

	mesh->Render();
}

void Racing::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 0.05f;

		if (window->KeyHold(GLFW_KEY_W))
			camera->TranslateForward(cameraSpeed);

		if (window->KeyHold(GLFW_KEY_A))
			camera->TranslateRight(-cameraSpeed);

		if (window->KeyHold(GLFW_KEY_S))
			camera->TranslateForward(-cameraSpeed);

		if (window->KeyHold(GLFW_KEY_D))
			camera->TranslateRight(cameraSpeed);

		if (window->KeyHold(GLFW_KEY_Q))
			camera->TranslateUpword(-cameraSpeed);

		if (window->KeyHold(GLFW_KEY_E))
			camera->TranslateUpword(cameraSpeed);
	}
	else {
		if (window->KeyHold(GLFW_KEY_W) && !collisionFront) {
			if (myCar->speed <= 0.07f) {
				myCar->speed += 0.01f;
				myCar->wheelAngle += 0.5f;
			}
			collisionRear = false;
		}
			

		if (window->KeyHold(GLFW_KEY_S) && !collisionRear) {
			if (myCar->speed >= -0.07f) {
				myCar->speed -= 0.01f;
				myCar->wheelAngle -= 0.5f;
			}
			
			collisionFront = false;
		}
			
			
		if (window->KeyHold(GLFW_KEY_A) && !window->KeyHold(GLFW_KEY_D) && !collisionRear && !collisionFront) {
			myCar->turnCar(2);
			myCar->totalAngleCar += 2;
			if (!myCar->turnedLeft) {
				myCar->turnWheels(wheelAngleTurn, 2, 4);
				myCar->totalAngleWheels += wheelAngleTurn;
				myCar->turnedLeft = true;
				myCar->turnedRight = false;
			}	
		}

		if (window->KeyHold(GLFW_KEY_D) && !window->KeyHold(GLFW_KEY_A) && !collisionRear && !collisionFront) {
			myCar->turnCar(-2);
			myCar->totalAngleCar -= 2;
			if (!myCar->turnedRight) {
				myCar->turnWheels(-wheelAngleTurn, 2, 4);
				myCar->totalAngleWheels -= wheelAngleTurn;
				myCar->turnedRight = true;
				myCar->turnedLeft = false;
			}
		}
	}
}

void Racing::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		freeCam = !freeCam;
		
	} else if (key == GLFW_KEY_X) {
		switch (polygonMode)
		{
		case GL_LINE:
			polygonMode = GL_FILL;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
	else if (key == GLFW_KEY_Z) {
		thirdPersCamera = !thirdPersCamera;
	}
	else if (key == GLFW_KEY_H) {
		cout << "coords = " << myCar->centre.x << " " << myCar->centre.y << " " << myCar->centre.z << endl;
	}
	
}

void Racing::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_A && myCar->turnedLeft) {
		myCar->turnWheels(-wheelAngleTurn, 2, 4);
		myCar->totalAngleWheels -= wheelAngleTurn;
		myCar->turnedLeft = false;
	}
	else if (key == GLFW_KEY_D && myCar->turnedRight) {
		myCar->turnWheels(wheelAngleTurn, 2, 4);
		myCar->totalAngleWheels += wheelAngleTurn;
		myCar->turnedRight = false;
	}
}

void Racing::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * deltaX);
			camera->RotateFirstPerson_OY(sensivityOY * deltaY);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * deltaX);
			camera->RotateThirdPerson_OY(sensivityOY * deltaY);
		}

	}
}

void Racing::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Racing::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Racing::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Racing::OnWindowResize(int width, int height)
{
}
