#include "Character.h"
#include "../Shaders/Shaders.h"

BoneInfo* bone;

glm::vec3 pos, rot, scale;

Character::Character()
{
	shader = Shaders::GetInstance().mBoneAnimationShader;
	//character->LoadModel("Assets/Models/Character_Idle.fbx");
	//character->LoadModel("Assets/Models/Ninja.fbx");
	LoadModel("Assets/Models/RaceDriver.fbx");
	meshes[0]->material->AsMaterial()->diffuseTexture = new Texture("Assets/Models/RaceDriver.png");
	transform.SetScale(glm::vec3(0.08f));

	AnimationClip* clip1 = new AnimationClip();
	clip1->SetCurrentKeyType(POSITION);
	clip1->AddKeyFrame(glm::vec3(0, 0.0f, 0), 0);
	clip1->AddKeyFrame(glm::vec3(5, 0.0f, 0), 5.0f, SineEaseIn);

	AddAnimationClip(clip1);

	InputManager::GetInstance().AddListener(this);

	std::unordered_map<std::string, BoneInfo>::iterator it = 
		mListOfMeshRootNodes[meshes[0]->mesh]->mListOfBoneInfos.find("mixamorig6:Head");

	bone = &it->second;
	pos = glm::vec3(0,-150,0);
	bone->mBoneOffset = glm::translate(glm::mat4(1.0f), pos);
}

void Character::OnKeyPressed(const int& key)
{
	/*if (key == GLFW_KEY_D)
	{
		pos.x += 20;
		bone->mBoneOffset = glm::translate(glm::mat4(1.0f), pos);
	}
	else if(key == GLFW_KEY_A)
	{
		pos.x -= 20;
		bone->mBoneOffset = glm::translate(glm::mat4(1.0f), pos);
	}*/
}
