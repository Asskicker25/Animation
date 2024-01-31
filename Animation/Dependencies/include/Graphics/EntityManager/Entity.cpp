#include "Entity.h"
#include "EntityManager.h"
#include "../Panels/EditorLayout.h"

void Entity::InitializeEntity(Entity* entity)
{
	EntityManager::GetInstance().AddEntity(entity);
}

void Entity::OnSceneDraw()
{
	if (ImGui::Selectable(name.c_str(), &isSelected))
	{
		EditorLayout::GetInstance().SetSelectedObjects({ this });
	}
}

void Entity::OnPropertyDraw()
{
	ImGui::InputText("##ObjectName", &name[0], 516);
	ImGui::SameLine();
	ImGui::InputText("##Tag", &tag[0], 516);
	transform.OnPropertyDraw();
}

void Entity::Destroy()
{
	EntityManager::GetInstance().RemoveEntity(entityId);
}

