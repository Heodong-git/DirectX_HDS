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
		MsgAssert("Level �� nullptr �Դϴ�.");
		return nullptr;
	}

	return Level;
}

void BaseActor::Update(float _DeltaTime)
{
}

