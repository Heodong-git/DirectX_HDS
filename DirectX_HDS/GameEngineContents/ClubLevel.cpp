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
#include "Inven.h"
#include "Timer.h"
#include "Map.h"
#include "Hud.h"

ClubLevel::ClubLevel()
{
}

ClubLevel::~ClubLevel()
{
}

void ClubLevel::Start()
{
	BaseLevel::Start();
	if (false == GameEngineInput::IsKey("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineInput::CreateKey("ClubLevel_ChangeLevel_ClubBossLevel", VK_F1);
		GameEngineInput::CreateKey("ClubLevel_DebugSwitch", 'Q');
	}

	ResourcesLoad();
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
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();

	PlayManager::GetInst()->SetLevelType(PlayManager::LevelName::CLUB);
	PlayManager::GetInst()->CameraSetting();
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel::LevelChangeEnd()
{
	SetState(BaseLevel::LevelState::WAIT);

	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel::ResourcesLoad()
{

}

void ClubLevel::ActorLoad()
{
	// 맵 
	m_Map_01 = CreateActor<Map>();
	m_Map_01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");
	//m_Map_01->GetRender()->SetAtlasConstantBuffer();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	// 플레이어
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->AddLocalPosition(float4{ -850 , -94 });

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
}

void ClubLevel::DebugUpdate()
{
	// 일단 임시 픽셀충돌 사용하지 않을 수도 있음
	if (true == IsDebug())
	{
		m_Map_01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");
	}

	else if (false == IsDebug())
	{
		m_Map_01->GetRender()->SetScaleToTexture("Club_0.png");
	}
}
