#include "StarDestroyer.h"

StarDestroyer::StarDestroyer() : AnimatedObject()
{
	LoadModel("Assets/StarDestroyer/Stardestroyer.ply");
	name = "StarDestroyer";

	transform.SetPosition(glm::vec3(0));
	transform.SetRotation(glm::vec3(-7.70f, 140.0f, 0));
	transform.SetScale(glm::vec3(0.005f));
}

void StarDestroyer::Start()
{
	AnimatedObject::Start();
}

void StarDestroyer::Update(float deltaTime)
{
	AnimatedObject::Update(deltaTime);
}

void StarDestroyer::OnDestroy()
{
	AnimatedObject::OnDestroy();
}
