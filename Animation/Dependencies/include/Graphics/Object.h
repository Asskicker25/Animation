#pragma once

#include "Debugger.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "Panels/ImguiDrawUtils.h"

class Object
{
public:
	
	int id;

	bool isSelected = false;
	bool isEnabled = true;

	Object();
	virtual void OnPropertyDraw() = 0;
	virtual void OnSceneDraw() = 0;
};

