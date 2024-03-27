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

	/*OnModelLoaded = [this](Model* self)
		{
		
		};*/

	LoadModel("Assets/Models/Player.fbx");
	//mColliderShape->SetPositionOffset(glm::vec3(0, 8, 0));
	//mColliderShape->AsCapsule()->SetRadius(2);
	//mColliderShape->AsCapsule()->SetHeight(12);
	InputManager::GetInstance().AddListener(this);
	transform.SetScale(glm::vec3(0.08f));
	InitializePhysics(RigidBody::DYNAMIC, BaseColliderShape::BOX);
	mColliderShape->SetPositionOffset(glm::vec3(0, 7.f, 0));

	LoadAndAddAnimationClip("Assets/Animations/Player_Run.fbx", "Taunt");

	mRigidBody.mRotationConstraints = RigidBody::AxisConstraints(true, true, true);
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

void Character::Start()
{
	SetVelocity(glm::vec3(0, GetVelocity().y, 0));
}

void Character::Update(float deltaTime)
{
	PhysicsSkeletonObject::Update(deltaTime);
	glm::vec2 dir;
	float speed = 2;

	dir.x = InputManager::GetInstance().GetAxisX();
	
	transform.rotation.y += dir.x * speed;
	transform.SetRotation(transform.rotation);
}
