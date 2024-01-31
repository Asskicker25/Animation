#pragma once

#include <Graphics/Model.h>
#include "BaseAnimationHelper.h"

class AnimatedObject : public Model, public BaseAnimationHelper
{

public:
	AnimatedObject();
	~AnimatedObject();

	// Inherited via BaseAnimationHelper
	void SetAnimatedPosition(const glm::vec3& position) override;
	void SetAnimatedRotation(const glm::vec3& rotation) override;
	void SetAnimatedScale(const glm::vec3& scale) override;

};

