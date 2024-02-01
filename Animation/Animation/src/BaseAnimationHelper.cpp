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
	if (currentAnimationIndex < 0 || currentAnimationIndex >= listOfAnimationClips.size())
	{
		return nullptr;
	}

	return listOfAnimationClips[currentAnimationIndex];
}

void BaseAnimationHelper::SetCurrentAnimationClip(int index)
{
	currentAnimationIndex = index;
}

void BaseAnimationHelper::SetCurrentAnimationClip(AnimationClip* clip)
{
	for (int i = 0; i < listOfAnimationClips.size(); i++)
	{
		if (clip == listOfAnimationClips[i])
		{
			currentAnimationIndex = i;
			return;
		}
	}

	listOfAnimationClips.push_back(clip);
	currentAnimationIndex = listOfAnimationClips.size() - 1;
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

