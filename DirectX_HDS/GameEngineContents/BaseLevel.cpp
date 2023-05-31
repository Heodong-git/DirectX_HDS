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

// 모든레벨에서 필요하기 때문에 base level 에서 가지고 있는다. 
// 근데 일단 오늘 구조 완성하면 ㅇㅇ 일단 기존 클럽레벨 00에서 ㄱㄱ 
void BaseLevel::Start()
{
	CameraSetting();

	// 벡터 리사이즈 
	m_ResetActors.reserve(8);

	// 페이드인아웃 이펙트
	m_FadeEffect = GetLastTarget()->CreateEffect<FadeEffect>();
}

void BaseLevel::Update(float _DeltaTime)
{

	// 현재 커서가 nullptr 이 아니라면 
	// 받아와서 로컬포지션을 저장
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	}

	// 여기서 Go도 만들어 
	// 현재 맵이 클리어 되었는지
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
				m_ColObj->GetTransform()->SetLocalPosition({ 653.0f, 48.0f});
			}
				break;
			case LevelType::CLUBMAP2:
			{

			}
				break;
			case LevelType::CLUBMAP3:
			{

			}
				break;
			case LevelType::CLUBMAP4:
			{

			}
				break;
			case LevelType::NONE:
				break;
			default:
				break;
			}
		}
	}


	// 플레이어 페이드인이펙트 
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

	// 없어도 되지만 일단 임시로 
	// 만약 현재 스테이트가 Play 라면 제한시간을 감소시킨다. 
	if (BaseLevel::LevelState::PLAY == m_CurState)
	{

		if (0 >= m_LimitTime)
		{
			// 플레이어 사망, 맵은 대기상태로 변경
			int a = 0;
		}

		m_LimitTime -= GameEngineTime::GlobalTime.GetDeltaTime();
	}

	GameEngineLevel::Update(_DeltaTime);
}

void BaseLevel::LevelChangeStart()
{
	
}


void BaseLevel::CameraSetting()
{
	// 카메라세팅
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}



void BaseLevel::ChangeMap()
{
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
	case LevelType::NONE:
	{
		MsgAssert("현재 맵의 이름이 NONE 입니다. 이름을 세팅하세요.");
		return;
	}
	break;
	}
}

void BaseLevel::ChangeColMap()
{
	// 현재 레벨이 타이틀 레벨이라면 return 해야함.
	if (LevelType::NONE== m_LevelType)
	{
		// 타이틀레벨 일 경우 맵타입이 세팅되지 않기때문에 해당 함수가 호출되면 바로 return; 
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
	case LevelType::NONE:
	{
		MsgAssert("현재 맵의 이름이 NONE 입니다. 이름을 세팅하세요.");
		return;
	}
	break;
	}
}

void BaseLevel::DebugCamera()
{
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

// 레벨 리셋을 호출하면 그냥 얘가 호출되는거지 자식에서 재정의는 하지않고 
void BaseLevel::LevelReset()
{
	// 일단 레벨의 제한시간 초기화 
	Reset();

	// 레벨 Start 에서 반드시 벡터에 추가
	//if (0 == m_ResetActors.size())
	//{
	//	// 일단걸어두고
	//	// MsgAssert("현재 초기화되어야할 액터의 수가 0 입니다.");
	//	return;
	//}

	std::vector <std::shared_ptr<class BaseActor>>::iterator StartIter = m_ResetActors.begin();
	std::vector <std::shared_ptr<class BaseActor>>::iterator EndIter = m_ResetActors.end();

	// 현재 벡터에 저장된 액터들을 순회하면서 리셋 
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Reset();
	}

	// 일단 여기까지 , 후에 추가 작업필요할 경우 코드 작성
}

void BaseLevel::Reset()
{
	m_IsClear = false;
	SetLimitTime();
	ResetMonsterCount();
	ResetColObj();
	SetState(BaseLevel::LevelState::PLAY);
}

void BaseLevel::ResetColObj()
{
	if (nullptr != m_ColObj)
	{
		m_ColObj->Death();
	}
}

bool BaseLevel::IsClear()
{
	if (0 == m_MonsterCount)
	{
		return true;
	}

	return false;
}
