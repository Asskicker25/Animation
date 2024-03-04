#include "Shaders.h"

Shaders::Shaders()
{
	mBoneAnimationShader = new Shader();
	mBoneAnimationShader->LoadShader("res/Shader/BoneAnimation.shader");
	mBoneAnimationShader->applyInverseModel = true;
}

Shaders& Shaders::GetInstance()
{
	static Shaders instance;
	return instance;
}