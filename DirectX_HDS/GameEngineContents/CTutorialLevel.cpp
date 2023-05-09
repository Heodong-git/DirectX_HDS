#include "PrecompileHeader.h"
#include "CTutorialLevel.h"

#include <GameEnginePlatform/GameengineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "CPlayManager.h"
#include "CRecordingManager.h"
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CCursor.h"
#include "CBattery.h"
#include "CInven.h"
#include "CTimer.h"
#include "CTitleEditer.h"

CTutorialLevel::CTutorialLevel()
{
}

CTutorialLevel::~CTutorialLevel()
{
}

void CTutorialLevel::Start()
{
	// TimeEvent.AddEvent(3.0f, std::bind(&CTutorialLevel::TestTest, this));
	CKatanaZero_Level::Start();
	if (false == GameEngineInput::IsKey("Stage01_ChangeLevel"))
	{
		GameEngineInput::CreateKey("Stage01_ChangeLevel", VK_F1);
	}

	// ���ҽ��ε� 
	ResourcesLoad();
	// ���ͷε� 
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
	SetState(ELEVEL_STATE::PLAY);
	m_GUI = GameEngineGUI::FindGUIWindowConvert<CTitleEditer>("Title_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	m_GUI->On();
}

void CTutorialLevel::LevelChangeEnd()
{
	//ShowCursor(true);
	SetState(ELEVEL_STATE::WAIT);
	m_GUI->Off();

}

void CTutorialLevel::ResourcesLoad()
{
	{
		// ���丮 Ŭ��������
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("TutorialLevel");

		// ���� ��ü�ε� 
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
