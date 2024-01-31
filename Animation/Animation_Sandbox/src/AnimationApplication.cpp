#include "AnimationApplication.h"




void AnimationApplication::SetUp()
{
	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 100.0f, 45.0f);

	camera->transform.SetPosition(glm::vec3(0, 0, 15));

	Light* dirLight = new Light(Directional);
	dirLight->transform.SetPosition(glm::vec3(0, 0, 3));

	AnimationClip* clip1 = new AnimationClip();

	clip1->SetCurrentKeyType(POSITION);
	clip1->AddKeyFrame(glm::vec3(0,0,0), 0);
	clip1->AddKeyFrame(glm::vec3(0,3,0), 1);

	clip1->SetCurrentKeyType(ROTATION);
	clip1->AddKeyFrame(glm::vec3(0, 0, 0), 0);
	clip1->AddKeyFrame(glm::vec3(40, 90, 0), 1);

	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(1, 1, 1), 0);
	clip1->AddKeyFrame(glm::vec3(2, 2, 2), 0.5f);
	clip1->AddKeyFrame(glm::vec3(1, 1, 1), 1.0f);

	AnimationClip* clip2 = new AnimationClip();

	clip2->SetCurrentKeyType(POSITION);
	clip2->AddKeyFrame(glm::vec3(0, 3, 0), 0);
	clip2->AddKeyFrame(glm::vec3(3, 0, 0), 1);

	clip2->SetCurrentKeyType(ROTATION);
	clip2->AddKeyFrame(glm::vec3(40, 90, 0), 0);
	clip2->AddKeyFrame(glm::vec3(0, 0, 0), 1);


	AnimatedObject* model = new AnimatedObject();
	model->LoadModel("Assets/Sphere/Sphere 1.fbx");
	model->AddAnimationClip(clip1);
	model->AddAnimationClip(clip2);

	listOfAnimatedObjects.push_back(model);


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
		else if (key == GLFW_KEY_LEFT)
		{
			HandlePreviousClip();
		}
		else if (key == GLFW_KEY_RIGHT)
		{
			HandleNextClip();
		}
	}
}

void AnimationApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}


void AnimationApplication::HandlePreviousClip()
{
	AnimationSystem::GetInstance().animationTime = 0;

	for (AnimatedObject* animObject : listOfAnimatedObjects)
	{
		animObject->SetCurrentAnimationClip((animObject->GetCurrentAnimationIndex() - 1));
	}
}

void AnimationApplication::HandleNextClip()
{
	AnimationSystem::GetInstance().animationTime = 0;

	for (AnimatedObject* animObject : listOfAnimatedObjects)
	{
		animObject->SetCurrentAnimationClip((animObject->GetCurrentAnimationIndex() + 1));
	}
}