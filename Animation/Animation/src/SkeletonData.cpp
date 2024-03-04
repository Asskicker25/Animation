#include "SkeletonData.h"
#include <Graphics/MathUtils.h>

using namespace MathUtilities;

void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g)
{
	g[0][0] = a.a1; g[0][1] = a.b1; g[0][2] = a.c1; g[0][3] = a.d1;
	g[1][0] = a.a2; g[1][1] = a.b2; g[1][2] = a.c2; g[1][3] = a.d2;
	g[2][0] = a.a3; g[2][1] = a.b3; g[2][2] = a.c3; g[2][3] = a.d3;
	g[3][0] = a.a4; g[3][1] = a.b4; g[3][2] = a.c4; g[3][3] = a.d4;
}

BoneNode* CreateBoneNode(aiNode* node)
{
	BoneNode* newNode = new BoneNode(node->mName.C_Str());

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
