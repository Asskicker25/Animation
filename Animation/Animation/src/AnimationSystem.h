#pragma once
#include <vector>
#include <functional>
#include "AnimatedObject.h"
#include "AnimationSequence.h"

class AnimationSystem
{

public:

	static AnimationSystem& GetInstance();

	void AddAnimatedObject(BaseAnimationHelper* animObject);
	void RemoveAnimatedObject(BaseAnimationHelper* animObject);
	void UpdateAnimations(float deltaTime);
	void TogglePlayAndPause();

	AnimationSequence* currentSequence;

	float animationSpeed = 1;

private:

	void HandleAnimation(BaseAnimationHelper* animObject);

	void HandleKeyFrames_Vector3(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames, 
		std::function<void(glm::vec3)> OnValueApply = nullptr);

	void HandleKeyFrames_Quaternion(double time, std::vector<BaseKeyFrame<glm::vec3>>& keyFrames,
		std::function<void(glm::quat)> OnValueApply = nullptr);

	std::vector<BaseAnimationHelper*> listOfAnimatedObjects;
	
	bool isPlaying = true;
};

