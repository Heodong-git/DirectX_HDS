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

#include "DistotionEffect.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::CameraSetting()
{
	// 카메라세팅
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}

void BaseLevel::Start()
{
	if (false == GameEngineInput::IsKey("SetLimitTime"))
	{
		// 디버그용 
		GameEngineInput::CreateKey("SetLimitTime", VK_F2);
		GameEngineInput::CreateKey("DebugRenderSwitch", 'Q');
	}

	// 카메라위치, 투영, Sort 세팅
	CameraSetting();
	LoadSound();
	CreateKey();

	// 리셋될 액터를 저장할 벡터 초기화
	m_ResetActors.reserve(8);

	// 카메라이펙트 생성
	m_FadeEffect = GetLastTarget()->CreateEffect<FadeEffect>();
}

void BaseLevel::Update(float _DeltaTime)
{
	// 마우스 포지션 저장
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	KeyUpdate();
	LevelClearCheck();
	PlayerSkillCheck();
	DebugUpdate();

	if (true == Player::MainPlayer->IsRecording())
	{
		m_CurState = BaseLevel::LevelState::PLAY;
		GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(m_TimeScale);
		GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(m_TimeScale);
		m_DistotionEffect->EffectOff();
		return;
	}

	// 현재 레벨이 대기상태라면 업데이트하지 않음
	if (BaseLevel::LevelState::WAIT == m_CurState)
	{
		return;
	}

	// 현재레벨이 플레이상태라면 제한시간을 감소시킨다. 
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

// 액터생성후 벡터에 푸시
void BaseLevel::Push_ResetActor(std::shared_ptr<class BaseActor> _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("액터가 nullptr 입니다.");
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

	// Q 만 여기서. 
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
	// 일단 안생기게해 
	// 보스레벨일 경우 return; 
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
	// 플레이어 페이드인이펙트 
	if (true == Player::MainPlayer->IsSkill())
	{
		// GetFadeEffect()->FadeIn();
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		//m_FadeEffect->FadeOut();
	}
}

void BaseLevel::LevelReset()
{
	// 레벨에서 초기화 되어야 할 부분을 초기화 
	Reset();

	// 임시
	return;

	// 순회하며 액터 초기화 
	std::vector <std::shared_ptr<class BaseActor>>::iterator StartIter = m_ResetActors.begin();
	std::vector <std::shared_ptr<class BaseActor>>::iterator EndIter = m_ResetActors.end();

	// 현재 벡터에 저장된 액터들을 순회하면서 리셋 
	// 여기서 액터를 순회하면서 리셋하는게 아니라. 
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

	// 여기서 플레이가 아니라 녹화진행 상태로 변경
	// 플레이어가 아니면, 딱히 죽은 상태가 아니더라도 뒤로 돌아가야함 
	// 다른 몬스터들은, 레벨이 레코딩스탠바이 상태가 되면 업데이트하지않고,
	// 레코딩 프로그레스 상태가 되면 녹화상태로 변경 되도록 
	// 여기서 디스토션이펙트 
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
		MsgAssert("현재 맵이 nullptr 입니다.");
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
		MsgAssert("현재 맵의 이름이 NONE 입니다. 레벨 타입을 세팅하세요.");
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
		MsgAssert("현재 맵이 nullptr 입니다.");
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
		MsgAssert("현재 맵의 이름이 NONE 입니다. 이름을 세팅하세요.");
		return;
	}
	break;
	}
}