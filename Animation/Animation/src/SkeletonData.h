#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <unordered_map>
#include "BaseKeyFrame.h"
#include "AnimationClip.h"

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
	std::unordered_map<std::string, HeirarchyNode*> mListOfNodes;
};

struct BoneWeightInfo
{
	float mBoneId[4] = {0};
	float mBoneWeight[4] = {0};
};

struct NodeAnim
{
	NodeAnim(const std::string& name, const aiNodeAnim* channel);

	std::string mName;
	KeyFrameType currentKeyType = POSITION;

	glm::mat4 mLocalTransformMatrix = glm::mat4(1.0f);

	std::vector<BaseKeyFrame<glm::vec3>> mListOfPositionKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> mListOfRotationKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> mListOfScaleKeyFrames;

	void AddKeyFrame(const glm::vec3& value, float time, EasingType easingType);

};

struct SkeletalAnimation
{
	std::string mName = "Empty";

	bool mLoop = true;

	double mTicksPerSecond = 30;
	double mDuration = 0;

	HeirarchyNode* RootNode = nullptr;
	std::vector<NodeAnim*> Channels;
};

extern void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g);
extern glm::vec3 AssimpToGLM(const aiVector3D& vec);
extern glm::quat AssimpToGLM(const aiQuaternion& quat);
extern HeirarchyNode* CreateBoneNode(aiNode* node);

