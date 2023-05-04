#include "PrecompileHeader.h"
#include "CTutorialLevel.h"

#include <GameEnginePlatform/GameengineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CPlayManager.h"
#include "CRecordingManager.h"
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CCursor.h"

CTutorialLevel::CTutorialLevel()
{
}

CTutorialLevel::~CTutorialLevel()
{
}


void CTutorialLevel::Start()
{
	CKatanaZero_Level::Start();
	if (false == GameEngineInput::IsKey("TestKey"))
	{
		GameEngineInput::CreateKey("Testkey", VK_F1);
	}

	// 리소스로드 
	ResourcesLoad();
	// 액터로드 
	ActorLoad();
}

void CTutorialLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Testkey"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
		return;
	}
}

void CTutorialLevel::LevelChangeStart()
{
	//ShowCursor(false);
}

void CTutorialLevel::LevelChangeEnd()
{
	//ShowCursor(true);
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
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	// test
	m_RecordingManager = CreateActor<CRecordingManager>("RecordingManager");

	// Setname 안하고있음
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>(static_cast<int>(ERENDERORDER::PLAYER),"Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>(static_cast<int>(ERENDERORDER::BOSS),"HeadHunter");
	NewBoss->GetTransform()->SetLocalPosition({ 100 , -50 });
	SetBoss(NewBoss);

	// 트랜스폼 부모자식구조 테스트코드 
	// NewBoss->GetTransform()->SetParent(NewPlayer->GetTransform());
	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>(static_cast<int>(ERENDERORDER::CURSOR), "Cursor");
	SetCursor(NewCursor);
}
