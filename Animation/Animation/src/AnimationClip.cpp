#include "AnimationClip.h"

void AnimationClip::AddKeyFrame(const glm::vec3& value, float time, EasingType easingType)
{
	switch (currentKeyType)
	{
	case POSITION:
		
		listOfPositionKeyFrames.push_back({ value, time, easingType });
		break;
	
	case ROTATION:

		listOfRotationKeyFrames.push_back({ value, time, easingType });
		break;

	case SCALE:

		listOfScaleKeyFrames.push_back({ value, time, easingType });
		break;

	default:
		break;
	}
}

void AnimationClip::SetCurrentKeyType(KeyFrameType keyType)
{
	currentKeyType = keyType;
}
