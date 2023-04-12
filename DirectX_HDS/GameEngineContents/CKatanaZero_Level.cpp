#include "PrecompileHeader.h"
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

bool CKatanaZero_Level::RecordTimeCheck()
{
	return true;
}

// 일정 시간마다 현재 액터의 상태 등을 기록하여 저장
void CKatanaZero_Level::RecordActor()
{
}

// 저장된 정보들을 불러오고 역재생
void CKatanaZero_Level::ReversePlay(float _DeltaTime)
{
}

void CKatanaZero_Level::TimeOver()
{
	// 플레이어 사망, 자막출력 
}