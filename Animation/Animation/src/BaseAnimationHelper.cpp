#include "BaseAnimationHelper.h"

void BaseAnimationHelper::AddAnimationClip(AnimationClip* clip)
{
	listOfAnimationClips.push_back(clip);
}

void BaseAnimationHelper::RemoveAnimationClip(AnimationClip* clip)
{
	listOfAnimationClips.erase(std::remove(listOfAnimationClips.begin(),
		listOfAnimationClips.end(), clip), listOfAnimationClips.end());
}

AnimationClip* BaseAnimationHelper::GetCurrentAnimationClip()
{
	return listOfAnimationClips[currentAnimationIndex];
}

void BaseAnimationHelper::SetCurrentAnimationClip(int index)
{
	if (index < 0) { index = 0; }
	if (index >= listOfAnimationClips.size()) { index = listOfAnimationClips.size() - 1; }

	currentAnimationIndex = index;
}


int BaseAnimationHelper::GetCurrentAnimationIndex()
{
	return currentAnimationIndex;
}

void BaseAnimationHelper::SetCurrentKeyType(KeyFrameType keyType)
{
	GetCurrentAnimationClip()->SetCurrentKeyType(keyType);
}

bool BaseAnimationHelper::IsAnimationAvailable()
{
	return listOfAnimationClips.size() == 0 ? false : true;
}

