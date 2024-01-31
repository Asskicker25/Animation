#pragma once

#include "WindowDockPanel.h"
#include "SceneHierarchyPanel.h"
#include "InspectorPanel.h"
#include "ToolPanel.h"
#include "SceneViewportPanel.h"

class Object;
class ApplicationWindow;

class EditorLayout
{

public:

	static EditorLayout& GetInstance();

	void InitializeLayout();
	void SetSelectedObjects(std::vector<Object*> objects);
	std::vector<Object*>& GetSelectedObject();

	ApplicationWindow* application;

private:

	WindowDockPanel* windowDockPanel;
	SceneHierarchyPanel* scenePanel;
	InspectorPanel* inspectorPanel;
	ToolPanel* toolPanel;
	SceneViewportPanel* sceneViewportPanel;

	std::vector<Object*> selectedObjects;

	void SetSelectedObjectsState(bool state);

};

