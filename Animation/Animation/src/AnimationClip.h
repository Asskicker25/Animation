#pragma once

#include <vector>
#include "BaseKeyFrame.h"
#include "KeyFrameEvent.h"

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

	void AddKeyFrameEvent(KeyFrameEvent* keyframeEvent);

	void ResetKeyFrameTrigger();

	void SetCurrentKeyType(KeyFrameType keyType);

	std::vector<BaseKeyFrame<glm::vec3>> listOfPositionKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> listOfRotationKeyFrames;
	std::vector<BaseKeyFrame<glm::vec3>> listOfScaleKeyFrames;

	std::vector<KeyFrameEvent*> listOfKeyFrameEvents;

private:

	KeyFrameType currentKeyType = POSITION;


};

