#pragma once

#include <Graphics/InputManager/InputManager.h>
#include <SkeletonModel.h>
#include <PhysicsSkeletonObject.h>
#include <Graphics/Mesh/Model.h>

class Character : public PhysicsSkeletonObject, public iInputListener
{
public:
	Character();
	virtual void OnKeyPressed(const int& key);

};

