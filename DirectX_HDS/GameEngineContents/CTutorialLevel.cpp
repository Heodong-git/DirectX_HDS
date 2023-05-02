#include "PrecompileHeader.h"
#include "CTutorialLevel.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

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
	ShowCursor(false);
	CKatanaZero_Level::Start();

	// ���ҽ��ε� 
	ResourcesLoad();
	// ���ͷε� 
	ActorLoad();
}

void CTutorialLevel::Update(float _DeltaTime)
{
}

void CTutorialLevel::LevelChangeStart()
{
}

void CTutorialLevel::LevelChangeEnd()
{
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

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>(static_cast<int>(ERENDERORDER::PLAYER),"Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>(static_cast<int>(ERENDERORDER::BOSS),"HeadHunter");
	NewBoss->GetTransform()->SetLocalPosition({ 100 , -50 });
	SetBoss(NewBoss);
	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>(static_cast<int>(ERENDERORDER::CURSOR), "Cursor");
	SetCursor(NewCursor);
}
