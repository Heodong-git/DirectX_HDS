#include "PrecompileHeader.h"
#include "CStageLevel_01.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// 컨텐츠
#include "StageEditer.h"
#include "CPlayManager.h"
#include "CPlayer.h"
#include "Cursor.h"
#include "Battery.h"
#include "Inven.h"
#include "CTimer.h"
#include "CMap.h"
#include "Hud.h"

CStageLevel_01::CStageLevel_01()
{
}

CStageLevel_01::~CStageLevel_01()
{
}

void CStageLevel_01::Start()
{
	CKatanaZero_Level::Start();
	if (false == GameEngineInput::IsKey("Stage01_ChangeLevel_Stage02"))
	{
		GameEngineInput::CreateKey("Stage01_ChangeLevel_Stage02", VK_F1);
	}

	ResourcesLoad();
	ActorLoad();
}

void CStageLevel_01::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Stage01_ChangeLevel_Stage02"))
	{
		GameEngineCore::ChangeLevel("StageLevel_02");
		return;
	}

	CKatanaZero_Level::Update(_DeltaTime);
}

void CStageLevel_01::LevelChangeStart()
{
	// 레벨체인지하면서 imgui 를 on 시킬때 포커스가 해제되는중
	//m_GUI = GameEngineGUI::FindGUIWindowConvert<CStageEditer>("Stage_Editer");
	//if (m_GUI == nullptr)
	//{
	//	MsgAssert("GUI Window가 nullptr 입니다.");
	//	return;
	//}
	//m_GUI->On();

	CPlayManager::GetInst()->SetLevelType(CPlayManager::LEVELTYPE::STAGE_01);
	CPlayManager::GetInst()->CameraSetting();
	SetState(ELEVEL_STATE::PLAY);
}

void CStageLevel_01::LevelChangeEnd()
{
	SetState(ELEVEL_STATE::WAIT);

	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void CStageLevel_01::ResourcesLoad()
{

}

void CStageLevel_01::ActorLoad()
{
	// 맵 로드 , 맵은 그대로 깔고, 카메라를 움직인다. 
	m_Map_01 = CreateActor<CMap>();
	m_Map_01->GetRender()->SetPipeLine("2DTexture");
	m_Map_01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");


	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	// 이게 댕글링포인터가 되지않..나? 
	std::shared_ptr<Hud> NewHud = CreateActor<Hud>(static_cast<int>(ERENDERORDER::BASEUI), "HUD");
	CPlayManager::GetInst()->SetHud(NewHud);
	NewHud->GetTransform()->AddLocalPosition({ -ScreenSize.hx(), ScreenSize.hy() });

	std::shared_ptr<Cursor> NewCursor = CreateActor<Cursor>(static_cast<int>(ERENDERORDER::CURSOR), "Cursor");
	SetCursor(NewCursor);
	
	std::shared_ptr<Battery> NewBattery = CreateActor<Battery>(static_cast<int>(ERENDERORDER::BASEUI), "Battery");
	CPlayManager::GetInst()->SetBattery(NewBattery);
	
	std::shared_ptr<Inven> NewInven = CreateActor<Inven>(static_cast<int>(ERENDERORDER::BASEUI), "Inven");
	CPlayManager::GetInst()->SetInven(NewInven);
	
	std::shared_ptr<CTimer> Timer = CreateActor<CTimer>(static_cast<int>(ERENDERORDER::BASEUI), "Timer");
	CPlayManager::GetInst()->SetTimer(Timer);
	
	std::shared_ptr<CPlayer> Player = CreateActor<CPlayer>(static_cast<int>(ERENDERORDER::PLAYER), "Player");
	SetPlayer(Player);
	Player->GetTransform()->AddLocalPosition(float4{ -850 , 0 , 0 });
	CPlayManager::GetInst()->SetPlayer(Player);
}
