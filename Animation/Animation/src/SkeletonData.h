#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <unordered_map>

#include <Graphics/Transform.h>

struct BoneInfo
{
	int boneId = 0;
	glm::mat4 mBoneOffset = glm::mat4(1.0f);
	glm::mat4 mFinalTransformation = glm::mat4(1.0f);
	glm::mat4 mGlobalTransformation = glm::mat4(1.0f);
};

struct BoneNode
{
	BoneNode(const std::string& name) : mName(name) { }

	std::string mName;
	Transform transform;
	glm::mat4 mNodeTransformation = glm::mat4(1.0f);
	std::vector<BoneNode*> Children;
};

struct RootNodeInfo
{
	BoneNode* mRootNode = nullptr;
	std::unordered_map<std::string, int> mBoneNameToIdMap;
	std::vector<BoneInfo> mBoneInfoVec;
};

struct BoneWeightInfo
{
	float mBoneId[4] = {0};
	float mBoneWeight[4] = {0};
};

extern void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g);
extern BoneNode* CreateBoneNode(aiNode* node);

