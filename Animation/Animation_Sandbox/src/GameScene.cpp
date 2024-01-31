#include "GameScene.h"
#include "AnimationSequenceManager.h"



GameScene::GameScene()
{
#pragma region Model1

	AnimationClip* clip1 = new AnimationClip();

	clip1->SetCurrentKeyType(POSITION);
	clip1->AddKeyFrame(glm::vec3(0, 0, 0), 0);
	clip1->AddKeyFrame(glm::vec3(0, 3, 0), 3, EasingType::Linear);

	clip1->SetCurrentKeyType(ROTATION);
	clip1->AddKeyFrame(glm::vec3(0, 0, 0), 0);
	clip1->AddKeyFrame(glm::vec3(40, 90, 0), 3);

	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(1, 1, 1), 0);
	clip1->AddKeyFrame(glm::vec3(1.2f, 1.2f, 1.2f), 1.5f);
	clip1->AddKeyFrame(glm::vec3(1, 1, 1), 3.0f);

	AnimationClip* clip2 = new AnimationClip();

	clip2->SetCurrentKeyType(POSITION);
	clip2->AddKeyFrame(glm::vec3(0, 3, 0), 0);
	clip2->AddKeyFrame(glm::vec3(3, 0, 0), 3);

	clip2->SetCurrentKeyType(ROTATION);
	clip2->AddKeyFrame(glm::vec3(40, 90, 0), 0);
	clip2->AddKeyFrame(glm::vec3(0, 0, 0), 3);


	AnimatedObject* model = new AnimatedObject();
	model->LoadModel("Assets/Sphere/Sphere 1.fbx");
	model->AddAnimationClip(clip1);
	model->AddAnimationClip(clip2);

#pragma endregion

#pragma region Model2
	AnimationClip* clip3 = new AnimationClip();

	clip3->SetCurrentKeyType(POSITION);
	clip3->AddKeyFrame(glm::vec3(-5, 0, 0), 0);
	clip3->AddKeyFrame(glm::vec3(-5, 1, 0), 1, EasingType::SineEaseIn);

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

#pragma endregion

	listOfAnimatedObjects.push_back(model);
	listOfAnimatedObjects.push_back(model2);

	AnimationSequence* sequence1 = new AnimationSequence();
	AnimationSequence* sequence2 = new AnimationSequence();
	sequence1->SetDuration(3.0f);
	sequence2->SetDuration(3.0f);

	sequenceManager = new AnimationSequenceManager();
	sequenceManager->AddSequence(sequence1);
	sequenceManager->AddSequence(sequence2);

	sequenceManager->OnSequenceChange = [this](int value)
		{
			OnSequenceChange(value);
		};

	sequenceManager->Initialize();
}

void GameScene::Start()
{
}

void GameScene::Update(float deltaTime)
{
}

void GameScene::OnDestroy()
{
}

void GameScene::OnSequenceChange(int index)
{
	for (AnimatedObject* obj : listOfAnimatedObjects)
	{
		obj->SetCurrentAnimationClip(index);
	}
}
