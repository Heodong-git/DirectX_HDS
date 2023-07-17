#include "PrecompileHeader.h"
#include "SoundManager.h"

SoundManager* SoundManager::MainManager = nullptr;

SoundManager::SoundManager()
{
	MainManager = this;
}

SoundManager::~SoundManager()
{
}

