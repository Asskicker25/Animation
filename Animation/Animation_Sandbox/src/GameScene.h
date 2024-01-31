#pragma once

#include <Graphics/EntityManager/Entity.h>
#include <AnimatedObject.h>
#include <AnimationSystem.h>

class AnimationSequenceManager;


class GameScene : public Entity
{
public:

	GameScene();
	std::vector<AnimatedObject*> listOfAnimatedObjects;
	AnimationSequenceManager* sequenceManager;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	void OnSequenceChange(int index);
	void OnSequenceReset(int index);
};

