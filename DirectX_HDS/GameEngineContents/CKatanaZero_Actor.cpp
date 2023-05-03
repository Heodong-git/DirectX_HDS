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
		MsgAssert("Level �� nullptr �Դϴ�.");
		return nullptr;
	}

	return Level;
}

void CKatanaZero_Actor::Update(float _DeltaTime)
{
	// ������Ʈ���� �ڽ��� ��ġ������ �����Ѵ�. 
	
}

