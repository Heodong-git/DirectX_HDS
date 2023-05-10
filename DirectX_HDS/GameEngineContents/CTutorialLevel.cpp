#include "PrecompileHeader.h"
#include "CTutorialLevel.h"

#include <GameEnginePlatform/GameengineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlayManager.h"
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "Cursor.h"
#include "Battery.h"
#include "Inven.h"
#include "Timer.h"
#include "TitleEditer.h"

CTutorialLevel::CTutorialLevel()
{
}

CTutorialLevel::~CTutorialLevel()
{
}

void CTutorialLevel::Start()
{
	// TimeEvent.AddEvent(3.0f, std::bind(&CTutorialLevel::TestTest, this));
	BaseLevel::Start();
	if (false == GameEngineInput::IsKey("Stage01_ChangeLevel"))
	{
		GameEngineInput::CreateKey("Stage01_ChangeLevel", VK_F1);
	}

	// 리소스로드 
	ResourcesLoad();
	// 액터로드 
	ActorLoad();
}

void CTutorialLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Stage01_ChangeLevel"))
	{
		GameEngineCore::ChangeLevel("StageLevel_01");
		return;
	}
}

void CTutorialLevel::LevelChangeStart()
{
	//ShowCursor(false);
	SetState(BaseLevel::LevelState::PLAY);
	m_GUI = GameEngineGUI::FindGUIWindowConvert<TitleEditer>("Title_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();
}

void CTutorialLevel::LevelChangeEnd()
{
	//ShowCursor(true);
	SetState(BaseLevel::LevelState::WAIT);
	m_GUI->Off();

}

void CTutorialLevel::ResourcesLoad()
{
	{
		// 디렉토리 클래스생성
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("TutorialLevel");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}

void CTutorialLevel::ActorLoad()
{
	/*m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	std::shared_ptr<CBattery> Battery = CreateActor<CBattery>(static_cast<int>(ERENDERORDER::BASEUI), "Battery");
	m_PlayManager->SetBattery(Battery);
	std::shared_ptr<CInven> Inven = CreateActor<CInven>(static_cast<int>(ERENDERORDER::BASEUI),"Inven");
	m_PlayManager->SetInven(Inven);
	std::shared_ptr<CTimer> Timer = CreateActor<CTimer>(static_cast<int>(ERENDERORDER::BASEUI), "Timer");
	m_PlayManager->SetTimer(Timer);
	
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>(static_cast<int>(ERENDERORDER::PLAYER),"Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>(static_cast<int>(ERENDERORDER::BOSS),"HeadHunter");
	NewBoss->GetTransform()->SetLocalPosition({ 100 , -50 });
	SetBoss(NewBoss);

	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>(static_cast<int>(ERENDERORDER::CURSOR), "Cursor");
	SetCursor(NewCursor);*/
}
