#pragma once

#include <glm/glm.hpp>

enum class EasingType
{
	Linear,
	SineEaseIn,
	SineEaseOut,
	SineEaseInOut
};


template <typename T>
struct BaseKeyFrame
{
public:
	BaseKeyFrame(const T& value, double time, EasingType easingType)
		: mValue { value }
		, mTime  { time }
		, mEasingType { easingType }
	{ }

	T mValue;
	EasingType mEasingType;
	double mTime;
};
