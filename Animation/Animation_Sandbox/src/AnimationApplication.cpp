#include "AnimationApplication.h"
#include "GameScene.h"

void AnimationApplication::SetUp()
{
	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 600.0f, 45.0f);

	camera->transform.SetPosition(glm::vec3(0, 0, 15));

	applicationPlay = true;
	imGuiPanelEnable = false;
	stopKeyCallback = true;
	stopMouseCallback = true;

#pragma region Skybox

	skyBox->meshes[0]->material = new SkyBoxMaterial();
	SkyBoxMaterial* skyboxMat = skyBox->meshes[0]->material->AsSkyBoxMaterial();

	skyboxMat->skyBoxTexture->LoadTexture({
		"Assets/Skybox/Right.jpg",
		"Assets/Skybox/Left.jpg",
		"Assets/Skybox/Up.jpg",
		"Assets/Skybox/Down.jpg",
		"Assets/Skybox/Front.jpg",
		"Assets/Skybox/Back.jpg",
		});

#pragma endregion


	Light* dirLight = new Light(Directional);
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));

	GameScene* gameScene = new GameScene();

	AnimationSystem::GetInstance().Initialize();
}

void AnimationApplication::Update()
{
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

