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

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel::LevelChangeStart()
{
	// 레벨체인지하면서 imgui 를 on 시킬때 포커스가 해제되는중
	//m_GUI = GameEngineGUI::FindGUIWindowConvert<CStageEditer>("Stage_Editer");
	//if (m_GUI == nullptr)
	//{
	//	MsgAssert("GUI Window가 nullptr 입니다.");
	//	return;
	//}
	//m_GUI->On();

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
	// 맵 로드 , 맵은 그대로 깔고, 카메라를 움직인다. 
	m_Map_01 = CreateActor<Map>();
	m_Map_01->GetRender()->SetPipeLine("2DTexture");
	m_Map_01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");


	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	// 이게 댕글링포인터가 되지않..나? 
	std::shared_ptr<Hud> NewHud = CreateActor<Hud>(static_cast<int>(RenderOrder::BASEUI), "HUD");
	PlayManager::GetInst()->SetHud(NewHud);
	NewHud->GetTransform()->AddLocalPosition({ -ScreenSize.hx(), ScreenSize.hy() });

	std::shared_ptr<Cursor> NewCursor = CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
	SetCursor(NewCursor);
	
	std::shared_ptr<Battery> NewBattery = CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");
	PlayManager::GetInst()->SetBattery(NewBattery);
	
	std::shared_ptr<Inven> NewInven = CreateActor<Inven>(static_cast<int>(RenderOrder::BASEUI), "Inven");
	PlayManager::GetInst()->SetInven(NewInven);
	
	std::shared_ptr<Timer> NewTimer = CreateActor<Timer>(static_cast<int>(RenderOrder::BASEUI), "Timer");
	PlayManager::GetInst()->SetTimer(NewTimer);
	
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	SetPlayer(NewPlayer);
	NewPlayer->GetTransform()->AddLocalPosition(float4{ -850 , 0 , 0 });
	PlayManager::GetInst()->SetPlayer(NewPlayer);
}
