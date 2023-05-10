#include "PrecompileHeader.h"
#include "CStageLevel_01.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI ������ ���
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// ������
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
	// ����ü�����ϸ鼭 imgui �� on ��ų�� ��Ŀ���� �����Ǵ���
	//m_GUI = GameEngineGUI::FindGUIWindowConvert<CStageEditer>("Stage_Editer");
	//if (m_GUI == nullptr)
	//{
	//	MsgAssert("GUI Window�� nullptr �Դϴ�.");
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
	// �� �ε� , ���� �״�� ���, ī�޶� �����δ�. 
	m_Map_01 = CreateActor<CMap>();
	m_Map_01->GetRender()->SetPipeLine("2DTexture");
	m_Map_01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");


	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	// �̰� ��۸������Ͱ� ������..��? 
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
