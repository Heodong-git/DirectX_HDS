#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Map.h"
#include "Player.h"
#include "FadeInOut_Effect.h"



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
}

void BaseLevel::Update(float _DeltaTime)
{
	// 현재 커서가 nullptr 이 아니라면 
	// 받아와서 로컬포지션을 저장
	if (nullptr != Cursor::MainCursor)
	{
		m_CurMouseLocalPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
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
