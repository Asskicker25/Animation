#include "AnimatedObject.h"
#include "AnimationSystem.h"

AnimatedObject::AnimatedObject()
{
	AnimationSystem::GetInstance().AddAnimatedObject(this);
}

AnimatedObject::~AnimatedObject()
{
	AnimationSystem::GetInstance().RemoveAnimatedObject(this);
}

void AnimatedObject::SetAnimatedPosition(const glm::vec3& position)
{
	transform.SetPosition(position);
}

void AnimatedObject::SetAnimatedRotation(const glm::vec3& rotation)
{
	transform.SetRotation(rotation);
}

void AnimatedObject::SetAnimatedScale(const glm::vec3& scale)
{
	transform.SetScale(scale);
}
