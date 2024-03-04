#include "SkeletonModel.h"

#include <Graphics/MathUtils.h>
#include <Graphics/Material/UnlitColorMaterial.h>


using namespace MathUtilities;

SkeletonModel::SkeletonModel() : Model()
{
}

SkeletonModel::SkeletonModel(const std::string& path, bool debugModel) : Model(path, debugModel)
{
}

MeshAndMaterial* SkeletonModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	RootNodeInfo* rootNodeInfo  = new RootNodeInfo();

	RootNode = GenerateBoneHeirachy(scene->mRootNode);
	GlobalInverseTransformation = glm::inverse(RootNode->mNodeTransformation);
#pragma region Bones

	std::vector<BoneWeightInfo> boneWeights;

	if (mesh->HasBones())
	{
		boneWeights.resize(mesh->mNumVertices);
		unsigned int numBones = mesh->mNumBones;
		for (unsigned int boneIdx = 0; boneIdx < numBones; ++boneIdx)
		{
			aiBone* bone = mesh->mBones[boneIdx];

			std::string name(bone->mName.C_Str(), bone->mName.length); //	'\0'
			BoneNameToIdMap.insert(std::pair<std::string, int>(name, boneIdx));

			// Store the offset matrices
			BoneInfo info;
			AssimpToGLM(bone->mOffsetMatrix, info.mBoneOffset);
			BoneInfoVec.emplace_back(info);
			printf("\n-----------\n");
			printf("Bone: %s\n", name.c_str());
			printf("Number of weights: %d\n", bone->mNumWeights);

			for (int weightIdx = 0; weightIdx < bone->mNumWeights; ++weightIdx)
			{
				aiVertexWeight& vertexWeight = bone->mWeights[weightIdx];

				BoneWeightInfo& boneInfo = boneWeights[vertexWeight.mVertexId];
				for (int infoIdx = 0; infoIdx < 4; ++infoIdx)
				{
					if (boneInfo.mBoneWeight[infoIdx] == 0.f)
					{
						boneInfo.mBoneId[infoIdx] = boneIdx;
						boneInfo.mBoneWeight[infoIdx] = vertexWeight.mWeight;
						break;
					}
				}
			}
		}
	}

#pragma endregion


#pragma region Vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 temp;
		glm::vec4 temp4;

		temp.x = mesh->mVertices[i].x;
		temp.y = mesh->mVertices[i].y;
		temp.z = mesh->mVertices[i].z;

		vertex.positions = temp;

		if (mesh->HasNormals())
		{
			temp.x = mesh->mNormals[i].x;
			temp.y = mesh->mNormals[i].y;
			temp.z = mesh->mNormals[i].z;

			vertex.normals = temp;
		}

		if (mesh->HasVertexColors(0))
		{
			aiColor4D color = mesh->mColors[0][i];
			vertex.color = glm::vec4(color.r, color.g, color.b, color.a);
		}
		else
		{
			vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		}


		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;

		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);


		if (mesh->HasBones())
		{

			BoneWeightInfo& boneInfo = boneWeights[i];

			temp4.x = boneInfo.mBoneId[0];
			temp4.y = boneInfo.mBoneId[1];
			temp4.z = boneInfo.mBoneId[2];
			temp4.w = boneInfo.mBoneId[3];

			vertex.boneIds = temp4;

			temp4.x = boneInfo.mBoneWeight[0];
			temp4.y = boneInfo.mBoneWeight[1];
			temp4.z = boneInfo.mBoneWeight[2];
			temp4.w = boneInfo.mBoneWeight[3];

			vertex.boneWeights = temp4;

		}

		vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}


#pragma endregion


#pragma region Material

	BaseMaterial* meshMat;
	aiColor4D baseColor(1.0f, 1.0f, 1.0f, 1.0f);


	if (mesh->mMaterialIndex >= 0)
	{
		meshMat = new Material();
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		meshMat->AsMaterial()->diffuseTexture = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		meshMat->AsMaterial()->specularTexture = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		meshMat->AsMaterial()->alphaMask = LoadMaterialTextures(material, aiTextureType_OPACITY, "texture_opacity");

		if (((Texture*)meshMat->AsMaterial()->alphaMask)->path != "res/Textures/DefaultTextures/Opacity_Default.png")
		{
			meshMat->AsMaterial()->useMaskTexture = true;
		}

		meshMat->AsMaterial()->SetBaseColor(glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a));

	}
	else
	{
		meshMat = new UnlitColorMaterial();
		meshMat->AsUnlitMaterial()->SetBaseColor(glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a));
	}

	std::string meshName = mesh->mName.C_Str();

	if (meshName == "")
	{
		meshName = "Mesh " + std::to_string(meshes.size());
	}
#pragma endregion


	std::shared_ptr<Mesh> meshInstance = std::make_shared<Mesh>(vertices, indices, meshName);

	//mListOfMeshRootNodes[meshInstance] = rootNodeInfo;

	return new MeshAndMaterial{ meshInstance, meshMat };
}

BoneNode* SkeletonModel::GenerateBoneHeirachy(aiNode* node)
{
	BoneNode* boneNode = CreateBoneNode(node);


	aiMatrix4x4& transformation = node->mTransformation;
	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scaling;
	transformation.Decompose(scaling, rotation, position);
	
	glm::mat4 glmMatrix;
	AssimpToGLM(transformation, glmMatrix);


	for (int i = 0; i < node->mNumChildren; ++i)
	{
		boneNode->Children.emplace_back(GenerateBoneHeirachy(node->mChildren[i]));
	}
	return boneNode;
}


void SkeletonModel::DrawShaded(MeshAndMaterial* mesh, Shader* shader)
{
	shader->Bind();

	shader->SetUniform1i("useBones", true);

	//RootNodeInfo* meshRootNodeInfo = mListOfMeshRootNodes[mesh->mesh];

	glm::mat4 rootTransformation = glm::mat4(1.0f);

	CalcualteNodeMatricses(RootNode, rootTransformation);

	for (int i = 0; i < BoneInfoVec.size(); ++i)
	{
		shader->SetUniformMatrix4fv("boneMatrices[" + std::to_string(i) + "]", 1, GL_FALSE, glm::value_ptr(rootTransformation));
	}

	//shader->SetUniformMatrix4fv("boneMatrices", meshRootNodeInfo->mBoneInfoVec.size(), GL_FALSE, glm::value_ptr(meshRootNodeInfo->mBoneInfoVec[0]));

	Model::DrawShaded(mesh, shader);

}




void SkeletonModel::CalcualteNodeMatricses(BoneNode* node, glm::mat4& parentTransformationMatrix)
{
	//Debugger::Print("Bone calc : ", node->mName);
	//unsigned int nodeHash = MathUtils::GetHash(node->mName);

	glm::mat4 transformMatrix = node->mNodeTransformation;

	glm::mat4 globalTransformation = parentTransformationMatrix * transformMatrix;

	std::map<std::string, int>::iterator it = BoneNameToIdMap.find(node->mName);

	if (it != BoneNameToIdMap.end())
	{
		BoneInfo& boneInfo = BoneInfoVec[it->second];
		boneInfo.mFinalTransformation = GlobalInverseTransformation * globalTransformation * boneInfo.mBoneOffset;
		boneInfo.mGlobalTransformation = globalTransformation;

	}

	for (int i = 0; i < node->Children.size(); i++)
	{
		CalcualteNodeMatricses(node->Children[i], globalTransformation);
	}

	//shader->SetUniformMatrix4fv("boneMatrices", numInstances, GL_FALSE, glm::value_ptr(boneMatrices[0]));

}
