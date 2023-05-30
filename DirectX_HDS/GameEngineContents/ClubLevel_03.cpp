#include "PrecompileHeader.h"
#include "ClubLevel_03.h"

#include <GameEnginePlatform/GameEngineInput.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "StageEditer.h"
#include "Map.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Battery.h"
#include "Cursor.h"
#include "Hud.h"
#include "PlaySupporter.h"
#include "Inven.h"
#include "Timer.h"

ClubLevel_03::ClubLevel_03()
{
}

ClubLevel_03::~ClubLevel_03()
{
}

void ClubLevel_03::Start()
{
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	// 필요한 키생성
	if (false == GameEngineInput::IsKey("ClubLevel03_ChangeLevel_ClubLevel04"))
	{
		GameEngineInput::CreateKey("ClubLevel03_ChangeLevel_ClubLevel04", VK_F1);
		GameEngineInput::CreateKey("ClubLevel03_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel03_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel03_ChangeMap", '2');
	}

	SetLevelType(LevelType::CLUBMAP3);

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();

	// 레벨의 상태를 변경해주는데 일단 지금은 바로 PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_03::Update(float _DeltaTime)
{
	
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_03::LevelChangeStart()
{
	// 필요하다면, GUI On <-- Core에서 초기화 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();

	CameraSetter::MainCamSetter->CameraSetting();

	// 플레이어 위치세팅
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->SetLocalPosition(m_PlayerSetPos);


	// HUD
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");

	// 플레이어 배터리 
	CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery");

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// 플레이서포터
	CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter");

	// 타이머
	CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer");

	// 인벤
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");
	
}

void ClubLevel_03::LevelChangeEnd()
{
	// 레벨이 종료될 때 , 대기상태로 변경
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_03::ResourcesLoad()
{
}

void ClubLevel_03::ActorLoad()
{
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_03.png");
	//m_Map->GetRender()->GetTransform()->SetLocalScale(float4{ 1557.0f , 1440.0f });
	

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("현재 플레이어가 nullptr 입니다.");
		return;
	}


}

void ClubLevel_03::DebugUpdate()
{
}
