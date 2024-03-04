#pragma once
#include <Graphics/Mesh/Model.h>
#include "SkeletonData.h"


class SkeletonModel : public Model
{
public:
	SkeletonModel();
	SkeletonModel(const std::string& path, bool debugModel = false);
	virtual MeshAndMaterial* ProcessMesh(aiMesh* mesh, const aiScene* scene) override;
	virtual void DrawShaded(MeshAndMaterial* mesh, Shader* shader)override ;

	std::unordered_map<std::shared_ptr<Mesh>, RootNodeInfo*> mListOfMeshRootNodes;

private:
	glm::mat4 GlobalInverseTransformation;

	BoneNode* GenerateBoneHeirachy(aiNode* node);
	void CalcualteNodeMatricses(RootNodeInfo* meshRootNodeInfo, BoneNode* node, glm::mat4& parentTransformationMatrix, std::vector<glm::mat4>& matArray);
};

