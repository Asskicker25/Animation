#include "Character.h"
#include "../Shaders/Shaders.h"

#include <Physics/Shapes/CapsuleCollider.h>
#include <Physics/Shapes/SphereCollider.h>

BoneInfo* bone;

glm::vec3 pos, rot, scale;

Character::Character() : PhysicsSkeletonObject()
{
	
}

void Character::Initialize()
{
	shader = Shaders::GetInstance().mBoneAnimationShader;
	//character->LoadModel("Assets/Models/Character_Idle.fbx");
	//character->LoadModel("Assets/Models/Ninja.fbx");
	//LoadModel("Assets/Models/RiggedCube_Anim.fbx");

	OnModelLoaded = [this](Model* self)
		{
			InitializePhysics(RigidBody::DYNAMIC, BaseColliderShape::SPHERE);
			mColliderShape->AsSphere()->SetRadius(1);
			//mColliderShape->AsCapsule()->mHeight = 10;
		};

	LoadModelAsync("Assets/Models/Player.fbx");
	InputManager::GetInstance().AddListener(this);
	transform.SetScale(glm::vec3(0.08f));
	LoadAndAddAnimationClip("Assets/Animations/Player_Run.fbx", "Taunt");
}

void Character::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_SPACE)
	{
		mIsPlaying = !mIsPlaying;
	}
	else if (key == GLFW_KEY_1)
	{
		PlayAnimation("Taunt");
	}
	else if (key == GLFW_KEY_2)
	{
		PlayAnimation("ChickenDance");
	}
	else if (key == GLFW_KEY_3)
	{
		PlayAnimation("SillyDancing");
	}
	else if (key == GLFW_KEY_4)
	{
		PlayAnimation("TakeDown");
	}
	else if (key == GLFW_KEY_5)
	{
		PlayAnimation("Stretching");
	}
}
