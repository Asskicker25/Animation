#include "AnimationSequence.h"
#include <iostream>

void AnimationSequence::CalculateTime(float deltaTime)
{
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