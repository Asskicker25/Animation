#pragma once

#include <Graphics/Scene/BaseScene.h>
#include <Graphics/Camera/GameCamera.h>
#include <Graphics/Light/Light.h>

using namespace Scene;

class AnimationApplication;

class Scene_One : public BaseScene
{
public:

	Scene_One(AnimationApplication* application);

	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;

	void ShutDown();

private:

	AnimationApplication* mApplication = nullptr;
	GameCamera* mMainCamera = nullptr;
	Light* mDirLight = nullptr;

};

