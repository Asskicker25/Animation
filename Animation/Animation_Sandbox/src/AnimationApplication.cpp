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
	clip1->AddKeyFrame(glm::vec3(0,3,0), 1, EasingType::Linear);

	clip1->SetCurrentKeyType(ROTATION);
	clip1->AddKeyFrame(glm::vec3(0, 0, 0), 0);
	clip1->AddKeyFrame(glm::vec3(40, 90, 0), 1);

	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(1, 1, 1), 0);
	clip1->AddKeyFrame(glm::vec3(1.2f, 1.2f, 1.2f), 0.5f);
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


	AnimationClip* clip3 = new AnimationClip();

	clip3->SetCurrentKeyType(POSITION);
	clip3->AddKeyFrame(glm::vec3(-5, 0, 0), 0);
	clip3->AddKeyFrame(glm::vec3(-5, 3, 0), 1, EasingType::SineEaseIn);

	clip3->SetCurrentKeyType(ROTATION);
	clip3->AddKeyFrame(glm::vec3(0, 0, 0), 0);
	clip3->AddKeyFrame(glm::vec3(40, 90, 0), 1);

	clip3->SetCurrentKeyType(SCALE);
	clip3->AddKeyFrame(glm::vec3(1, 1, 1), 0);
	clip3->AddKeyFrame(glm::vec3(1.2f, 1.2f, 1.2f), 0.5f);
	clip3->AddKeyFrame(glm::vec3(1, 1, 1), 1.0f);

	AnimationClip* clip4 = new AnimationClip();

	clip4->SetCurrentKeyType(POSITION);
	clip4->AddKeyFrame(glm::vec3(-5, 3, 0), 0);
	clip4->AddKeyFrame(glm::vec3(-2, 0, 0), 1);

	clip4->SetCurrentKeyType(ROTATION);
	clip4->AddKeyFrame(glm::vec3(40, 90, 0), 0);
	clip4->AddKeyFrame(glm::vec3(0, 0, 0), 1);


	AnimatedObject* model2 = new AnimatedObject();
	model2->LoadModel("Assets/Sphere/Sphere 1.fbx");
	model2->AddAnimationClip(clip3);
	model2->AddAnimationClip(clip4);

	listOfAnimatedObjects.push_back(model);
	listOfAnimatedObjects.push_back(model2);


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