#pragma once

#include <Graphics/InputManager/iInputListener.h>
#include <AnimationSequence.h>
#include <vector>
#include <functional>

class AnimationSequenceManager : public iInputListener
{
public:

	std::function<void(int)> OnSequenceChange = nullptr;

	void Initialize();
	AnimationSequenceManager();

	void AddSequence(AnimationSequence* sequence);
	void RemoveSequence(AnimationSequence* sequence);

	AnimationSequence* GetCurrentSequence();


	// Inherited via iInputListener
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;

private:

	void HandleNextSequence();
	void HandlePreviousSequence();
	void HandleSequenceStart();

	std::vector<AnimationSequence*> listOfSequences;

	int currentSequenceIndex = 0;
};

