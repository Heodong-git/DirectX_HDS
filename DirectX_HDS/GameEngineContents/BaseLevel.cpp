#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlaySupporter.h"
#include "Map.h"
#include "Player.h"
#include "FadeEffect.h"
#include "ColEventObj.h"
#include "Go_UI.h"
#include "DistotionEffect.h"
#include "GlitchEffect.h"
#include "OldFilmEffect.h"
#include "KatanaFadeEffect.h"


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
	m_GlitchEffect = GetLastTarget()->CreateEffect<GlitchEffect>();
	m_OldFilmEffect = GetLastTarget()->CreateEffect<OldFilmEffect>();
	m_KatanaFadeEffect = GetLastTarget()->CreateEffect<KatanaFadeEffect>();
}

void BaseLevel::Update(float _DeltaTime)
{
	if (LevelType::CLUBBOSS0 == m_LevelType)
	{
		if (true == GetKatanaFadeEffect()->IsComplete())
		{
			GameEngineCore::ChangeLevel("ClubLevel_Boss_01");
			return;
		}
	}

	if (true == GetKatanaFadeEffect()->IsComplete() && true == Player::MainPlayer->IsRecording())
	{
		LevelType CurLevelType = GetLevelType();

		switch (CurLevelType)
		{
		case LevelType::CLUBMAP0:
			// GetReturnCastLevel()->GetFadeEffect()->FadeOut();
			GameEngineCore::ChangeLevel("ClubLevel_01");
			break;
		case LevelType::CLUBMAP1:
			GameEngineCore::ChangeLevel("ClubLevel_02");
			break;
		case LevelType::CLUBMAP2:
			GameEngineCore::ChangeLevel("ClubLevel_03");
			break;
		case LevelType::CLUBMAP3:
			GameEngineCore::ChangeLevel("ClubLevel_Boss");
			break;
		case LevelType::CLUBMAP4:
			GameEngineCore::ChangeLevel("ClubLevel_Boss");
			break;
		}

		return;
	}

	// ���콺 ������ ����
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	KeyUpdate();
	// ���������� Ŭ���� �Ǿ����� üũ 
	LevelClearCheck();
	// ����׿� ������Ʈ 
	DebugUpdate();
	// ��ȭ ������Ʈ 
	RecordingUpdate(_DeltaTime);

	// ���� ������ �����¶�� ������Ʈ���� ����
	if (BaseLevel::LevelState::WAIT == m_CurState)
	{
		return;
	}

	// ���緹���� �÷��̻��¶�� ���ѽð��� ���ҽ�Ų��. 
	if (BaseLevel::LevelState::PLAY == m_CurState)
	{
		PlayerSkillCheck();
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

void BaseLevel::RecordingUpdate(float _DeltaTime)
{
	// ���� ��ȭ���� ���¿��� ���콺 ��Ŭ���� �ԷµǾ��ٸ�
	if (BaseLevel::LevelState::RECORDING_PROGRESS == m_CurState && true == GameEngineInput::IsDown("EngineMouseLeft"))
	{
		GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(m_TimeScale);
		GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(m_TimeScale);
		m_DistotionEffect->EffectOff();
		
		ActorReset();
		m_CurState = BaseLevel::LevelState::PLAY;
		
		

		return;
	}

	if (true == Player::MainPlayer->IsRecording())
	{
		m_CurState = BaseLevel::LevelState::PLAY;
		GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(m_TimeScale);
		GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(m_TimeScale);

		if (nullptr != m_DistotionEffect)
		{
			m_DistotionEffect->EffectOff();
		}

	

		return;
	}
}

void BaseLevel::ActorReset()
{
	// ���¾���... �� 
	std::vector <std::shared_ptr<class BaseActor>>::iterator StartIter = m_ResetActors.begin();
	std::vector <std::shared_ptr<class BaseActor>>::iterator EndIter = m_ResetActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->ForcedReset();
	}
}

void BaseLevel::LevelClearCheck()
{
	// �ϴ� �Ȼ������ 
	// ���������� ��� return; 
	if (LevelType::CLUBBOSS0 == m_LevelType || LevelType::CLUBBOSS1 == m_LevelType)
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
		// �÷��̾ ��ų ������̶��
		if (true == m_SoundPlayer.IsValid())
		{
			m_SoundPlayer.SetPitch(0.15f);
		}
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		m_SoundPlayer.SetPitch(1.0f);
	}
}

void BaseLevel::LevelReset()
{
	// �������� �ʱ�ȭ �Ǿ�� �� �κ��� �ʱ�ȭ 
	Reset();
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

	// ���⼭ �÷��̰� �ƴ϶� ��ȭ���� ���·� ����
	// �÷��̾ �ƴϸ�, ���� ���� ���°� �ƴϴ��� �ڷ� ���ư����� 
	// �ٸ� ���͵���, ������ ���ڵ����Ĺ��� ���°� �Ǹ� ������Ʈ�����ʰ�,
	// ���ڵ� ���α׷��� ���°� �Ǹ� ��ȭ���·� ���� �ǵ��� 
	// ���⼭ ���������Ʈ 
	SetState(BaseLevel::LevelState::RECORDING_PROGRESS);
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(m_RecordingTimeScale);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(m_RecordingTimeScale);
	if (nullptr == m_DistotionEffect)
	{
		m_DistotionEffect = GetLevel()->GetLastTarget()->CreateEffect<DistotionEffect>();
	}

	m_DistotionEffect->EffectOn();
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