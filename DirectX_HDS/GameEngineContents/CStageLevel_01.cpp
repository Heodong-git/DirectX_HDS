#include "PrecompileHeader.h"
#include "CStageLevel_01.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "CStageEditer.h"

#include "CKatanaZero_Level.h"
#include "CPlayManager.h"
#include "CPlayer.h"
#include "CCursor.h"
#include "CBattery.h"
#include "CInven.h"
#include "CMap.h"
#include "CTimer.h"
#include "CHud.h"


CStageLevel_01::CStageLevel_01()
{
}

CStageLevel_01::~CStageLevel_01()
{
}

void CStageLevel_01::Start()
{
	CKatanaZero_Level::Start();

	if (false == GameEngineInput::IsKey("Stage01_ChangeLevel_Title"))
	{
		GameEngineInput::CreateKey("Stage01_ChangeLevel_Title", VK_F1);
	}

	ResourcesLoad();
	ActorLoad();
}

void CStageLevel_01::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Stage01_ChangeLevel_Title"))
	{
		GameEngineCore::ChangeLevel("Titlelevel");
		return;
	}

	CKatanaZero_Level::Update(_DeltaTime);
}

void CStageLevel_01::LevelChangeStart()
{
	m_GUI = GameEngineGUI::FindGUIWindowConvert<CStageEditer>("Stage_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();

	SetState(ELEVEL_STATE::PLAY);
}

void CStageLevel_01::LevelChangeEnd()
{
	SetState(ELEVEL_STATE::WAIT);
	m_GUI->Off();
}

void CStageLevel_01::ResourcesLoad()
{
	//// 디렉토리 클래스생성
	//GameEngineDirectory NewDir;
	//// 원하는 폴더를 가진 디렉터리로 이동
	//NewDir.MoveParentToDirectory("katanazero_resources");
	//// 그 폴더로 이동
	//NewDir.Move("katanazero_resources");
	//NewDir.Move("Texture");
	//NewDir.Move("Stage01Level");

	//// 파일 전체로드 
	//std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
	//for (size_t i = 0; i < File.size(); i++)
	//{
	//	GameEngineTexture::Load(File[i].GetFullPath());
	//}
}

void CStageLevel_01::ActorLoad()
{
	// 맵 생성, 
	m_Map = CreateActor<CMap>();
	m_Map->GetRender()->SetPipeLine("2DTexture");
	m_Map->GetRender()->SetScaleToTexture("Club_0.png");
	m_Map->GetTransform()->SetLocalPosition(float4{ 300, -31 });

	// 이게 댕글링포인터가 되지않..나? 
	std::shared_ptr<CHud> Hud = CreateActor<CHud>(static_cast<int>(ERENDERORDER::BASEUI), "HUD");
	CPlayManager::GetInst()->SetHud(Hud);

	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>(static_cast<int>(ERENDERORDER::CURSOR), "Cursor");
	SetCursor(NewCursor);
	
	std::shared_ptr<CBattery> Battery = CreateActor<CBattery>(static_cast<int>(ERENDERORDER::BASEUI), "Battery");
	CPlayManager::GetInst()->SetBattery(Battery);
	
	std::shared_ptr<CInven> Inven = CreateActor<CInven>(static_cast<int>(ERENDERORDER::BASEUI), "Inven");
	CPlayManager::GetInst()->SetInven(Inven);
	
	std::shared_ptr<CTimer> Timer = CreateActor<CTimer>(static_cast<int>(ERENDERORDER::BASEUI), "Timer");
	CPlayManager::GetInst()->SetTimer(Timer);
	
	std::shared_ptr<CPlayer> Player = CreateActor<CPlayer>(static_cast<int>(ERENDERORDER::PLAYER), "Player");
	SetPlayer(Player);

	/*m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	m_PlayManager->CreateRender();

	std::shared_ptr<CBattery> Battery = CreateActor<CBattery>(static_cast<int>(ERENDERORDER::BASEUI), "Battery");
	m_PlayManager->SetBattery(Battery);
	std::shared_ptr<CInven> Inven = CreateActor<CInven>(static_cast<int>(ERENDERORDER::BASEUI), "Inven");
	m_PlayManager->SetInven(Inven);
	std::shared_ptr<CTimer> Timer = CreateActor<CTimer>(static_cast<int>(ERENDERORDER::BASEUI), "Timer");
	m_PlayManager->SetTimer(Timer);*/
}
