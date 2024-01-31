#include "KeyFrameEvent.h"

KeyFrameEvent::KeyFrameEvent(float time, std::function<void()> callback) 
	: eventTime { time }
	, OnEventTrigger { callback }
{
}
