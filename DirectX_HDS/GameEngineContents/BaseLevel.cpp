#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Map.h"
#include "Player.h"
#include "FadeEffect.h"



BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

// ��緹������ �ʿ��ϱ� ������ base level ���� ������ �ִ´�. 
// �ٵ� �ϴ� ���� ���� �ϼ��ϸ� ���� �ϴ� ���� Ŭ������ 00���� ���� 
void BaseLevel::Start()
{
	CameraSetting();

	// ���̵��ξƿ� ����Ʈ
	m_FadeEffect = GetLastTarget()->CreateEffect<FadeEffect>();
}

void BaseLevel::Update(float _DeltaTime)
{
	// ���� Ŀ���� nullptr �� �ƴ϶�� 
	// �޾ƿͼ� ������������ ����
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	// �׽�Ʈ
	if (true == Player::MainPlayer->IsSlowSkill())
	{
		GetFadeEffect()->FadeIn();
	}

	else if (false == Player::MainPlayer->IsSlowSkill())
	{
		//m_FadeEffect->FadeOut();
	}

	if (true == GameEngineInput::IsDown("ClubLevel_DebugSwitch"))
	{
		DebugSwitch();

		if (true == IsDebug())
		{
			ChangeColMap();
			return;
		}

		if (false == IsDebug())
		{
			ChangeMap();
			return;
		}
	}

	if (BaseLevel::LevelState::WAIT == m_CurState)
	{
		return;
	}



	GameEngineLevel::Update(_DeltaTime);
}

void BaseLevel::LevelChangeStart()
{
	
}


void BaseLevel::CameraSetting()
{
	// ī�޶���
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}

void BaseLevel::ChangeMap()
{
	if (nullptr == m_Map)
	{
		MsgAssert("���� ���� nullptr �Դϴ�.");
		return;
	}

	switch (m_LevelType)
	{
	case LevelType::CLUBMAP0:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");
		break;
	case LevelType::CLUBMAP1:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_01.png");
		break;
	case LevelType::CLUBMAP2:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_02.png");
		break;
	case LevelType::CLUBMAP3:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_03.png");
		break;
	case LevelType::CLUBMAP4:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_04.png");
		break;
	case LevelType::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
	break;
	}
}

void BaseLevel::ChangeColMap()
{
	// ���� ������ Ÿ��Ʋ �����̶�� return �ؾ���.
	if (LevelType::NONE== m_LevelType)
	{
		// Ÿ��Ʋ���� �� ��� ��Ÿ���� ���õ��� �ʱ⶧���� �ش� �Լ��� ȣ��Ǹ� �ٷ� return; 
			return;
	}
	if (nullptr == m_Map)
	{
		MsgAssert("���� ���� nullptr �Դϴ�.");
		return;
	}

	switch (m_LevelType)
	{
	case LevelType::CLUBMAP0:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_00.png");
		break;
	case LevelType::CLUBMAP1:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_01.png");
		break;
	case LevelType::CLUBMAP2:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_02.png");
		break;
	case LevelType::CLUBMAP3:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_03.png");
		break;
	case LevelType::CLUBMAP4:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_04.png");
		break;
	case LevelType::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
	break;
	}
}

void BaseLevel::DebugCamera()
{
}
