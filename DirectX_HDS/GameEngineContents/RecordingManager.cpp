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

// �׽�Ʈ 
void RecordingManager::Save()
{
	MsgAssert("������?");
}

void RecordingManager::Start()
{
	/*GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("���� ������ nullptr �Դϴ�.");
		return;
	}*/
}

void RecordingManager::Update(float _DeltaTime)
{
}

void RecordingManager::Render(float _DeltaTime)
{
}
