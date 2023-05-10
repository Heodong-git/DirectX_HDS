#include "PrecompileHeader.h"
#include "RecordingManager.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <functional>

#include "BaseLevel.h"

RecordingManager::RecordingManager()
{
	m_vecTest.resize(70);
}

RecordingManager::~RecordingManager()
{
}

// 테스트 
void RecordingManager::Save()
{
	MsgAssert("들어오나?");
}

void RecordingManager::Start()
{
	/*GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}*/
}

void RecordingManager::Update(float _DeltaTime)
{
}

void RecordingManager::Render(float _DeltaTime)
{
}
