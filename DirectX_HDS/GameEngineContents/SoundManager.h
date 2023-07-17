#pragma once

// Ό³Έν :
class SoundManager
{
public:
	static SoundManager* MainManager;

public:
	// constrcuter destructer
	SoundManager();
	~SoundManager();

	// delete Function
	SoundManager(const SoundManager& _Other) = delete;
	SoundManager(SoundManager&& _Other) noexcept = delete;
	SoundManager& operator=(const SoundManager& _Other) = delete;
	SoundManager& operator=(SoundManager&& _Other) noexcept = delete;

protected:

private:
	
};
