#include "SkeletonData.h"
#include <MathUtils.h>
#include "BaseKeyFrame.h"

using namespace MathUtilities;

void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g)
{
	g[0][0] = a.a1; g[0][1] = a.b1; g[0][2] = a.c1; g[0][3] = a.d1;
	g[1][0] = a.a2; g[1][1] = a.b2; g[1][2] = a.c2; g[1][3] = a.d2;
	g[2][0] = a.a3; g[2][1] = a.b3; g[2][2] = a.c3; g[2][3] = a.d3;
	g[3][0] = a.a4; g[3][1] = a.b4; g[3][2] = a.c4; g[3][3] = a.d4;
}

glm::vec3 AssimpToGLM(const aiVector3D& vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

glm::quat AssimpToGLM(const aiQuaternion& quat)
{
	return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

HeirarchyNode* CreateBoneNode(aiNode* node)
{
	HeirarchyNode* newNode = new HeirarchyNode(node->mName.C_Str());

	AssimpToGLM(node->mTransformation, newNode->mNodeTransformation);

	//glm::vec3 pos, rot, scale;

	//MathUtils::DecomposeTransform_Simple(newNode->mNodeTransformation, pos, rot, scale);

	//newNode->transform.position = pos;
	//newNode->transform.SetRotation(rot);
	//newNode->transform.SetScale(scale);

	//Debugger::Print("Bone Name : ", newNode->mName);
	//Debugger::Print("Bone Pos : ", pos);
	//Debugger::Print("Bone Rot : ", rot);
	//Debugger::Print("Bone scale : ", scale);
	return newNode;
}

void NodeAnim::AddKeyFrame(const glm::vec3& value, float time, EasingType easingType)
{
	switch (currentKeyType)
	{
	case POSITION:

		mListOfPositionKeyFrames.push_back({ value, time, easingType });
		break;

	case ROTATION:

		mListOfRotationKeyFrames.push_back({ value, time, easingType });
		break;

	case SCALE:

		mListOfScaleKeyFrames.push_back({ value, time, easingType });
		break;

	default:
		break;
	}
}


NodeAnim::NodeAnim(const std::string& name, const aiNodeAnim* channel) : mName{ name }
{
	currentKeyType = POSITION;
	for (int posIndex = 0; posIndex < channel->mNumPositionKeys; ++posIndex)
	{
		aiVector3D aiPosition = channel->mPositionKeys[posIndex].mValue;
		float timeStamp = channel->mPositionKeys[posIndex].mTime;
		glm::vec3 pos = AssimpToGLM(aiPosition);

		//Debugger::Print("Pos Time : " + std::to_string(posIndex), timeStamp);

		AddKeyFrame(pos, timeStamp, EasingType::Linear);
	}

	currentKeyType = ROTATION;
	for (int rotIndex = 0; rotIndex < channel->mNumRotationKeys; ++rotIndex)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotIndex].mTime;
		glm::quat rot = AssimpToGLM(aiOrientation);
		glm::vec3 eulerRot = glm::degrees(glm::eulerAngles(rot));

		AddKeyFrame(eulerRot, timeStamp, EasingType::Linear);
	}

	currentKeyType = SCALE;
	for (int scaleIndex = 0; scaleIndex < channel->mNumScalingKeys; ++scaleIndex)
	{
		aiVector3D aiScale = channel->mScalingKeys[scaleIndex].mValue;
		float timeStamp = channel->mScalingKeys[scaleIndex].mTime;
		glm::vec3 scale = AssimpToGLM(aiScale);

		AddKeyFrame(scale, timeStamp, EasingType::Linear);
	}

}

