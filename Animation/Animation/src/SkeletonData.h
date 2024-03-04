#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <unordered_map>
#include "BaseKeyFrame.h"

#include <Graphics/Transform.h>

struct BoneInfo
{
	int boneId = 0;
	glm::mat4 mBoneOffset = glm::mat4(1.0f);
	glm::mat4 mFinalTransformation = glm::mat4(1.0f);
	glm::mat4 mGlobalTransformation = glm::mat4(1.0f);
};

struct HeirarchyNode
{
	HeirarchyNode(const std::string& name) : mName(name) { }

	std::string mName;
	Transform transform;
	glm::mat4 mNodeTransformation = glm::mat4(1.0f);
	std::vector<HeirarchyNode*> Children;
};

struct RootNodeInfo
{
	HeirarchyNode* mRootNode = nullptr;
	//std::unordered_map<unsigned int, BoneInfo> mListOfBoneInfos;
	std::unordered_map<std::string, BoneInfo> mListOfBoneInfos;
};

struct BoneWeightInfo
{
	float mBoneId[4] = {0};
	float mBoneWeight[4] = {0};
};

struct NodeAnim
{
	NodeAnim(std::string& name) : mName{ name } {}

	std::string mName;

	std::vector<BaseKeyFrame<glm::vec3>> mListOfPositionKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> mListOfRotationKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> mListOfScaleKeyFrames;
};

struct HumanoidAnimation
{
	std::string mName;
	double mTicksPerSecond;
	double mDuration;

	HeirarchyNode* RootNode;
	std::vector<NodeAnim*> Channels;
};

extern void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g);
extern HeirarchyNode* CreateBoneNode(aiNode* node);

