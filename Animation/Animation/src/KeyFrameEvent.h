#pragma once

#include <functional>

class KeyFrameEvent
{
public:

	KeyFrameEvent(float time, std::function<void()> callback);

	std::function<void()> OnEventTrigger;

	float eventTime = 0;

	bool isEventTriggered = false;
};

