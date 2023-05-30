#include "PrecompileHeader.h"
#include "BaseActor.h"
#include "BaseLevel.h"


BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
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

