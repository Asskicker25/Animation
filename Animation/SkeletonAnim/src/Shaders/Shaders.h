#pragma once

#include <Graphics/Shaders/Shader.h>

class Shaders
{
public:

	Shaders();

	static Shaders& GetInstance();

	Shader* mBoneAnimationShader = nullptr;
};

