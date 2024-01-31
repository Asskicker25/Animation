#include "AnimationApplication.h"
#include "GameScene.h"

void AnimationApplication::SetUp()
{
	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 100.0f, 45.0f);

	camera->transform.SetPosition(glm::vec3(0, 0, 15));

	Light* dirLight = new Light(Directional);
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));


	GameScene* gameScene = new GameScene();
}

void AnimationApplication::Update()
{
	AnimationSystem::GetInstance().UpdateAnimations(Timer::GetInstance().deltaTime);
}

void AnimationApplication::Render()
{
}

void AnimationApplication::ProcessInput(GLFWwindow* window)
{
}

void AnimationApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_SPACE)
		{
			AnimationSystem::GetInstance().TogglePlayAndPause();
		}
		else if (key == GLFW_KEY_1)
		{
			AnimationSystem::GetInstance().animationSpeed = 1;
		}
		else if (key == GLFW_KEY_2)
		{
			AnimationSystem::GetInstance().animationSpeed = 2;
		}
		else if (key == GLFW_KEY_3)
		{
			AnimationSystem::GetInstance().animationSpeed = 3;
		}
		else if (key == GLFW_KEY_4)
		{
			AnimationSystem::GetInstance().animationSpeed = 4;
		}
		else if (key == GLFW_KEY_5)
		{
			AnimationSystem::GetInstance().animationSpeed = 5;
		}
	}
}

void AnimationApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}

