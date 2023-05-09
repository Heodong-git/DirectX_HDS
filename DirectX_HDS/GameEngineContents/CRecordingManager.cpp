#include "PrecompileHeader.h"
#include "CRecordingManager.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <functional>

#include "CKatanaZero_Level.h"

CRecordingManager::CRecordingManager()
{
	m_vecTest.reserve(70);
}

CRecordingManager::~CRecordingManager()
{
}

// 테스트 
void CRecordingManager::Save()
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
	// GetReturnCastLevel()->TimeEvent.AddEvent(2.0f, std::bind(&CRecordingManager::Save, this), true);
}

void CRecordingManager::Update(float _DeltaTime)
{
}

void CRecordingManager::Render(float _DeltaTime)
{
}
