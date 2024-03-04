#pragma once

#include <Graphics/InputManager/InputManager.h>
#include <SkeletonModel.h>

class Character : public SkeletonModel, public iInputListener
{
public:
	Character();
	virtual void OnKeyPressed(const int& key);

};

