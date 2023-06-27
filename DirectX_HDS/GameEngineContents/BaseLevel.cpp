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

	// 스테이지 클리어 체크
	LevelClearCheck();
	PlayerSkillCheck();
	DebugUpdate();

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
	// 플레이어 페이드인이펙트 
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
	// 레벨에서 초기화 되어야 할 부분을 초기화 
	Reset();

	// 순회하며 액터 초기화 
	std::vector <std::shared_ptr<class BaseActor>>::iterator StartIter = m_ResetActors.begin();
	std::vector <std::shared_ptr<class BaseActor>>::iterator EndIter = m_ResetActors.end();

	// 현재 벡터에 저장된 액터들을 순회하면서 리셋 
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