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
	MsgAssert("������?");
}


// �׽�Ʈ 
void CRecordingManager::Save(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	MsgAssert("������?");
}

void CRecordingManager::Start()
{
	/*GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("���� ������ nullptr �Դϴ�.");
		return;
	}*/

	// ���� �Լ���ü�� Ŭ��������Լ��� ������, ����ؾ��ҵ� 
	// CurLevel->TimeEvent.AddEvent(2.0f, Test, false);
}

void CRecordingManager::Update(float _DeltaTime)
{
}

void CRecordingManager::Render(float _DeltaTime)
{
}
