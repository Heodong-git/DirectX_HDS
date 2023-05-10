#include "PrecompileHeader.h"
#include "ClubBossLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

ClubBossLevel::ClubBossLevel()
{
}

ClubBossLevel::~ClubBossLevel()
{
}

void ClubBossLevel::Start()
{
	BaseLevel::Start();

	ResourcesLoad();
	ActorLoad();
}

void ClubBossLevel::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubBossLevel::LevelChangeStart()
{
}

void ClubBossLevel::LevelChangeEnd()
{
}

void ClubBossLevel::ResourcesLoad()
{
}

void ClubBossLevel::ActorLoad()
{
}
