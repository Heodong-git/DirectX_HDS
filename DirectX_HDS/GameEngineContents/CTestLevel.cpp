#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CCursor.h"
#include "CBackGround.h"
#include "CTitleManager.h"
#include "CPlayManager.h"
#include "CRecordingManager.h"

// test
#include <GameEngineCore/GameEngineVideo.h>


CTestLevel::CTestLevel()
{
}

CTestLevel::~CTestLevel()
{
}

void CTestLevel::Start()
{
	CKatanaZero_Level::Start();

	// �ش� �������� ����� ���ҽ��� �ε��Ѵ�. 
	// �ش� ������ ����Ǹ� �ε��� ���ҽ��� ��� �����Ѵ� 
	// ������ �ε� �� ��� ������ �̸����δ� ������ �� ����.
	// ���ҽ�, ���ͷε� 
	ResourcesLoad();
	ActorLoad();
}

void CTestLevel::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
}

void CTestLevel::ResourcesLoad()
{
}

void CTestLevel::ActorLoad()
{
	// �Ŵ���. static�� �´°Ű�����������
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	m_RecordingManager = CreateActor<CRecordingManager>("RecordingManager");

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	std::shared_ptr<CCursor> NewCursor = CreateActor<CCursor>("Mouse");
	SetCursor(NewCursor);
}


void CTestLevel::LevelChangeStart()
{
}

void CTestLevel::LevelChangeEnd()
{
	
}

