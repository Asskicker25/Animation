#include "GameScene.h"
#include "AnimationSequenceManager.h"
#include "StarDestroyer/StarDestroyer.h"

GameScene::GameScene()
{
	name = "GameScene";

	sequenceManager = new AnimationSequenceManager();
	sequenceManager->OnSequenceChange = [this](int value)
		{
			OnSequenceChange(value);
		};

	sequenceManager->OnReset = [this](int value)
		{
			OnSequenceReset(value);
		};


	StarDestroyer* starDestroyer = new StarDestroyer();

	SpawnXWingOne();
	SpawnXWingTwo();
	SpawnExplosionOne();
	SpawnExplosionTwo();

	AnimationSequence* sequence1 = new AnimationSequence();
	AnimationSequence* sequence2 = new AnimationSequence();
	AnimationSequence* sequence3 = new AnimationSequence();
	sequence1->SetDuration(10);
	sequence2->SetDuration(6);
	sequence3->SetDuration(4);

	sequenceManager->AddSequence(sequence3);
	sequenceManager->AddSequence(sequence1);
	sequenceManager->AddSequence(sequence2);

	sequenceManager->Initialize();


	InitializeEntity(this);
}

GameScene::~GameScene()
{
	delete sequenceManager;
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

void GameScene::OnSequenceReset(int index)
{
	for (AnimatedObject* obj : listOfAnimatedObjects)
	{
		if (obj->GetCurrentAnimationClip() == nullptr) continue;

		obj->GetCurrentAnimationClip()->ResetKeyFrameTrigger();
	}
}

void GameScene::SpawnXWingOne()
{
	AnimatedObject* xwing1 = new AnimatedObject();
	xwing1->LoadModel("Assets/X-Wing/X-Wing.ply");
	xwing1->name = "X-Wing 1";
	xwing1->transform.SetScale(glm::vec3(0.1f));
	xwing1->transform.SetPosition(glm::vec3(0, -0.3f, 16));




#pragma region ClipOne
	AnimationClip* clip1 = new AnimationClip();

	clip1->SetCurrentKeyType(POSITION);
	clip1->AddKeyFrame(glm::vec3(0, -0.3f, 16), 0);
	clip1->AddKeyFrame(glm::vec3(0.7f, -0.3f, 1.5), 5.0f, SineEaseIn);
	clip1->AddKeyFrame(glm::vec3(0.86, -0.3f, 16), 10.0f, SineEaseOut);

	clip1->SetCurrentKeyType(ROTATION);
	clip1->AddKeyFrame(glm::vec3(0, 0, 0), 0);
	clip1->AddKeyFrame(glm::vec3(0, 0, 180), 5.0f);
	clip1->AddKeyFrame(glm::vec3(0, -180, 180), 6.0f);

	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(0.1), 0);
	clip1->AddKeyFrame(glm::vec3(0.1), 10);

	clip1->AddKeyFrameEvent(new KeyFrameEvent(5, [this]()
		{
			std::cout << "Star Destroyer Explosion Trigger " << std::endl;
		}));



#pragma endregion

#pragma region ClipTwo

	AnimationClip* clip2 = new AnimationClip();
	clip2->SetCurrentKeyType(POSITION);
	clip2->AddKeyFrame(glm::vec3(5.5, 0.0f, 9.6), 0);
	clip2->AddKeyFrame(glm::vec3(-1.26, 0.0f, 9.6), 3, SineEaseIn);

	clip2->SetCurrentKeyType(ROTATION);
	clip2->AddKeyFrame(glm::vec3(-1.2, 77.0f, 0), 0);
	clip2->AddKeyFrame(glm::vec3(-3.9, 34.0f, 0), 3);

	clip2->SetCurrentKeyType(SCALE);
	clip2->AddKeyFrame(glm::vec3(0.1), 0);
	clip2->AddKeyFrame(glm::vec3(0.1), 3);
	clip2->AddKeyFrame(glm::vec3(0), 4);

	clip2->AddKeyFrameEvent(new KeyFrameEvent(3, [this]()
		{
			std::cout << "XWing Explosion Trigger " << std::endl;
		}));

#pragma endregion

#pragma region ClipThree

	AnimationClip* clip3 = new AnimationClip();
	clip3->SetCurrentKeyType(POSITION);
	clip3->AddKeyFrame(glm::vec3(-10, 0.0f, 0.6), 0);
	clip3->AddKeyFrame(glm::vec3(10, 0.0f, 0.6), 4, SineEaseIn);

	clip3->SetCurrentKeyType(ROTATION);
	clip3->AddKeyFrame(glm::vec3(-280, 0.0f, -90.0), 0);


#pragma endregion

	xwing1->AddAnimationClip(clip3);
	xwing1->AddAnimationClip(clip1);
	xwing1->AddAnimationClip(clip2);
	listOfAnimatedObjects.push_back(xwing1);

}

