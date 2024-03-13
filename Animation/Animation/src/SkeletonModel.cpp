#include "SkeletonModel.h"
#include "AnimationSystem.h"

#include <Graphics/MathUtils.h>
#include <Graphics/Panels/ImguiDrawUtils.h>
#include <Graphics/Material/UnlitColorMaterial.h>


using namespace MathUtilities;

SkeletonModel::SkeletonModel() : Model()
{
	//AnimationSystem::GetInstance().AddAnimatedObject(this);
}

SkeletonModel::SkeletonModel(const std::string& path, bool debugModel) : Model(path, debugModel)
{
}

void SkeletonModel::SetAnimatedPosition(const glm::vec3& position)
{
	transform.SetPosition(position);
}

void SkeletonModel::SetAnimatedRotation(const glm::vec3& rotation)
{
	transform.SetRotation(rotation);
}

void SkeletonModel::SetAnimatedRotation(const glm::quat& rotation)
{
	transform.SetQuatRotation(rotation);
}

void SkeletonModel::SetAnimatedScale(const glm::vec3& scale)
{
	transform.SetScale(scale);
}

void SkeletonModel::SetBaseColor(const glm::vec4& color)
{
	for (MeshAndMaterial* mesh : meshes)
	{
		mesh->material->AsMaterial()->SetBaseColor(color);
	}
}

