#pragma once

#include <Graphics/InputManager/InputManager.h>
#include <SkeletonModel.h>
#include <PhysicsSkeletonObject.h>
#include <Graphics/Mesh/Model.h>

class Character : public PhysicsSkeletonObject, public iInputListener
{
public:
	Character();
	void Initialize();
	virtual void OnKeyPressed(const int& key);
	virtual void Start();
	virtual void Update(float deltaTime) override;

};

