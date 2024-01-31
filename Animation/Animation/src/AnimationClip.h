#pragma once

#include <vector>
#include "BaseKeyFrame.h"

enum KeyFrameType
{
	POSITION = 0,
	ROTATION = 1,
	SCALE = 2,
};

class AnimationClip
{
public:
	double time;

	void AddKeyFrame(const glm::vec3& value, float time, EasingType easingType = EasingType::Linear);

	void SetCurrentKeyType(KeyFrameType keyType);

	std::vector<BaseKeyFrame<glm::vec3>> listOfPositionKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> listOfRotationKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> listOfScaleKeyFrames;
private:

	KeyFrameType currentKeyType = POSITION;


};

