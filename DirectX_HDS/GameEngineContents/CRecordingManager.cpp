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

// �׽�Ʈ 
void CRecordingManager::Save()
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
	// GetReturnCastLevel()->TimeEvent.AddEvent(2.0f, std::bind(&CRecordingManager::Save, this), true);
}

void CRecordingManager::Update(float _DeltaTime)
{
}

void CRecordingManager::Render(float _DeltaTime)
{
}