void GameScene::SpawnXWingTwo()
{
	AnimatedObject* xwing2 = new AnimatedObject();
	xwing2->LoadModel("Assets/X-Wing/X-Wing.ply");
	xwing2->name = "X-Wing 2";
	xwing2->transform.SetScale(glm::vec3(0.1f));
	xwing2->transform.SetPosition(glm::vec3(13.0f, 0.2f, -0.74f));

#pragma region ClipOne
	AnimationClip* clip1 = new AnimationClip();

	clip1->SetCurrentKeyType(POSITION);
	clip1->AddKeyFrame(glm::vec3(13.0f, 0.2f, -0.74f), 0);
	clip1->AddKeyFrame(glm::vec3(3.12f, 0.2f, -0.74f), 3.0f, SineEaseInOut);
	clip1->AddKeyFrame(glm::vec3(-13.2f, 1.0f, 0.46), 6.0f, SineEaseIn);


	clip1->SetCurrentKeyType(ROTATION);
	clip1->AddKeyFrame(glm::vec3(-3.0f, 51.40, 0), 0);
	clip1->AddKeyFrame(glm::vec3(-3.0f, 51.40, 0), 3);
	clip1->AddKeyFrame(glm::vec3(10.0f, 51.40, 0), 4);

	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(0.1), 0);
	clip1->AddKeyFrame(glm::vec3(0.1), 10);

#pragma endregion

#pragma region ClipTwo

	AnimationClip* clip2 = new AnimationClip();

	clip2->SetCurrentKeyType(POSITION);
	clip2->AddKeyFrame(glm::vec3(-8.0f, 6.5f, -0.54f), 0);
	clip2->AddKeyFrame(glm::vec3(-8.0f, 3.0f, -0.54f), 1.5f, SineEaseIn);
	clip2->AddKeyFrame(glm::vec3(-2.0f, 0.1f, 8.44f), 3.0f, SineEaseInOut);

	clip2->SetCurrentKeyType(ROTATION);
	clip2->AddKeyFrame(glm::vec3(-24.0f, -151.5f, 0.0), 0);
	clip2->AddKeyFrame(glm::vec3(-24.0f, -151.5f, 0.0), 1.5f);
	clip2->AddKeyFrame(glm::vec3(-0.20f, -142.5f, 0.0), 3.0f);

	clip2->SetCurrentKeyType(SCALE);
	clip2->AddKeyFrame(glm::vec3(0.1), 0);
	clip2->AddKeyFrame(glm::vec3(0.1), 3);
	clip2->AddKeyFrame(glm::vec3(0), 4);


#pragma endregion

#pragma region ClipThree

	AnimationClip* clip3 = new AnimationClip();
	clip3->SetCurrentKeyType(POSITION);
	clip3->AddKeyFrame(glm::vec3(-10, -1.6f, 0.6), 0);
	clip3->AddKeyFrame(glm::vec3(10, -1.6f, 0.6), 4, SineEaseInOut);

	clip3->SetCurrentKeyType(ROTATION);
	clip3->AddKeyFrame(glm::vec3(-280, 0.0f, -90.0), 0);


