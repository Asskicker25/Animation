#pragma once
#include <Graphics/Mesh/Model.h>
#include "SkeletonData.h"

#include "BaseAnimationHelper.h"

class SkeletonModel : public Model, public BaseAnimationHelper
{
public:
	SkeletonModel();
	SkeletonModel(const std::string& path, bool debugModel = false);
	virtual MeshAndMaterial* ProcessMesh(aiMesh* mesh, const aiScene* scene) override;
	virtual void DrawShaded(MeshAndMaterial* mesh, Shader* shader)override ;

	std::unordered_map<std::shared_ptr<Mesh>, RootNodeInfo*> mListOfMeshRootNodes;

	virtual void SetAnimatedPosition(const glm::vec3& position);
	virtual void SetAnimatedRotation(const glm::vec3& rotation);
	virtual void SetAnimatedRotation(const glm::quat& rotation);
	virtual void SetAnimatedScale(const glm::vec3& scale);
	virtual void SetBaseColor(const glm::vec4& color);

private:
	glm::mat4 GlobalInverseTransformation;

	HeirarchyNode* GenerateBoneHeirachy(aiNode* node);
	void CalcualteNodeMatricses(RootNodeInfo* meshRootNodeInfo, HeirarchyNode* node, glm::mat4& parentTransformationMatrix, std::vector<glm::mat4>& matArray);
};

