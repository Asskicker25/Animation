#include "AnimationSequence.h"
#include <iostream>

static int a = 0;

void AnimationSequence::CalculateTime(float deltaTime)
{
	if (a == 1)
	{
		std::cout << "Current Time : " << currentTime << std::endl;
	}
	switch (sequenceState)
	{
	case NORMAL:
		currentTime += deltaTime;
		break;
	case REVERSE:
		currentTime -= deltaTime;
		break;
	}

	if (currentTime < 0) { currentTime = 0; }
	if (currentTime > duration) { currentTime = duration; }

	a++;

	
}

void AnimationSequence::SetDuration(float duration)
{
	this->duration = duration;
}

float AnimationSequence::GetCurrentTime()
{
	return currentTime;
}

void AnimationSequence::Reset()
{
	switch (sequenceState)
	{
	case NORMAL:
		currentTime = 0;
		break;
	case REVERSE:
		currentTime = duration;
		break;
	}
}