#include "PrecompileHeader.h"
#include "CRecordingManager.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <functional>

CRecordingManager::CRecordingManager()
{
	m_vecTest.reserve(70);
}

CRecordingManager::~CRecordingManager()
{
}


void Test(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	MsgAssert("들어오나?");
}


// 테스트 
void CRecordingManager::Save(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	MsgAssert("들어오나?");
}

void CRecordingManager::Start()
{
	/*GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}*/

	// 지금 함수자체가 클래스멤버함수는 못넣음, 얘기해야할듯 
	// CurLevel->TimeEvent.AddEvent(2.0f, Test, false);
}

void CRecordingManager::Update(float _DeltaTime)
{
}

void CRecordingManager::Render(float _DeltaTime)
{
}
