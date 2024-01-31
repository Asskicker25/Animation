#include "SceneHierarchyPanel.h"
#include <iostream>
#include "../EntityManager/EntityManager.h"
#include "../LightManager.h"


SceneHierarchyPanel::SceneHierarchyPanel()
{
	entityManager = &EntityManager::GetInstance();
	lightManager = &LightManager::GetInstance();
}

void SceneHierarchyPanel::OnRender(float windowSizeX, float windowSizeY)
{
	if (!isOpen) return;

	if (!ImGui::Begin("Scene Hierarchy", &isOpen) || !isEnabled)
	{
		ImGui::End();
		return;
	}

	ShowLights();
	ShowEntities();
	
	ImGui::End();
}

void SceneHierarchyPanel::ShowEntities()
{
	if (!ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	std::unordered_map<std::string, Entity*>::iterator it;

	for (it = entityManager->listOfEntities.begin(); it != entityManager->listOfEntities.end(); ++it)
	{
		it->second->OnSceneDraw();
	}

}

void SceneHierarchyPanel::ShowLights()
{
	if (!ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	std::vector<Light*> lights = lightManager->GetListOfLights();

	for (Light* light : lights)
	{
		light->OnSceneDraw();
	}
}
