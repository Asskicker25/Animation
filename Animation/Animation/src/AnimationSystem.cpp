#include "AnimationSystem.h"
#include <glm/gtx/easing.hpp>


AnimationSystem& AnimationSystem::GetInstance()
{
	static AnimationSystem instance;
	return instance;
}

void AnimationSystem::AddAnimatedObject(BaseAnimationHelper* animObject)
{
	listOfAnimatedObjects.push_back(animObject);
}

void AnimationSystem::RemoveAnimatedObject(BaseAnimationHelper* animObject)
{
	listOfAnimatedObjects.erase(std::remove(listOfAnimatedObjects.begin(),
		listOfAnimatedObjects.end(), animObject), listOfAnimatedObjects.end());
}

void AnimationSystem::UpdateAnimations(float deltaTime)
{
	if (!isPlaying) return;

	animationTime += deltaTime * animationSpeed;

	for (BaseAnimationHelper* animObject : listOfAnimatedObjects)
	{
		if (!animObject->IsAnimationAvailable()) continue;

		animObject->GetCurrentAnimationClip()->time = animationTime;
		HandleAnimation(animObject);
	}
}

void AnimationSystem::TogglePlayAndPause()
{
	isPlaying = !isPlaying;
}

void AnimationSystem::HandleAnimation(BaseAnimationHelper* animObject)
{
	AnimationClip* animationClip = animObject->GetCurrentAnimationClip();

	HandleKeyFrames_Vector3(animationClip->time, animationClip->listOfPositionKeyFrames, [animObject](glm::vec3 value)
		{
			animObject->SetAnimatedPosition(value);
		});

	HandleKeyFrames_Vector3(animationClip->time, animationClip->listOfRotationKeyFrames, [animObject](glm::vec3 value)
		{
			animObject->SetAnimatedRotation(value);
		});

	HandleKeyFrames_Vector3(animationClip->time, animationClip->listOfScaleKeyFrames, [animObject](glm::vec3 value)
		{
			animObject->SetAnimatedScale(value);
		});

}

void AnimationSystem::HandleKeyFrames_Vector3(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames, 
	std::function<void(glm::vec3)> OnValueApply)
{
	if (keyFrames.size() == 0) return;

	if (keyFrames.size() == 1)
	{
		OnValueApply(keyFrames[0].mValue);
		return;
	}

	int keyFrameEndIndex = 0;
	for (; keyFrameEndIndex < keyFrames.size(); keyFrameEndIndex++)
	{
		if (keyFrames[keyFrameEndIndex].mTime > time)
		{
			break;
		}
	}

	if (keyFrameEndIndex >= keyFrames.size())
	{
		OnValueApply(keyFrames[keyFrameEndIndex-1].mValue);
		return;
	}

	int keyFrameStartIndex = keyFrameEndIndex - 1;

	BaseKeyFrame<glm::vec3> startKeyFrame = keyFrames[keyFrameStartIndex];
	BaseKeyFrame<glm::vec3> endKeyFrame = keyFrames[keyFrameEndIndex];

	float percent = (time - startKeyFrame.mTime) / (endKeyFrame.mTime - startKeyFrame.mTime);

	float result = 0.0f;

	switch (endKeyFrame.mEasingType)
	{
	case EasingType::Linear:
		result = percent;
		break;

	case EasingType::SineEaseIn:
		result = glm::sineEaseIn(percent);
		break;

	case EasingType::SineEaseOut: 
		result = glm::sineEaseOut(percent);
		break;

	case EasingType::SineEaseInOut:
		result = glm::sineEaseInOut(percent);
		break;

	}

	glm::vec3 delta = endKeyFrame.mValue - startKeyFrame.mValue;
	OnValueApply(startKeyFrame.mValue + delta * result);

}

