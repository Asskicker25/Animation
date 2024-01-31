#pragma once

#include "BasePanel.h"

class EntityManager;
class LightManager;

class SceneHierarchyPanel : public BasePanel
{

public:

	SceneHierarchyPanel();

	// Inherited via BasePanel
	void OnRender(float windowSizeX, float windowSizeY) override;

	void ShowEntities();
	void ShowLights();


private:

	EntityManager* entityManager = nullptr;
	LightManager* lightManager = nullptr;
};

