#pragma once

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "LightManager.h"

#include "Material.h"
#include "UnlitColorMaterial.h"
#include "CubeMapTexture.h"
#include "SkyBoxMaterial.h"
#include "DebugCubeData.h"
#include "Timer.h"
#include "Panels/PanelManager.h"
#include "Panels/EditorLayout.h"
#include "FrameBuffer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


class ApplicationWindow
{
private:

	const char* glsl_version = "#version 130";

	GLFWwindow* window;

	void MoveMouse();
	void MoveCameraKeyBoard(GLFWwindow* window);
	void SetViewportSize(GLFWwindow* window, int width, int height);
	void GetCursorCallback(GLFWwindow* window, double xpos, double ypos);

public:
	float moveSpeed{ 10.0f };
	float mouseSens{ 0.1f };

	float windowWidth{ 1280 };
	float windowHeight{ 720 };

	bool mouseHeld{ false };
	bool mouseCameraMove{ false };
	bool stopKeyCallback{ false };
	bool stopMouseCallback{ false };
	bool applicationPlay{ false };

	glm::vec2 currentMousePos{ 0 };
	glm::vec2 lastMousePos{ 0 };
	glm::vec2 mouseDeltaPos{ 0 };

	glm::mat4 view = glm::mat4(1.0f);

	FrameBuffer* frameBuffer;

	DebugModels* debugCubesModel;
	DebugModels* debugCubesData;
	DebugModels* debugSpheres;

	DebugCubeData cubeData;

	Shader solidColorShader;
	Shader defShader;
	Shader alphaBlendShader;
	Shader alphaCutOutShader;
	Shader skyboxShader;

	Model* skyBox;

	Camera* camera;


	ApplicationWindow();
	virtual ~ApplicationWindow() = 0;

	void EngineUpdate();
	void EngineRender();
	
	void InitializeWindow(int windowWidth, int windowHeight);
	void SetWindowIcon(const std::string& path);
	void SetBackgroundColor(const glm::vec3& color);

	void MainLoop();
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ProcessInput(GLFWwindow* window) = 0;
	virtual void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) = 0;
	virtual void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) = 0;

	void MouseHeldCallback(GLFWwindow* window, int& button, int& action, int& mods);
	void InputCallback(GLFWwindow* window, int& key, int& scancode, int& action, int& mods);
};


