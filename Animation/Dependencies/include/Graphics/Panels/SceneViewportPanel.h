#pragma once

#include "BasePanel.h"
#include "../FrameBuffer.h"

class SceneViewportPanel : public BasePanel
{
public:

	// Inherited via BasePanel
	void OnRender(float windowSizeX, float windowSizeY) override;

	FrameBuffer* frameBuffer = nullptr;

};

