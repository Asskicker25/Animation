#include "Character.h"
#include "../Shaders/Shaders.h"

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
	LoadModel("Assets/Models/Player.fbx");
	//meshes[0]->material->AsMaterial()->diffuseTexture = new Texture("Assets/Models/RaceDriver.png");
	transform.SetScale(glm::vec3(0.08f));

	InitializePhysics(AABB, DYNAMIC);

	LoadAndAddAnimationClip("Assets/Animations/Player_Run.fbx", "Taunt");
	/*LoadAndAddAnimationClip("Assets/Animations/ChickenDance.fbx", "ChickenDance");
	LoadAndAddAnimationClip("Assets/Animations/SillyDancing.fbx", "SillyDancing");
	LoadAndAddAnimationClip("Assets/Animations/TakeDown.fbx", "TakeDown");
	LoadAndAddAnimationClip("Assets/Animations/Stretching.fbx", "Stretching");*/
	//LoadAndAddAnimationClip("Assets/Models/RiggedCube_Anim.fbx", "Test");

	InputManager::GetInstance().AddListener(this);
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
