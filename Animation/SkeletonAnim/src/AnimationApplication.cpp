#include "AnimationApplication.h"
#include <Physics/PhysicsEngine.h>

void AnimationApplication::SetUp()
{
	viewportCamera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 500.0f, 65.0f);
	viewportCamera->transform.SetPosition(glm::vec3(0.0f, 10.0f, 30.0f));
	viewportCamera->transform.SetRotation(glm::vec3(-10, 0, 0));
	viewportCamera->applyPostProcessing = true;

	EditorLayout::GetInstance().SetMaximizeState(true);

	//PhysicsEngine::GetInstance().gravity.y = -9.8f / 3.0f;

	sceneOne = new Scene_One(this);

	SceneManager::GetInstance().AddScene("SceneOne", sceneOne);
	SceneManager::GetInstance().ChangeScene("SceneOne");
}

void AnimationApplication::Update()
{
	//PhysicsEngine::GetInstance().Update(Timer::GetInstance().deltaTime);
}

void AnimationApplication::Render()
{
}

void AnimationApplication::Shutdown()
{
}

void AnimationApplication::OnPlayStateChanged(bool state)
{
}

void AnimationApplication::ProcessInput(GLFWwindow* window)
{
}

void AnimationApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void AnimationApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
