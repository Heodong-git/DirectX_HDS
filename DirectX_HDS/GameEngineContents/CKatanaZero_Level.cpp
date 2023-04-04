#include "CKatanaZero_Level.h"

CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void CKatanaZero_Level::Start()
{
	
}

// GameEngineLevel 의 업데이트가 virtual 이 되어야될거같은데. 
void CKatanaZero_Level::Update(float _DeltaTime)
{
	if (110.0f >= GetTimeLimit())
	{
		int a = 0;
	}

	// 제한시간감소 
	TimeDecrease(_DeltaTime);

	GameEngineLevel::Update(_DeltaTime);
}

void CKatanaZero_Level::TimeOver()
{
	// 플레이어 사망, 자막출력 
}