#pragma once

#include <Graphics/Mesh/Model.h>
#include "BaseAnimationHelper.h"

class AnimatedObject : public Model, public BaseAnimationHelper
{

public:
	AnimatedObject(bool showEasingColor = true);
	~AnimatedObject();

	// Inherited via BaseAnimationHelper
	void SetAnimatedPosition(const glm::vec3& position) override;
	void SetAnimatedRotation(const glm::vec3& rotation) override;
	void SetAnimatedRotation(const glm::quat& rotation) override;
	void SetAnimatedScale(const glm::vec3& scale) override;


	// Inherited via BaseAnimationHelper
	void SetBaseColor(const glm::vec4& color) override;

	virtual void Start() { Model::Start(); }
	virtual void Update(float deltaTime) { Model::Update(deltaTime); }
	virtual void OnDestroy() { Model::OnDestroy(); }

	virtual void OnSceneDraw() override;
	virtual void OnPropertyDraw() override;

};