#pragma endregion

	xwing2->AddAnimationClip(clip3);
	xwing2->AddAnimationClip(clip1);
	xwing2->AddAnimationClip(clip2);
	listOfAnimatedObjects.push_back(xwing2);
}

void GameScene::SpawnExplosionOne()
{
	AnimatedObject* explosion = new AnimatedObject(false);
	explosion->LoadModel("res/Models/DefaultSphere.fbx");
	explosion->name = "Explosion";
	explosion->transform.SetScale(glm::vec3(0));
	explosion->transform.SetPosition(glm::vec3(0.5f, -0.4, 0.4));

	explosion->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.8, 0.4, 0, 1));

	AnimationClip* clip1 = new AnimationClip();

	clip1->SetCurrentKeyType(POSITION);
	clip1->AddKeyFrame(glm::vec3(0.5f, -0.4, 0.4), 0);
	clip1->AddKeyFrame(glm::vec3(0.5f, -0.4, 0.4), 6);


	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(0), 0);
	clip1->AddKeyFrame(glm::vec3(0), 5);
	clip1->AddKeyFrame(glm::vec3(1), 5.8, SineEaseOut);
	clip1->AddKeyFrame(glm::vec3(0), 9, SineEaseIn);

	AnimationClip* clip2 = new AnimationClip();

	clip2->SetCurrentKeyType(POSITION);
	clip2->AddKeyFrame(glm::vec3(-1.26, 0.0f, 9.6), 0);
	clip2->AddKeyFrame(glm::vec3(-1.26, 0.0f, 9.6), 6);


	clip2->SetCurrentKeyType(SCALE);
	clip2->AddKeyFrame(glm::vec3(0), 0);
	clip2->AddKeyFrame(glm::vec3(0), 3);
	clip2->AddKeyFrame(glm::vec3(1), 3.8, SineEaseOut);
	clip2->AddKeyFrame(glm::vec3(0), 6, SineEaseIn);

	AnimationClip* clip3 = new AnimationClip();
	clip3->SetCurrentKeyType(SCALE);
	clip3->AddKeyFrame(glm::vec3(0), 0);

	explosion->AddAnimationClip(clip3);
	explosion->AddAnimationClip(clip1);
	explosion->AddAnimationClip(clip2);

	listOfAnimatedObjects.push_back(explosion);
}

void GameScene::SpawnExplosionTwo()
{
	AnimatedObject* explosion = new AnimatedObject(false);
	explosion->LoadModel("res/Models/DefaultSphere.fbx");
	explosion->name = "Explosion";
	explosion->transform.SetScale(glm::vec3(0));
	explosion->transform.SetPosition(glm::vec3(0.5f, -0.4, 0.4));
	explosion->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.8, 0.4, 0, 1));

	AnimationClip* clip1 = new AnimationClip();
	clip1->SetCurrentKeyType(SCALE);
	clip1->AddKeyFrame(glm::vec3(0), 0);
	clip1->AddKeyFrame(glm::vec3(0), 10);


	AnimationClip* clip2 = new AnimationClip();
	clip2->SetCurrentKeyType(POSITION);
	clip2->AddKeyFrame(glm::vec3(-2.0f, 0.1f, 8.44f), 0);
	clip2->AddKeyFrame(glm::vec3(-2.0f, 0.1f, 8.44f), 6);

	
	clip2->SetCurrentKeyType(SCALE);
	clip2->AddKeyFrame(glm::vec3(0), 0);
	clip2->AddKeyFrame(glm::vec3(0), 3);
	clip2->AddKeyFrame(glm::vec3(1), 3.8, SineEaseOut);
	clip2->AddKeyFrame(glm::vec3(0), 6, SineEaseIn);


	AnimationClip* clip3 = new AnimationClip();
	clip3->SetCurrentKeyType(SCALE);
	clip3->AddKeyFrame(glm::vec3(0), 0);

	explosion->AddAnimationClip(clip3);
	explosion->AddAnimationClip(clip1);
	explosion->AddAnimationClip(clip2);

	listOfAnimatedObjects.push_back(explosion);
}
