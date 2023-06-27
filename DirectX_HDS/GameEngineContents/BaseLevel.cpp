#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Map.h"
#include "Player.h"
#include "FadeEffect.h"
#include "ColEventObj.h"
#include "Go_UI.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::CameraSetting()
{
	// ī�޶���
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}

void BaseLevel::Start()
{
	if (false == GameEngineInput::IsKey("SetLimitTime"))
	{
		// ����׿� 
		GameEngineInput::CreateKey("SetLimitTime", VK_F2);
		GameEngineInput::CreateKey("DebugRenderSwitch", 'Q');
	}

	// ī�޶���ġ, ����, Sort ����
	CameraSetting();
	LoadSound();
	CreateKey();

	// ���µ� ���͸� ������ ���� �ʱ�ȭ
	m_ResetActors.reserve(8);

	// ī�޶�����Ʈ ����
	m_FadeEffect = GetLastTarget()->CreateEffect<FadeEffect>();
}

void BaseLevel::Update(float _DeltaTime)
{
	// ���콺 ������ ����
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	KeyUpdate();

	// �������� Ŭ���� üũ
	LevelClearCheck();
	PlayerSkillCheck();
	DebugUpdate();

	// ���� ������ �����¶�� ������Ʈ���� ����
	if (BaseLevel::LevelState::WAIT == m_CurState)
	{
		return;
	}

	// ���緹���� �÷��̻��¶�� ���ѽð��� ���ҽ�Ų��. 
	if (BaseLevel::LevelState::PLAY == m_CurState)
	{

		if (0 >= m_LimitTime)
		{
			int a = 0;
		}

		m_LimitTime -= GameEngineTime::GlobalTime.GetDeltaTime();
	}

	// GameEngineLevel::Update(_DeltaTime);
}

// ���ͻ����� ���Ϳ� Ǫ��
void BaseLevel::Push_ResetActor(std::shared_ptr<class BaseActor> _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("���Ͱ� nullptr �Դϴ�.");
		return;
	}

	m_ResetActors.push_back(_Actor);
}

void BaseLevel::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("SetLimitTime"))
	{
		SetLimitTime(1.0f);
	}

	if (true == GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		IsDebugSwitch();
	}

	// Q �� ���⼭. 
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
}

void BaseLevel::LevelClearCheck()
{
	// �ϴ� �Ȼ������ 
	if (LevelType::CLUBBOSS0 == m_LevelType)
	{
		return;
	}

	if (true == IsClear() && LevelType::TITLE != m_LevelType)
	{
		if (false == m_IsClear)
		{
			m_IsClear = true;
			m_ColObj = CreateActor<ColEventObj>(static_cast<int>(RenderOrder::DEBUG));
			m_GoUI = CreateActor<Go_UI>(static_cast<int>(RenderOrder::UI));
			switch (m_LevelType)
			{
			case LevelType::CLUBMAP0:
			{
				m_ColObj->GetTransform()->SetLocalPosition({ 959.0f , -75.0f });
			}
			break;
			case LevelType::CLUBMAP1:
			{
				m_ColObj->GetTransform()->SetLocalPosition({ 636.0f, 48.0f});
			}
			break;
			case LevelType::CLUBMAP2:
			{
				m_ColObj->GetTransform()->SetLocalPosition({ 954.0f, 154.0f });
			}
			break;
			case LevelType::CLUBMAP3:
			{
				m_ColObj->GetTransform()->SetLocalPosition({ 738.0f, -515.0f });
			}
			break;
			case LevelType::CLUBMAP4:
			{
				m_ColObj->GetTransform()->SetLocalPosition({1305.0f, 465.0f });
			}
			break;
			case LevelType::NONE:
				break;
			default:
				break;
			}
		}
	}
}

void BaseLevel::PlayerSkillCheck()
{
	// �÷��̾� ���̵�������Ʈ 
	if (true == Player::MainPlayer->IsSkill())
	{
		GetFadeEffect()->FadeIn();
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		//m_FadeEffect->FadeOut();
	}
}

void BaseLevel::LevelReset()
{
	// �������� �ʱ�ȭ �Ǿ�� �� �κ��� �ʱ�ȭ 
	Reset();

	// ��ȸ�ϸ� ���� �ʱ�ȭ 
	std::vector <std::shared_ptr<class BaseActor>>::iterator StartIter = m_ResetActors.begin();
	std::vector <std::shared_ptr<class BaseActor>>::iterator EndIter = m_ResetActors.end();

	// ���� ���Ϳ� ����� ���͵��� ��ȸ�ϸ鼭 ���� 
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Reset();
	}
}

void BaseLevel::Reset()
{
	if (nullptr != m_GoUI)
	{
		m_GoUI->Death();
		m_GoUI = nullptr;
	}

	m_IsClear = false;
	SetLimitTime();
	ResetMonsterCount();
	ResetColObj();
	ResetSound();
	SetState(BaseLevel::LevelState::PLAY);
}

void BaseLevel::ResetColObj()
{
	if (nullptr != m_ColObj)
	{
		m_ColObj->Death();
	}
}

void BaseLevel::ResetSound()
{
	m_SoundPlayer.SetPosition(0.0f);
}

bool BaseLevel::IsClear()
{
	if (0 == m_MonsterCount)
	{
		return true;
	}

	return false;
}


// ----------------------------- Change Map -----------------------------------
void BaseLevel::ChangeColMap()
{
	if (LevelType::TITLE == m_LevelType || LevelType::NONE == m_LevelType)
	{
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
	case LevelType::CLUBBOSS0:
		m_Map->GetRender()->SetScaleToTexture("Club_ColMap_Boss_00.png");
		break;
	case LevelType::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. ���� Ÿ���� �����ϼ���.");
	}
	break;
	}
}

void BaseLevel::ChangeMap()
{
	if (LevelType::TITLE == m_LevelType || LevelType::NONE == m_LevelType)
	{
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
	case LevelType::CLUBBOSS0:
		m_Map->GetRender()->SetScaleToTexture("ClubMap_Boss_00.png");
		m_Map->GetRender()->GetTransform()->SetLocalScale(float4{ 1344.0f, 580.0f });
		break;	
	case LevelType::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
	break;
	}
}