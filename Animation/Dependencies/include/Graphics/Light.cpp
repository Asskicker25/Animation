#include "Light.h"
#include "LightManager.h"
#include "UnlitColorMaterial.h"
#include "Renderer.h"
#include "Panels/EditorLayout.h"

float Light::lightModelScale = 0.1f;

Light::Light(LightType newLightType) : lightType{ newLightType }
{
	intensity = 0.5f;
	attenuation = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	innerAngle = 30;
	outerAngle = 50;

	material.SetBaseColor(glm::vec4(1));

	InitializeLight(newLightType);
}

Light::Light() : lightType{ Point }
{
	intensity = 0.5f;
	attenuation = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	innerAngle = 30;
	outerAngle = 50;

	material.SetBaseColor(glm::vec4(1));
}

Light::~Light()
{
}

void Light::InitializeLight(LightType lightType)
{
	this->lightType = lightType;

	LoadModel("res/Models/DefaultSphere.fbx", true);
	transform.SetScale(glm::vec3(lightModelScale));
	shader = Renderer::GetInstance().solidColorShader;
	meshes[0]->material = new UnlitColorMaterial();

	meshes[0]->material->AsUnlitMaterial()->SetBaseColor(material.GetBaseColor());

	LightManager::GetInstance().AddLight(this);
	Renderer::GetInstance().AddModel(this);
}

glm::vec4 Light::GetLightColor()
{
	glm::vec4 baseColor = glm::vec4(
		material.GetBaseColor().x * intensity,
		material.GetBaseColor().y * intensity,
		material.GetBaseColor().z * intensity,
		material.GetBaseColor().w);

	return baseColor;
}

glm::vec4 Light::GetAmbientColor()
{
	glm::vec4 ambientColor = glm::vec4(
		material.GetAmbientColor().x * intensity,
		material.GetAmbientColor().y * intensity,
		material.GetAmbientColor().z * intensity,
		material.GetAmbientColor().w);

	return ambientColor;
}

//glm::vec3 Light::GetSpecularColor()
//{
//	return glm::vec3(material.specularValue);
//}

float Light::GetAmbientValue()
{
	return material.ambientValue;
}

//float Light::GetSpecularValue()
//{
//	return material.specularValue;
//}

void Light::SetLightColor(glm::vec4 color)
{
	material.SetBaseColor(color);
}

void Light::SetAmbientColor(glm::vec4 color)
{
	material.SetAmbientColor(color);
}

void Light::SetAmbientValue(float ambientValue)
{
	material.ambientValue = ambientValue;
}

void Light::OnDestroy()
{
}

void Light::OnPropertyDraw()
{
	Model::OnPropertyDraw();
}

void Light::OnSceneDraw()
{
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	node_flags |= ImGuiTreeNodeFlags_SpanFullWidth;
	node_flags |= ImGuiTreeNodeFlags_Leaf;

	if (isSelected)
	{
		node_flags |= ImGuiTreeNodeFlags_Selected;
	}

	bool node_open = ImGui::TreeNodeEx(name.c_str(), node_flags);

	if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
	{
		EditorLayout::GetInstance().SetSelectedObjects({ this });
	}
}

//void Light::SetSpecualrValue(float specularValue)
//{
//	material.specularValue = specularValue;
//}

