#pragma once

#include "BasePanel.h"

class ToolPanel : public BasePanel
{
public:

	bool* applicationPlay = nullptr;
	void OnRender(float windowSizeX, float windowSizeY) override;
};