void SkeletonModel::OnPropertyDraw()
{
	SkeletonModel::OnPropertyDraw();

	if (!ImGui::TreeNodeEx("Animation", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGuiUtils::DrawBool("EnableControlTime", mControlTime);
	ImGuiUtils::DrawDragFloat("ControlTime", mControlTimeParam, 0.001f, 0, 1);

	ImGui::TreePop();
}

void SkeletonModel::Update(float deltaTime)
{
	if (!mIsPlaying) return;

	if (deltaTime > 1.0f / 60.0f) { deltaTime = 1.0f / 60.0f; }

	if (!mControlTime)
	{
		mCurrentTime += deltaTime * 1000;

		if (mCurrentAnimation->mLoop && mCurrentTime > mCurrentAnimation->mDuration)
		{
			mCurrentTime = 0;
		}
	}
	else
	{
		mCurrentTime = MathUtils::Remap(mControlTimeParam, 0, 1, 0, mCurrentAnimation->mDuration);
	}

	//Debugger::Print("Current Time :", mCurrentTime);

	AnimateNodes(deltaTime);
}

void SkeletonModel::LoadAndAddAnimationClip(const std::string& path, const std::string& animName, bool loop)
{
	Assimp::Importer importer;

	SkeletalAnimation* newAnimation = new SkeletalAnimation();
	newAnimation->mLoop = loop;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	assert(scene && scene->mAnimations[0]);
	aiAnimation* animation = scene->mAnimations[0];
	newAnimation->mDuration = animation->mDuration;
	newAnimation->mTicksPerSecond = animation->mTicksPerSecond;
	newAnimation->mName = scene->mRootNode->mName.C_Str();

	int channelSize = animation->mNumChannels;

	for (int i = 0; i < channelSize; i++)
	{
		aiNodeAnim* channel = animation->mChannels[i];
		NodeAnim* nodeAnim = new NodeAnim(channel->mNodeName.C_Str(), channel);
		newAnimation->Channels.push_back(nodeAnim);
	}

	mListOfSkeletalAnimations[animName] = newAnimation;

	mCurrentAnimation = newAnimation;

}

MeshAndMaterial* SkeletonModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	RootNodeInfo* rootNodeInfo  = new RootNodeInfo();

	rootNodeInfo->mRootNode = GenerateBoneHeirachy(rootNodeInfo, scene->mRootNode);
	GlobalInverseTransformation = glm::inverse(rootNodeInfo->mRootNode->mNodeTransformation);


#pragma region Bones

	std::vector<BoneWeightInfo> boneInfos;

	if (mesh->HasBones())
	{
		boneInfos.resize(mesh->mNumVertices);
		unsigned int numOfBones = mesh->mNumBones;

		for (unsigned int boneId = 0; boneId < numOfBones; boneId++)
		{
			aiBone* bone = mesh->mBones[boneId];
			std::string name(bone->mName.C_Str(), bone->mName.length);
			//unsigned int hashValue = MathUtils::GetHash(name);

			BoneInfo boneInfo;

			boneInfo.boneId = boneId;
			AssimpToGLM(bone->mOffsetMatrix, boneInfo.mBoneOffset);
			rootNodeInfo->mListOfBoneInfos[name] = boneInfo;

			Debugger::Print("Bone : ", bone->mName.C_Str());
			Debugger::Print("Bone ID : ", boneId);
			//Debugger::Print("Bone Weight Count : ", bone->mNumWeights);

			for (int weightId = 0; weightId < bone->mNumWeights; weightId++)
			{

				aiVertexWeight& vertexWeight = bone->mWeights[weightId];

				BoneWeightInfo& boneWeightInfo = boneInfos[vertexWeight.mVertexId];

				for (int infoId = 0; infoId < 4; infoId++)
				{
					if (boneWeightInfo.mBoneWeight[infoId] == 0)
					{
						boneWeightInfo.mBoneId[infoId] = boneId;
						boneWeightInfo.mBoneWeight[infoId] = vertexWeight.mWeight;
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

			BoneWeightInfo& boneInfo = boneInfos[i];

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

	mListOfMeshRootNodes[meshInstance] = rootNodeInfo;

	return new MeshAndMaterial{ meshInstance, meshMat };
}

HeirarchyNode* SkeletonModel::GenerateBoneHeirachy(RootNodeInfo* rootNodeInfo, aiNode* node)
{
	HeirarchyNode* boneNode = CreateBoneNode(node);

	rootNodeInfo->mListOfNodes[boneNode->mName] = boneNode;

	//Debugger::Print("Bone Name : ", boneNode->mName);

	for (int i = 0; i < node->mNumChildren; i++)
	{
		boneNode->Children.emplace_back(GenerateBoneHeirachy(rootNodeInfo, node->mChildren[i]));
	}

	return boneNode;
}

void SkeletonModel::DrawShaded(MeshAndMaterial* mesh, Shader* shader)
{
	shader->Bind();

	shader->SetUniform1i("useBones", true);

	RootNodeInfo* meshRootNodeInfo = mListOfMeshRootNodes[mesh->mesh];

	glm::mat4 rootTransformation = glm::mat4(1.0f);
	std::vector<glm::mat4> boneMatrices;

	boneMatrices.resize(meshRootNodeInfo->mListOfBoneInfos.size());

	CalcualteNodeMatricses(meshRootNodeInfo, meshRootNodeInfo->mRootNode, rootTransformation, boneMatrices);

	shader->SetUniformMatrix4fv("boneMatrices", meshRootNodeInfo->mListOfBoneInfos.size(), GL_FALSE, glm::value_ptr(boneMatrices[0]));

	Model::DrawShaded(mesh, shader);

}

void SkeletonModel::CalcualteNodeMatricses(RootNodeInfo* meshRootNodeInfo, HeirarchyNode* node, glm::mat4& parentTransformationMatrix,
	std::vector<glm::mat4>& matArray)
{
	glm::mat4 transformMatrix = node->mNodeTransformation;

	glm::mat4 globalTransformation = parentTransformationMatrix * transformMatrix;

	std::unordered_map<std::string, BoneInfo>::iterator it = meshRootNodeInfo->mListOfBoneInfos.find(node->mName);

	if (it != meshRootNodeInfo->mListOfBoneInfos.end())
	{
		BoneInfo& boneInfo = it->second;

		boneInfo.mFinalTransformation = /*GlobalInverseTransformation **/ globalTransformation * boneInfo.mBoneOffset;
		boneInfo.mGlobalTransformation = globalTransformation;

		matArray[boneInfo.boneId] = boneInfo.mFinalTransformation;
	}

	for (int i = 0; i < node->Children.size(); i++)
	{
		CalcualteNodeMatricses(meshRootNodeInfo, node->Children[i], globalTransformation, matArray);
	}

}



void SkeletonModel::AnimateNodes(float deltaTime)
{
	for (MeshAndMaterial* mesh : meshes)
	{
		std::unordered_map<std::string, BoneInfo>& mListOfBoneInfos = mListOfMeshRootNodes[mesh->mesh]->mListOfBoneInfos;
		std::unordered_map<std::string, HeirarchyNode*>& mListOfNodes = mListOfMeshRootNodes[mesh->mesh]->mListOfNodes;

		//for (int i = 0; i < mCurrentAnimation->Channels.size(); ++i)
		int i = 0;
		for (NodeAnim* nodeAnim : mCurrentAnimation->Channels)
		{
			std::string boneName = nodeAnim->mName;

			std::unordered_map<std::string, BoneInfo>::iterator boneInfoIt = mListOfBoneInfos.find(boneName);
			std::unordered_map<std::string, HeirarchyNode*>::iterator boneNodeIt = mListOfNodes.find(boneName);

			if (boneInfoIt == mListOfBoneInfos.end()) continue;
			if (boneNodeIt == mListOfNodes.end()) continue;

			BoneInfo& boneInfo = boneInfoIt->second;
			HeirarchyNode* node = boneNodeIt->second;

			glm::vec3 animatedPos = AnimationSystem::GetInstance().HandleKeyFrames_Vector3(
				mCurrentTime, nodeAnim->mListOfPositionKeyFrames
			);

			glm::quat animatedRot = AnimationSystem::GetInstance().HandleKeyFrames_Quaternion(
				mCurrentTime, nodeAnim->mListOfRotationKeyFrames
			);

			glm::vec3 animatedScale = AnimationSystem::GetInstance().HandleKeyFrames_Vector3(
				mCurrentTime, nodeAnim->mListOfScaleKeyFrames
			);

			node->mNodeTransformation = glm::translate(glm::mat4(1.0f), animatedPos)
				* glm::toMat4(animatedRot)
				* glm::scale(glm::mat4(1.0f), animatedScale);

			/*if (i == 0)
			{
				Debugger::Print("Node 1 Pos : ", animatedPos);
			}*/

			i++;
		}
	}
}

void SkeletonModel::PlayAnimation(const std::string& name)
{
	mCurrentAnimation = mListOfSkeletalAnimations[name];
	mCurrentTime = 0;
}

SkeletonModel* SkeletonModel::CopyFromOther(const SkeletonModel& other, bool initialize)
{
	CopyFromModel(other, initialize);

	this->mIsPlaying = other.mIsPlaying;
	this->mCurrentTime = other.mCurrentTime;
	this->mControlTime = other.mControlTime;
	this->mControlTimeParam = other.mControlTimeParam;
	this->mCurrentAnimation = other.mCurrentAnimation;
	this->mListOfMeshRootNodes = other.mListOfMeshRootNodes;
	this->mListOfSkeletalAnimations = other.mListOfSkeletalAnimations;

	return this;
}
