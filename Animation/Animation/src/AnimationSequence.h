#pragma once

enum SequenceState
{
	NORMAL = 0,
	REVERSE = 1
};

class AnimationSequence
{
public:

	void CalculateTime(float deltaTime);
	void SetDuration(float duration);
	void Reset();

	float GetCurrentTime();

	SequenceState sequenceState = NORMAL;

	int currentSequenceIndex = 0;

private:
	float duration;
	float currentTime;
};

