#include "PrecompileHeader.h"
#include "BaseActor.h"
#include "BaseLevel.h"

#include <GameEngineBase/GameEngineRandom.h>

BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

const int BaseActor::CreateRandomValue(const int _MAX)
{
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, _MAX);
	return RandomValue;
}

BaseLevel* BaseActor::GetReturnCastLevel() const
{
	BaseLevel* Level = dynamic_cast<BaseLevel*>(GetLevel());
	
	if (nullptr == Level)
	{
		MsgAssert("Level 이 nullptr 입니다.");
		return nullptr;
	}

	return Level;
}

void BaseActor::Update(float _DeltaTime)
{
}

