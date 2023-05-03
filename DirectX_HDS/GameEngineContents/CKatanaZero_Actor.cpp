#include "PrecompileHeader.h"
#include "CKatanaZero_Actor.h"
#include "CKatanaZero_Level.h"

CKatanaZero_Actor::CKatanaZero_Actor()
{
}

CKatanaZero_Actor::~CKatanaZero_Actor()
{
}

CKatanaZero_Level* CKatanaZero_Actor::GetReturnCastLevel() const
{
	CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
	
	if (nullptr == Level)
	{
		MsgAssert("Level 이 nullptr 입니다.");
		return nullptr;
	}

	return Level;
}

void CKatanaZero_Actor::Update(float _DeltaTime)
{
	// 업데이트마다 자신의 위치정보를 저장한다. 
	
}

