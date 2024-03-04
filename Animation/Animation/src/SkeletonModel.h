#pragma once
#include <Graphics/Mesh/Model.h>
#include "SkeletonData.h"
#include <map>

class SkeletonModel : public Model
{
public:
	SkeletonModel();
	SkeletonModel(const std::string& path, bool debugModel = false);
	virtual MeshAndMaterial* ProcessMesh(aiMesh* mesh, const aiScene* scene) override;
	virtual void DrawShaded(MeshAndMaterial* mesh, Shader* shader)override ;

	//std::unordered_map<std::shared_ptr<Mesh>, RootNodeInfo*> mListOfMeshRootNodes;

	std::vector<BoneInfo> BoneInfoVec;
	std::map<std::string, int> BoneNameToIdMap;
	BoneNode* RootNode;

private:
	glm::mat4 GlobalInverseTransformation;

	BoneNode* GenerateBoneHeirachy(aiNode* node);
	void CalcualteNodeMatricses(BoneNode* node, glm::mat4& parentTransformationMatrix);
};

