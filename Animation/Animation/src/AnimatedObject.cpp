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

void AnimatedObject::SetAnimatedRotation(const glm::quat& rotation)
{
	transform.SetQuatRotation(rotation);
}

void AnimatedObject::SetAnimatedScale(const glm::vec3& scale)
{
	transform.SetScale(scale);
}

void AnimatedObject::SetBaseColor(const glm::vec4& color)
{
	for (MeshAndMaterial* mesh : meshes)
	{
		mesh->material->AsMaterial()->SetBaseColor(color);
	}
}
