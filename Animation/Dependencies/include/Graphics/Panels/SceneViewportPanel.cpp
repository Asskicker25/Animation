#include "SceneViewportPanel.h"

void SceneViewportPanel::OnRender(float windowSizeX, float windowSizeY)
{
	if (!isOpen) return;

	if (!ImGui::Begin("Viewport", &isOpen) || !isEnabled)
	{
		ImGui::End();
		return;
	}

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();

	ImVec2 imageSize = ImVec2(windowSizeX, windowSizeY);

	ImVec2 uv0 = ImVec2(0.0f, 1.0f);
	ImVec2 uv1 = ImVec2(1.0f, 0.0f);

	ImGui::Image((void*)frameBuffer->GetRendererId(), imageSize, uv0, uv1);

	ImGui::End();
}
