#include "ToolPanel.h"

void ToolPanel::OnRender(float windowSizeX, float windowSizeY)
{
	if (!isOpen) return;

	ImGuiWindowFlags window_flags = 0;

	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_MenuBar;

	float panelSizeX = windowSizeX;
	float panelSizeY = windowSizeY / 40;

	float panelPosX = 0;
	float panelPosY = 0 + panelSizeY / 10;

	ImGui::SetNextWindowSize(ImVec2(panelSizeX, panelSizeY));
	ImGui::SetNextWindowPos(ImVec2(panelPosX, panelPosY));

	if (!ImGui::Begin("ToolPanel", &isOpen, window_flags) || !isEnabled)
	{
		ImGui::End();
		return;
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();

		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(panelSizeX * 0.5f,0));
		ImGui::Spacing();
		ImGui::PopStyleVar();

		if (ImGui::Button(*applicationPlay ? "Pause" : "Play"))
		{
			*applicationPlay = !(*applicationPlay);
		}

		ImGui::EndMenuBar();
	}


	ImGui::End();
}
