#include "EditorLayout.h"
#include "../ApplicationWindow.h"

EditorLayout& EditorLayout::GetInstance()
{
	static EditorLayout instance;
	return instance;
}

void EditorLayout::InitializeLayout()
{
	windowDockPanel = new WindowDockPanel();
	scenePanel = new SceneHierarchyPanel();
	inspectorPanel = new InspectorPanel();
	toolPanel = new ToolPanel();
	sceneViewportPanel = new SceneViewportPanel();

	toolPanel->applicationPlay = &application->applicationPlay;
	sceneViewportPanel->frameBuffer = application->frameBuffer;
}

void EditorLayout::SetSelectedObjects(std::vector<Object*> objects)
{
	if (selectedObjects.size() != 0)
	{
		for (Object* obj : selectedObjects)
		{
			SetSelectedObjectsState(false);
		}
	}

	selectedObjects.clear();

	selectedObjects = objects;
	SetSelectedObjectsState(true);

}

std::vector<Object*>& EditorLayout::GetSelectedObject()
{
	return selectedObjects;
}

void EditorLayout::SetSelectedObjectsState(bool state)
{
	for (Object* obj : selectedObjects)
	{
		obj->isSelected = state;
	}
}

