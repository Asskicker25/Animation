#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "AnimationClip.h"

class BaseAnimationHelper
{
public:

	bool canAnimate = true;
	bool showEasingColor = false;

	virtual void SetAnimatedPosition(const glm::vec3& position) = 0;
	virtual void SetAnimatedRotation(const glm::vec3& rotation) = 0;
	virtual void SetAnimatedRotation(const glm::quat& rotation) = 0;
	virtual void SetAnimatedScale(const glm::vec3& scale) = 0;
	virtual void SetBaseColor(const glm::vec4& color) = 0;

	void AddAnimationClip(AnimationClip* clip);
	void RemoveAnimationClip(AnimationClip* clip);

	void SetCurrentAnimationClip(int index = 0);
	void SetCurrentAnimationClip(AnimationClip* clip);

	AnimationClip* GetCurrentAnimationClip();
	int GetCurrentAnimationIndex();

	void SetCurrentKeyType(KeyFrameType keyType);

	bool IsAnimationAvailable();

private:

	std::vector<AnimationClip*> listOfAnimationClips;

	int currentAnimationIndex = 0;

};

