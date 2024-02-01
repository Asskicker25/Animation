#pragma once

#include <AnimatedObject.h>

class StarDestroyer : public AnimatedObject 
{
public:
	StarDestroyer();

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void OnDestroy();
};

