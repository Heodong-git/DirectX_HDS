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

	// ���ҽ��ε� 
	ResourcesLoad();
	// ���ͷε� 
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
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	// test
	m_RecordingManager = CreateActor<CRecordingManager>("RecordingManager");

	// Setname ���ϰ�����
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>(static_cast<int>(ERENDERORDER::PLAYER),"Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>(static_cast<int>(ERENDERORDER::BOSS),"HeadHunter");
	NewBoss->GetTransform()->SetLocalPosition({ 100 , -50 });
	SetBoss(NewBoss);

	// Ʈ������ �θ��ڽı��� �׽�Ʈ�ڵ� 
	// NewBoss->GetTransform()->SetParent(NewPlayer->GetTransform());
	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>(static_cast<int>(ERENDERORDER::CURSOR), "Cursor");
	SetCursor(NewCursor);
}
