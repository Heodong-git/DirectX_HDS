#include "PrecompileHeader.h"
#include "ClubLevel_Boss.h"

#include <GameEnginePlatform/GameEngineInput.h>

ClubLevel_Boss::ClubLevel_Boss()
{
}

ClubLevel_Boss::~ClubLevel_Boss()
{
}

void ClubLevel_Boss::Start()
{
	BaseLevel::Start();

	ResourcesLoad();
	ActorLoad();
}

void ClubLevel_Boss::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_Boss::LevelChangeStart()
{
}

void ClubLevel_Boss::LevelChangeEnd()
{
}

void ClubLevel_Boss::ResourcesLoad()
{
}

void ClubLevel_Boss::ActorLoad()
{
}
