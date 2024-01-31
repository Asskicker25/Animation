#pragma once

#include <Graphics/ApplicationWindow.h>


class AnimationApplication : public ApplicationWindow
{
public:

	// Inherited via ApplicationWindow
	void SetUp() override;
	void Update() override;
	void Render() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;
};

