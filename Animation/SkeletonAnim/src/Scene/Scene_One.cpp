#include "Scene_One.h"
#include "../AppSettings.h"
#include "../AnimationApplication.h"
#include "../Shaders/Shaders.h"

#include <SkeletonModel.h>

Scene_One::Scene_One(AnimationApplication* application)
{
	this->mApplication = application;
}

void Scene_One::Start()
{
	mMainCamera = new GameCamera();
	mMainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 65.0f);
	mMainCamera->transform.SetPosition(glm::vec3(0.0f, 10.0f, 30.0f));
	mMainCamera->transform.SetRotation(glm::vec3(-10, 0, 0));
	//mMainCamera->applyPostProcessing = true;

	mDirLight = new Light();
	mDirLight->transform.SetScale(glm::vec3(0.1f));
	mDirLight->transform.SetPosition(glm::vec3(0, 0, 3));
	mDirLight->transform.SetRotation(glm::vec3(10, 40, 0));
	mDirLight->InitializeLight(Directional);
	mDirLight->intensity = 0.7;


	SkeletonModel* character = new SkeletonModel();
	character->shader = Shaders::GetInstance().mBoneAnimationShader;
	//character->LoadModel("Assets/Models/Character_Idle.fbx");
	//character->LoadModel("Assets/Models/Ninja.fbx");
	character->LoadModel("Assets/Models/RaceDriver.fbx");
	character->transform.SetScale(glm::vec3(0.08f));
}

void Scene_One::Update()
{

}

void Scene_One::Render()
{
}

void Scene_One::ShutDown()
{
	
}
