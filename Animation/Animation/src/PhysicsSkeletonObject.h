#pragma once
#pragma once
#include <Physics/PhysX_Object.h>
#include "SkeletonData.h"

#include "BaseAnimationHelper.h"

class PhysicsSkeletonObject : public PhysX_Object, public BaseAnimationHelper
{
public:
	PhysicsSkeletonObject();
	PhysicsSkeletonObject(const std::string& path, bool debugModel = false);
	virtual MeshDataHolder* ProcessMesh(aiMesh* mesh, const aiScene* scene) override;
	virtual void DrawShaded(MeshAndMaterial* mesh, Shader* shader)override;

	std::unordered_map<std::string, RootNodeInfo*> mListOfMeshRootNodes;
	std::unordered_map<std::string, SkeletalAnimation*> mListOfSkeletalAnimations;

	virtual void SetAnimatedPosition(const glm::vec3& position);
	virtual void SetAnimatedRotation(const glm::vec3& rotation);
	virtual void SetAnimatedRotation(const glm::quat& rotation);
	virtual void SetAnimatedScale(const glm::vec3& scale);
	virtual void SetBaseColor(const glm::vec4& color);

	virtual void OnPropertyDraw();

	virtual void Update(float deltaTime) override;
	void LoadAndAddAnimationClip(const std::string& path, const std::string& animName, bool loop = true);
	void AnimateNodes(float deltaTime);

	void PlayAnimation(const std::string& name);


	PhysicsSkeletonObject* CopyFromOther(const PhysicsSkeletonObject& other, bool initialize = false);

	bool mIsPlaying = false;
	float mCurrentTime = 0;

private:
	glm::mat4 GlobalInverseTransformation;
	SkeletalAnimation* mCurrentAnimation = nullptr;


	HeirarchyNode* GenerateBoneHeirachy(RootNodeInfo* rootNodeInfo, aiNode* node);
	void CalcualteNodeMatricses(RootNodeInfo* meshRootNodeInfo, HeirarchyNode* node, glm::mat4& parentTransformationMatrix, std::vector<glm::mat4>& matArray);
};

