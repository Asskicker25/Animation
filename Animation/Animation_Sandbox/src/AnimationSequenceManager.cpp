#include "AnimationSequenceManager.h"
#include <Graphics/InputManager/InputManager.h>
#include <iostream>
#include <Graphics/Debugger.h>
#include <AnimationSystem.h>

void AnimationSequenceManager::Initialize()
{
	HandleSequenceStart();
}

AnimationSequenceManager::AnimationSequenceManager()
{
	InputManager::GetInstance().AddListener(this);
}

void AnimationSequenceManager::AddSequence(AnimationSequence* sequence)
{
	sequence->currentSequenceIndex = (int)listOfSequences.size();
	listOfSequences.push_back(sequence);
}

void AnimationSequenceManager::RemoveSequence(AnimationSequence* sequence)
{
	listOfSequences.erase(std::remove(listOfSequences.begin(), listOfSequences.end(), sequence),
		listOfSequences.end());
}

AnimationSequence* AnimationSequenceManager::GetCurrentSequence()
{
	return listOfSequences[currentSequenceIndex];
}

void AnimationSequenceManager::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_LEFT)
	{
		HandlePreviousSequence();
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		HandleNextSequence();
	}
	else if (key == GLFW_KEY_R)
	{
		OnReset(currentSequenceIndex);
		GetCurrentSequence()->sequenceState = GetCurrentSequence()->sequenceState == REVERSE ? NORMAL : REVERSE;
	}
}

void AnimationSequenceManager::OnKeyReleased(const int& key)
{
}

void AnimationSequenceManager::OnKeyHeld(const int& key)
{
}

void AnimationSequenceManager::HandleNextSequence()
{
	currentSequenceIndex++;

	if (currentSequenceIndex >= listOfSequences.size()) 
	{
		currentSequenceIndex = listOfSequences.size() - 1;
	}
	else
	{
		HandleSequenceStart();
	}

}

void AnimationSequenceManager::HandlePreviousSequence()
{
	currentSequenceIndex--;
	if (currentSequenceIndex < 0) 
	{ 
		currentSequenceIndex = 0; 
	}
	else
	{
		HandleSequenceStart();
	}

}

void AnimationSequenceManager::HandleSequenceStart()
{
	GetCurrentSequence()->Reset();
	AnimationSystem::GetInstance().currentSequence = GetCurrentSequence();
	OnSequenceChange(currentSequenceIndex);
	OnReset(currentSequenceIndex);
}
