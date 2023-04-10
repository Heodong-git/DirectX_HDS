#include "CKatanaZero_Level.h"
#include <GameEngineBase/GameEngineDebug.h>


CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void CKatanaZero_Level::Update(float _DeltaTime)
{
	if (115.0f >= GetTimeLimit())
	{
		//MsgAssert("실험용");
	}

	// 제한시간감소 
	TimeDecrease(_DeltaTime);

	// GameEngineLevel 의 update 를 virtual 로 변경해준다면 삭제
	GameEngineLevel::Update(_DeltaTime);
}

void CKatanaZero_Level::TimeOver()
{
	// 플레이어 사망, 자막출력 
}