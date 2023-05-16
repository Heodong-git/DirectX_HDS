#include "PrecompileHeader.h"
#include "ClubLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// 컨텐츠
#include "StageEditer.h"
#include "PlayManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Battery.h"
#include "Map.h"

// 아직
#include "Inven.h"
#include "Timer.h"
#include "Hud.h"

ClubLevel::ClubLevel()
{
}

ClubLevel::~ClubLevel()
{
}

void ClubLevel::Start()
{
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	// 필요한 키생성
	if (false == GameEngineInput::IsKey("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineInput::CreateKey("ClubLevel_ChangeLevel_ClubBossLevel", VK_F1);
		GameEngineInput::CreateKey("ClubLevel_DebugSwitch", 'Q');
	}

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();
}

void ClubLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineCore::ChangeLevel("ClubBossLevel");
		return;
	}

	if (true == GameEngineInput::IsDown("ClubLevel_DebugSwitch"))
	{
		DebugSwitch();
	}

	DebugUpdate();
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel::LevelChangeStart()
{
	//레벨체인지하면서 imgui 를 on 시킬때 포커스가 해제되는중
	//레벨 start 의 기본 인터페이스

	// 필요하다면, GUI On <-- Core에서 초기화 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();

	// 필요한 액터 생성, 초기화(세팅)
	CreateActor<PlayManager>();
	PlayManager::MainManager->SetLevelType(PlayManager::LevelName::CLUB);
	PlayManager::MainManager->CameraSetting();

	// 레벨의 상태를 변경해주는데 일단 지금은 바로 PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel::LevelChangeEnd()
{
	// 레벨이 종료될 때 , 대기상태로 변경
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel::ResourcesLoad()
{
	// 레벨에서 필요한 리소스 로드
	// 액터가 자기자신의 리소스를 로드하도록 하는중.
}

void ClubLevel::ActorLoad()
{
	// 맵 
	m_Map_Club01 = CreateActor<Map>(-10);
	m_Map_Club01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");
	//m_Map_01->GetRender()->SetAtlasConstantBuffer();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	// 플레이어
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->AddLocalPosition(float4{ -850 , -94 });

	// 플레이어 배터리 
	CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
}

void ClubLevel::DebugUpdate()
{
	// 일단 임시 픽셀충돌 사용하지 않을 수도 있음
	if (true == IsDebug())
	{
		m_Map_Club01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");
	}

	else if (false == IsDebug())
	{
		m_Map_Club01->GetRender()->SetScaleToTexture("Club_0.png");
	}
}
